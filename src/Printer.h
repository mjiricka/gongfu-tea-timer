#ifndef PRINTER_H
#define PRINTER_H

#include <string>

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
};


#endif /* PRINTER_H */
