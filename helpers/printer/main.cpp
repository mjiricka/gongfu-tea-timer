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

    for (int i = 1; i <= total; ++i) {
        if (i == 1) {
            printer.drawProgressBar(80, i, total);
        } else {
            printer.redrawProgressBar(80, i, total);
            sleep_for(sleepTime);
        }
    }

    return 0;
}

