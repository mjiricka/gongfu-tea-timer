#include "App.h"

#include <iostream>
#include <stdexcept>
#include "Printer.h"
#include "TonePlayer.h"
#include "ConsoleReader.h"
#include "SessionData.h"
#include "Notifier.h"


using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;


App::App() : printer(true) {
    try {
        tonePlayer.init();
    } catch (runtime_error &) {
        cout << "ERROR: Sound could not be initialized! ";
        cout << "(Check your /etc/libao.conf)" << endl;
        cout << "       Continuing without playing sound!" << endl;
    }

    try {
        notifier.init();
    } catch (runtime_error &) {
        cout << "ERROR: Desktop notifications could not be initialized!" << endl;
    }
}

App::~App() {
    if (tonePlayer.isInited()) tonePlayer.destroy();
    if (notifier.isInited()) notifier.destroy();
}

