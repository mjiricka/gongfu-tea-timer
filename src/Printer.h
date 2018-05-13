#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include "SessionData.h"


using std::string;


/**
 * Class for printing into console.
 */
class Printer {
public:
    Printer(bool useColours);

    void eraseOutput(int numLines);
    void clearLine();

    void drawProgressBar(int width, double fraction, int secondsPassed, int secondsTotal);
    void drawPausedProgressBar(int width, double fraction, int secondsPassed, int secondsTotal);
    void drawCancelledProgressBar(int width, double fraction, int secondsPassed, int secondsTotal);

    void drawNotice(const string &notice);
    void drawPrompt(const string &prompt);

    void printSession(SessionData &sessionData);
};


#endif /* PRINTER_H */
