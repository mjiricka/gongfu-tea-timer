#include "TerminalUtils.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <cassert>


bool TerminalUtils::isAppRunInInteractiveTerminal() {
    winsize ws;

    return (
        ioctl(STDIN_FILENO , TIOCGWINSZ, &ws) == 0 &&
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0
        //ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == 0
    );
}

unsigned int TerminalUtils::getTerminalWidth() {
    assert(TerminalUtils::isAppRunInInteractiveTerminal());

    winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return ws.ws_col;
}

