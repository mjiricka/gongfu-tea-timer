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

    void drawProgressBar(int width, int secondsPassed, int secondsTotal);
    void drawPausedProgressBar(int width, int secondsPassed, int secondsTotal);
    void drawCancelledProgressBar(int width, int secondsPassed, int secondsTotal);

    void drawNotice(const string &notice);
};


#endif /* PRINTER_H */
