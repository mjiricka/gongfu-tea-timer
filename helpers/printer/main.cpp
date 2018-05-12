#include <iostream>
#include <thread>
#include <chrono>
#include <Printer.h>

using std::cout;
using std::endl;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;


int main() {
    Printer printer(true);

    const milliseconds sleepTime{100};
    const int total = 76;

    printer.drawPausedProgressBar(80, .25, 20, total);

    printer.drawCancelledProgressBar(80, .5, 20, total);

    cout << endl;

    for (int i = 1; i <= total; ++i) {
        if (i != 1) printer.eraseOutput(1);

        double fraction = static_cast<double>(i) / total;
        printer.drawProgressBar(80, fraction, i, total);
        printer.drawNotice(" [p - pause, c - cancel]> ");

        if (i < total) {
            sleep_for(sleepTime);
        }
    }

    cout << endl;
    printer.eraseOutput(1);

    return 0;
}

