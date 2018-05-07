#ifndef CONSOLEREADER_H
#define CONSOLEREADER_H

#include <termios.h>


/**
 * Do non-blocking console IO.
 *
 * Non-blocking IO is enabled during session. When session
 * is running, `getInput` and `isInput` method can be used.
 */
class ConsoleReader {
public:
    void startSession();
    void stopSession();
    bool isInput();
    char getInput();
    bool sessionIsRunning();

private:
    char userInput;
    bool _sessionIsRunning = false;
    termios termSettings;
};


#endif /* CONSOLEREADER_H */
