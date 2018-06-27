#include "Actions.h"

#include <iostream>
#include <string>
#include <vector>
#include "Settings.h"
#include "App.h"


using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::stoi;


Action::~Action() {
    // Nothing to do...
}

Action* Action::factory(vector<string> &input) {
    if (Volume::isMine(input)) {
        if (input.size() == 2) {
            return new Volume(input[1]);
        } else {
            return new Volume("");
        }
    } if (Info::isMine(input)) {
        return new Info();
    } else {
        return NULL;
    }
}


/********************************************************************
 * Volume
 ********************************************************************/

Volume::Volume(string param) {
    this->param = param;
}

void Volume::set(Settings &settings, int volume) {
    settings.soundVolume = volume;
}

void Volume::print(Settings &settings) {
    cout << settings.soundVolume << endl;
}

bool Volume::isMine(vector<string> &input) {
    return (input.size() > 0) && (input.front() == "volume");
}

void Volume::execute(Settings &settings, App &app) {
    if (param == "") {
        print(settings);
    } else {
        set(settings, stoi(param));
    }
}


/********************************************************************
 * Info
 ********************************************************************/

bool Info::isMine(vector<string> &input) {
    return (input.size() > 0) && (
            input.front() == "i" ||
            input.front() == "info");
}

void Info::execute(Settings &settings, App &app) {
    app.printer.printSession(app.sessionData);
    cout << endl;
}

