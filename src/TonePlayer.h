#ifndef TONEPLAYER_H
#define TONEPLAYER_H

#include <ao/ao.h>


/**
 * Plays tones on given frequency and time.
 */
class TonePlayer {
public:
    void init();
    void destroy();
    void play(float freq, float fractionOfSecond, int volume);
    bool isInited();

private:
    bool _isInited = false;
    int default_driver;
    ao_sample_format format;
    ao_device *device;
    char *buffer;
};


#endif /* TONEPLAYER_H */
