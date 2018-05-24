#include <iostream>
#include <string>
#include <argh.h>
#include "Settings.h"
#include "TeaSession.h"


using std::cout;
using std::endl;
using std::string;


const string VERSION="0.1";


void loadSettings(Settings &settings, argh::parser &cmdl) {
    if (cmdl[{ "-s", "--silent" }]) {
        settings.playSound = false;
    }
}


int main(int argc, char *argv[]) {
    argh::parser cmdl(argv);

    if (cmdl[{ "-v", "--version" }]) {
        // TODO
        cout << "version: " << VERSION << endl;
    }
    else if (cmdl[{ "-h", "--help" }]) {
        // TODO
        cout << "USAGE: " << argv[0] << endl;
    } else {
        Settings settings;
        loadSettings(settings, cmdl);
        //cout << "USAGE: " << settings.playSound << endl;
        TeaSession ts(settings);
        ts.run();
    }

    return EXIT_SUCCESS;
}

