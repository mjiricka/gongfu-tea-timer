#include "TonePlayer.h"

#include <ao/ao.h>
#include <math.h>
#include <cassert>
#include <stdexcept>


// Inspiration: https://xiph.org/ao/doc/ao_example.c


using std::runtime_error;


static const char bits = 16;
static const char channels = 2;
static const int rate = 44100;
static const int sampleBits = (bits / 8) * channels;
static const int totalBufferSize = sampleBits * rate;
static const int volumeMagic = (1 << 15);  // This number is used in official libao example.


void TonePlayer::init() {
    assert(_isInited == false);

    ao_initialize();

    default_driver = ao_default_driver_id();

    format = ao_sample_format();
    format.bits = bits;
    format.channels = channels;
    format.rate = rate;
    format.byte_format = AO_FMT_LITTLE;

    device = ao_open_live(default_driver, &format, NULL /* no options */);
    if (device == NULL) {
        throw runtime_error("Error opening device.");
    }

    buffer = new char[totalBufferSize];

    _isInited = true;
}

void TonePlayer::destroy() {
    assert(_isInited == true);
    _isInited = false;

    ao_close(device);
    ao_shutdown();
    delete[] buffer;
}

void TonePlayer::play(float freq, float fractionOfSecond, int volume) {
    assert(_isInited == true);
    assert(0 < fractionOfSecond && fractionOfSecond <= 1.0);
    assert(0 <= volume && volume <= 100);

    int numSamples = format.rate * fractionOfSecond;
    int bufSize = sampleBits * numSamples;

    for (int i = 0; i < numSamples; i++) {
        float volumeF = (volume / 100.0) * volumeMagic;
        int sample = (int)(volumeF * sin(2 * M_PI * freq * ((float) i/format.rate)));

        // Put the same stuff in left and right channel.
        // I have no idea why it is done like that :(
        assert(bits == 16);
        buffer[4*i] = buffer[4*i+2] = sample & 0xff;
        buffer[4*i+1] = buffer[4*i+3] = (sample >> 8) & 0xff;
    }
    ao_play(device, buffer, bufSize);
}

bool TonePlayer::isInited() {
    return _isInited;
}

