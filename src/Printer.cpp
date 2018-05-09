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


// TODO
string col1 = "\033[1;33m";  // yellow
string col2 = "\033[0;32m";  // green
string col3 = "\033[0;30m";  // lightgray
string colReset = "\033[0m";

static const int NUM_LINES = 1;
static const int MAX_TIME_LENGTH = 6;


static void eraseOutput(int numLines) {
    cout << "\033[" << numLines << "A";
}

static void printProgressbar(int length, int done) {
    cout << col1 << "[" << col2;
    for (int i = 0; i < length; ++i) {
        cout << ((i < done) ? "\u25A0" : " ");
    }
    cout << col1 << "]" << colReset;
}


Printer::Printer(bool useColours) {
    // TODO
}

void Printer::drawProgressBar(int width, int secondsPassed, int secondsTotal) {
    assert(secondsPassed <= secondsTotal);
    assert(0 <= secondsPassed);
    assert(0 < secondsTotal);

    string passed = Utils::padLeft(Utils::seconds2string(secondsPassed), MAX_TIME_LENGTH);
    string total = Utils::padRight(Utils::seconds2string(secondsTotal), MAX_TIME_LENGTH);

    cout << passed << "/" << total << " ";
    int done = ceil(width * (static_cast<float>(secondsPassed) / secondsTotal));
    printProgressbar(width, done);
    cout << endl;
}

void Printer::redrawProgressBar(int width, int secondsPassed, int secondsTotal) {
    eraseOutput(NUM_LINES);
    drawProgressBar(width, secondsPassed, secondsTotal);
}

