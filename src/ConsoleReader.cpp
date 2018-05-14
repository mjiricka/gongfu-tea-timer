#include "ConsoleReader.h"

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <cassert>


// Inspiration: https://gist.github.com/whyrusleeping/3983293


static void setKeyboardNonBlock(termios *initialSettings)
{
    struct termios new_settings;
    tcgetattr(STDIN_FILENO, initialSettings);

    new_settings = *initialSettings;
    new_settings.c_lflag &= ~(ICANON | ECHO | ISIG);
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

static void restoreKeyboardBlocking(termios *initialSettings)
{
    tcsetattr(STDIN_FILENO, TCSANOW, initialSettings);
}

void ConsoleReader::startSession() {
    assert(_sessionIsRunning == false);

    setKeyboardNonBlock(&termSettings);
    userInput = 0;
    _sessionIsRunning = true;
}

void ConsoleReader::stopSession() {
    assert(_sessionIsRunning == true);

    while (getchar() > 0);  // Clear CIN buffer.
    restoreKeyboardBlocking(&termSettings);
    _sessionIsRunning = false;
}

bool ConsoleReader::isInput() {
    assert(_sessionIsRunning == true);

    if (userInput > 0) {
        return true;
    } else {
        userInput = getchar();
        return userInput > 0;
    }
}

char ConsoleReader::getInput() {
    assert(_sessionIsRunning == true);

    char ui = userInput;
    userInput = 0;
    return ui;
}

bool ConsoleReader::sessionIsRunning() {
    return _sessionIsRunning;
}

