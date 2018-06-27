#include "TeaSession.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include "App.h"
#include "Printer.h"
#include "TonePlayer.h"
#include "ConsoleReader.h"
#include "SessionData.h"
#include "Settings.h"
#include "Utils.h"
#include "Notifier.h"
#include "Actions.h"


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


// TODO: Awesome idea: possibility to run timer in background.


int parseInt(const string &i) {
    try {
        return stoi(i);
    } catch (invalid_argument &) {
        return -1;
    }
}

void playEndTune(App &app, int soundVolume) {
    app.tonePlayer.play(380, .5, soundVolume);
    app.tonePlayer.play(420, .5, soundVolume);
    app.tonePlayer.play(500, 1, soundVolume);
}

const milliseconds sleepTime{100};


string getProgressBar(bool doAlarms) {
    static const string on("on");
    static const string off("off");

    return string(" [Press 'a' to abort, +/- to adjust time, t: toggle alarms [now " +
            (doAlarms ? on : off) + "]]> ");
}


// TODO: Why did I not used seconds instead of int?
void session(App &app, Settings &settings, int durationInSeconds) {
    int duration = durationInSeconds;
    seconds waitTime{durationInSeconds};
    int totalMilliseconds = durationInSeconds * 1000;

    const system_clock::time_point start = system_clock::now();
    milliseconds passedTime;
    bool noAbort = true;
    bool doAlarms = true;

    app.consoleReader.startSession();

    // This is the first draw to show something fast without waiting (=sleeping).
    // Second draw is after user input to ensure that it will always reflect the
    // last input.
    app.printer.drawProgressBar(80, 0.0, 0, duration);
    app.printer.drawNotice(getProgressBar(doAlarms));
    do {
        // Loop sleep.
        sleep_for(sleepTime);

        // User input.
        if (app.consoleReader.isInput()) {
            char userInput = app.consoleReader.getInput();
            switch (userInput) {
                case 'a':
                    noAbort = false;
                    break;

                case 't':
                    doAlarms = ! doAlarms;
                    break;

                case '+':
                case '-':
                    if (userInput == '+') duration += 1;
                    else duration -= 1;

                    waitTime = seconds{duration};
                    totalMilliseconds = duration * 1000;
                    break;
            }
        }

        // Calculate current timing.
        system_clock::time_point end = system_clock::now();
        passedTime = duration_cast<milliseconds>(end - start);
        seconds passedTimeSeconds = duration_cast<seconds>(passedTime);

        // Re-draw printer.
        double fraction = static_cast<double>(passedTime.count()) / totalMilliseconds;
        app.printer.eraseOutput(1);
        if (noAbort) {
            app.printer.drawProgressBar(80, fraction, passedTimeSeconds.count(), duration);
            app.printer.drawNotice(getProgressBar(doAlarms));
        } else {
            app.printer.drawCancelledProgressBar(80, fraction, passedTimeSeconds.count(), duration);
        }
    } while ((passedTime <= waitTime) && noAbort);

    if (noAbort) {
        // Signal end of session to the user.
        if (doAlarms) {
            if (settings.showNotifications && app.notifier.isInited()) {
                app.notifier.notify();
            }
            if (settings.playSound && app.tonePlayer.isInited()) {
                playEndTune(app, settings.soundVolume);
            }
        }
        // Record session.
        app.sessionData.addSession(duration, start);
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
        char *ch = readline("gongfu> ");

        if (ch == NULL) {
            run = false;
            cout << endl << "Quiting... " << endl;
        } else {
            input = ch;
            free(ch);
            Utils::trim(input);

            if (input == "quit" || input == "q") {
                run = false;
            } else if (input == "") {
                // Skip empty lines.
            } else {
                // Regular command.
                add_history(input.c_str());

                // TODO: Rework this into action.
                if (input == "info" || input == "i") {
                    app.printer.printSession(app.sessionData);
                    cout << endl;
                } else {
                    add_history(input.c_str());

                    auto inputSplit = Utils::split(input, " ");
                    Utils::printStrVector(inputSplit);
                    Action *action = Action::factory(inputSplit);
                    if (action != NULL) {
                        action->execute(settings, app.sessionData);
                        delete action;
                    } else {
                        int i = parseInt(input);

                        if (i <= 0) {
                            run = false;
                        } else {
                            session(app, settings, i);
                            cout << endl;
                            app.printer.printSession(app.sessionData);
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
}

