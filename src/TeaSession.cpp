#include "TeaSession.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "Printer.h"


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


int parseInt(const string &i) {
    try {
        return stoi(i);
    } catch (invalid_argument) {
        return -1;
    }
}

const milliseconds sleepTime{200};

void session(Printer &printer, int i) {
    const system_clock::time_point start = system_clock::now();
    const seconds waitTime{i};
    milliseconds passedTime;

    printer.drawProgressBar(80, 0, i);
    printer.drawNotice(" [p - pause, c - cancel]> ");
    do {
        sleep_for(sleepTime);
        system_clock::time_point end = system_clock::now();

        passedTime = duration_cast<milliseconds>(end - start);
        seconds passedTimeSeconds = duration_cast<seconds>(passedTime);

        printer.eraseOutput(1);

        printer.drawProgressBar(80, passedTimeSeconds.count(), i);
        printer.drawNotice(" [p - pause, c - cancel]> ");
    } while (passedTime <= waitTime);

    printer.clearLine();
    //printer.drawProgressBar(80, i, total);
    //printer.drawNotice(" [p - pause, c - cancel]> ");

}

void TeaSession::run() {
    Printer printer(true);

    string input;
    bool run = true;

    while (run) {
        printer.drawPrompt("> ");
        cin >> input;

        if (input == "q") {
            run = false;
        } else {
            int i = parseInt(input);

            if (i <= 0) {
                run = false;
            } else {
                session(printer, i);
            }
        }
    }

}

