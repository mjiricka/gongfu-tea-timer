#include "Utils.h"

#include <algorithm>
#include <functional>
#include <string>
#include <chrono>
#include <ctime>

using std::string;
using std::time_t;
using std::remove;
using std::to_string;
using std::chrono::system_clock;


// TODO: longFormat is not used now?
string Utils::seconds2string(int numSeconds, bool longFormat) {
    if (numSeconds == 0) {
        return "0s";
    } else {
        int hours = numSeconds / 3600;
        int minutes = (numSeconds % 3600) / 60;
        int seconds = numSeconds % 60;

        string hoursStr = hours == 0 ? "" : to_string(hours) + "h";
        string minutesStr = (minutes == 0) && (hours == 0) ? "" : to_string(minutes) + "m";
        string secondsStr = (seconds == 0 || hours > 0) ? "" : to_string(seconds) + "s";

        string sep = longFormat ? " " : "";
        string result = hoursStr + sep + minutesStr + sep + secondsStr;

        Utils::trim(result);

        return result;
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

void Utils::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
void Utils::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
void Utils::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

string Utils::getTime(system_clock::time_point tp) {
    std::time_t t = system_clock::to_time_t(tp);
    tm *timeinfo = localtime(&t);
    char buffer[80];

    strftime(buffer, 80, "%R", timeinfo);

    return string(buffer);
}

