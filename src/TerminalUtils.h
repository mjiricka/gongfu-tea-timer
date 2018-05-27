#ifndef TERMINALUTILS_H
#define TERMINALUTILS_H

/**
 * Groups functions for getting info about terminal.
 */
class TerminalUtils {
public:
    static bool isAppRunInInteractiveTerminal();
    static unsigned int getTerminalWidth();
};


#endif /* TERMINALUTILS_H */

