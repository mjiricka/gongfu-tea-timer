#ifndef PRINTER_H
#define PRINTER_H



/**
 * Class for printing into console.
 */
class Printer {
public:
    Printer(bool useColours);

    void drawProgressBar(int width, int secondsPassed, int secondsTotal);
    void redrawProgressBar(int width, int secondsPassed, int secondsTotal);
};


#endif /* PRINTER_H */
