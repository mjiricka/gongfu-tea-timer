#include "Printer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include "Utils.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::min;


// TODO
string col1 = "\033[1;33m";  // yellow
string col2 = "\033[0;32m";  // green
string col3 = "\033[1;30m";  // lightgray
string colReset = "\033[0m";

static const int MAX_TIME_LENGTH = 6;


struct ProgressBarColours {
    string brace;
    string text;
    string fill;
};

static ProgressBarColours noLabelColours{col1, "", col2};
static ProgressBarColours withLabelColours{col1, col2, col3};



static void printProgressBar(size_t length, size_t done, const ProgressBarColours &colours, const string &label) {
    assert(label.size() < length);

    cout << colours.brace << "[" << colours.fill;

    size_t labelSize = label.size();
    size_t whenLabelStarts = labelSize > 0 ? (length - labelSize) / 2 : length;
    size_t i = 0;

    while (i < length) {
        if (i == whenLabelStarts) {
            cout << colours.text << label << colours.fill;
            i += labelSize;
        } else {
            cout << ((i < done) ? "\u25A0" : " ");
            ++i;
        }
    }
    cout << colours.brace << "]" << colReset;
}

static void doDrawProgressBar(int width, double fraction, int secondsPassed, int secondsTotal, ProgressBarColours &colours, const string &label = "") {
    assert(secondsPassed <= secondsTotal);
    assert(0 <= secondsPassed);
    assert(0 < secondsTotal);

    string passed = Utils::padLeft(Utils::seconds2string(secondsPassed), MAX_TIME_LENGTH);
    string total = Utils::padRight(Utils::seconds2string(secondsTotal), MAX_TIME_LENGTH);

    cout << passed << "/" << total << " ";
    int done = ceil(width * fraction);
    printProgressBar(width, done, colours, label);
    cout << endl;
}


Printer::Printer(bool useColours) {
    // TODO
}

void Printer::eraseOutput(int numLines) {
    for (int i = 0; i < numLines; ++i) {
        cout << "\r\033[K\033[1A";
    }
    cout.flush();
}

void Printer::clearLine() {
    cout << "\r\033[K";
    cout.flush();
}

void Printer::drawProgressBar(int width, double fraction, int secondsPassed, int secondsTotal) {
    doDrawProgressBar(
        width,
        min(fraction, 1.0),
        min(secondsPassed, secondsTotal),
        secondsTotal, noLabelColours);
}

void Printer::drawPausedProgressBar(int width, double fraction, int secondsPassed, int secondsTotal) {
    doDrawProgressBar(
        width,
        min(fraction, 1.0),
        min(secondsPassed, secondsTotal),
        secondsTotal, noLabelColours,
        "PAUSED");
}

void Printer::drawCancelledProgressBar(int width, double fraction, int secondsPassed, int secondsTotal) {
    doDrawProgressBar(
        width,
        min(fraction, 1.0),
        min(secondsPassed, secondsTotal),
        secondsTotal, noLabelColours,
        "CANCELLED");
}

void Printer::drawNotice(const string &notice) {
    cout << col3 << notice << colReset;
    cout.flush();
}

void Printer::drawPrompt(const string &prompt) {
    cout << col1 << prompt << colReset;
    cout.flush();
}

