#include <iostream>
#include <string>
#include <TonePlayer.h>


float tones[] = {
    440,  // A  0
    466.16,  // A#  1
    493.88,  // B  2
    523.25,  // C  3
    554.37,  // C#  4
    587.33,  // D  5
    622.25,  // D#  6
    659.26,  // E  7
    698.46,  // F  8
    739.99,  // F#  9
    783.99,  // G  10
    830.61  //G#  11
    };

int main(int argc, char **argv) {
    TonePlayer *tp = new TonePlayer();
    tp->init();

    std::string input;
    int volume = 80;

    while (input != "q") {
        std::cin >> input;
        int tone = -1;

        if (input.size() > 0 && input[0] == 'v') {
            volume = std::stoi(input.substr(1));
        } else {
            try {
                tone = std::stoi(input);
            } catch(...) {
                break;
            }

            std::cout << tones[tone] << " " << volume << std::endl;
            tp->play(tones[tone], .5, volume);
        }
    }

    tp->destroy();
    delete tp;
}

