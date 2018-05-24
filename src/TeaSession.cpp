#include "TeaSession.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include "Printer.h"
#include "TonePlayer.h"
#include "ConsoleReader.h"
#include "SessionData.h"
#include "Settings.h"
#include "Utils.h"


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
    ConsoleReader consoleReader;
    SessionData sessionData;
};


int parseInt(const string &i) {
    try {
        return stoi(i);
    } catch (invalid_argument &) {
        return -1;
    }
}

void playEndTune(App &app) {
    app.tonePlayer.play(380, .5);
    app.tonePlayer.play(420, .5);
    app.tonePlayer.play(500, 1);
}

const milliseconds sleepTime{200};

void session(App &app, Settings &settings, int durationInSeconds) {
    const system_clock::time_point start = system_clock::now();
    const seconds waitTime{durationInSeconds};
    milliseconds passedTime;
    const int totalMilliseconds = durationInSeconds * 1000;
    bool noAbort = true;

    app.consoleReader.startSession();

    app.printer.drawProgressBar(80, 0.0, 0, durationInSeconds);
    app.printer.drawNotice(" [Press 'a' to abort]> ");
    do {
        sleep_for(sleepTime);
        system_clock::time_point end = system_clock::now();

        passedTime = duration_cast<milliseconds>(end - start);
        seconds passedTimeSeconds = duration_cast<seconds>(passedTime);

        app.printer.eraseOutput(1);

        double fraction = static_cast<double>(passedTime.count()) / totalMilliseconds;
        app.printer.drawProgressBar(80, fraction, passedTimeSeconds.count(), durationInSeconds);
        app.printer.drawNotice(" [Press 'a' to abort]> ");

        if (app.consoleReader.isInput()) {
            char userInput = app.consoleReader.getInput();
            switch (userInput) {
                case 'a':
                    app.printer.eraseOutput(1);
                    app.printer.drawCancelledProgressBar(80, fraction, passedTimeSeconds.count(), durationInSeconds);
                    noAbort = false;
                    break;
            }
        }
    } while ((passedTime <= waitTime) && noAbort);

    if (noAbort) {
        if (settings.playSound) {
            playEndTune(app);
        }
        app.sessionData.addSession(durationInSeconds, start);
    }

    app.printer.clearLine();

    app.consoleReader.stopSession();
}


TeaSession::TeaSession(Settings &settings) {
    this->settings = settings;
}


void TeaSession::run() {
    App app;

    string input;
    bool run = true;

    // Disable readline tab completion.
    // TODO: it does not work..:(
    rl_bind_key('\t', rl_insert);

    while (run) {
        if (app.sessionData.getSessionNum() > 0) {
            cout << endl;
            app.printer.printSession(app.sessionData);
        }

        input = readline("> ");
        Utils::trim(input);

        if (input == "q") {
            run = false;
        } if (input == "") {
            // Skip empty lines.
        } else {
            add_history(input.c_str());

            int i = parseInt(input);

            if (i <= 0) {
                run = false;
            } else {
                session(app, settings, i);
            }
        }
    }

}

