#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <sys/ioctl.h>


// Good blog post: https://dev.to/pauljlucas/getting-the-terminal-width-in-c


unsigned get_term_width() {
    winsize ws;
    if ( ioctl( STDIN_FILENO , TIOCGWINSZ, &ws ) != 0 &&
        ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws ) != 0 &&
        ioctl( STDERR_FILENO, TIOCGWINSZ, &ws ) != 0 ) {
        fprintf( stderr, "ioctl() failed (%d): %s\n", errno, strerror( errno ) );
        return 0;
    }

    return ws.ws_col;
}

int main() {
    std::string input;

    do {
        int width = get_term_width();
        std::cout << "Width = " << width << std::endl;

        std::cin >> input;
    } while (input != "q");
}

