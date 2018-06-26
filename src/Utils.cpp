#include "Utils.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

using std::string;
using std::vector;
using std::time_t;
using std::remove;
using std::to_string;
using std::chrono::system_clock;
using std::cout;
using std::endl;


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

// Taken from:
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> Utils::split(const string &str, const string &delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;

    do {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());

    return tokens;
}

void Utils::printStrVector(const vector<string> &data) {
    for (auto i = data.begin(); i != data.end(); ++i) {
        cout << "[" << *i << "] ";
    }
    cout << endl;
}

