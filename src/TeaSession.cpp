#include "TeaSession.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "Printer.h"
#include "TonePlayer.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::invalid_argument;
using std::stoi;


class App {
public:
    App() : printer(true) {
        tonePlayer.init();
    }

    ~App() {
        tonePlayer.destroy();
    }

    Printer printer;
    TonePlayer tonePlayer;
};


int parseInt(const string &i) {
    try {
        return stoi(i);
    } catch (invalid_argument) {
        return -1;
    }
}

void playEndTune(App &app) {
    app.tonePlayer.play(380, .5);
    app.tonePlayer.play(420, .5);
    app.tonePlayer.play(500, 1);
}

const milliseconds sleepTime{200};

void session(App &app, int i) {
    const system_clock::time_point start = system_clock::now();
    const seconds waitTime{i};
    milliseconds passedTime;
    const int totalMilliseconds = i * 1000;

    app.printer.drawProgressBar(80, 0, 0, i);
    app.printer.drawNotice(" [p - pause, c - cancel]> ");
    do {
        sleep_for(sleepTime);
        system_clock::time_point end = system_clock::now();

        passedTime = duration_cast<milliseconds>(end - start);
        seconds passedTimeSeconds = duration_cast<seconds>(passedTime);

        app.printer.eraseOutput(1);

        double fraction = static_cast<double>(passedTime.count()) / totalMilliseconds;
        app.printer.drawProgressBar(80, fraction, passedTimeSeconds.count(), i);

        app.printer.drawNotice(" [p - pause, c - cancel]> ");
    } while (passedTime <= waitTime);

    app.printer.clearLine();

    playEndTune(app);
}

void TeaSession::run() {
    App app;

    string input;
    bool run = true;

    while (run) {
        app.printer.drawPrompt("> ");
        cin >> input;

        if (input == "q") {
            run = false;
        } else {
            int i = parseInt(input);

            if (i <= 0) {
                run = false;
            } else {
                session(app, i);
            }
        }
    }

}

