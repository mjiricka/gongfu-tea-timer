#ifndef APP_H
#define APP_H

#include "Printer.h"
#include "TonePlayer.h"
#include "ConsoleReader.h"
#include "SessionData.h"
#include "Notifier.h"


/**
 * All objects used by `TeaSession` to make the app run.
 */

struct App {
    App();
    ~App();

    Printer printer;
    TonePlayer tonePlayer;
    ConsoleReader consoleReader;
    SessionData sessionData;
    Notifier notifier;
};



#endif /* APP_H */
