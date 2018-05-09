#ifndef UTILS_H
#define UTILS_H

#include <string>

using std::string;


/**
 * Various utility functions.
 */
class Utils {
public:
    static string seconds2string(int seconds);
    static string padRight(std::string const &str, size_t s);
    static string padLeft(string const &str, size_t s);
};

#endif /* UTILS_H */
