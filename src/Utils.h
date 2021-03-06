#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>
#include <vector>

using std::string;
using std::chrono::system_clock;
using std::vector;


/**
 * Various utility functions.
 */
class Utils {
public:
    static string seconds2string(int seconds);
    static string padRight(std::string const &str, size_t s);
    static string padLeft(string const &str, size_t s);

    static void ltrim(std::string &s);
    static void rtrim(std::string &s);
    static void trim(std::string &s);

    static string getTime(system_clock::time_point tp);

    static vector<string> split(const string &str, const string &delim);
    static void printStrVector(const vector<string> &data);
};

#endif /* UTILS_H */
