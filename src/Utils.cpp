#include "Utils.h"

#include <string>

using std::string;
using std::to_string;


string Utils::seconds2string(int seconds) {
    if (seconds >= 60) {
        string minutes = to_string(seconds / 60) + "m";

        int secs = seconds % 60;
        if (secs == 0) {
            return minutes;
        } else {
            return minutes + to_string(secs) + "s";
        }
    } else {
        return std::to_string(seconds) + "s";
    }
}

string Utils::padRight(std::string const &str, size_t s) {
    if (str.size() < s)
        return str + string(s-str.size(), ' ');
    else
        return str;
}

string Utils::padLeft(string const &str, size_t s) {
    if (str.size() < s)
        return string(s-str.size(), ' ') + str;
    else
        return str;
}

