#include "SessionData.h"
#include <vector>


using std::vector;
using std::chrono::system_clock;
using std::chrono::seconds;
using std::chrono::duration_cast;


void SessionData::addSession(int duration, system_clock::time_point startTime) {
    SessionEntry se;
    se.duration = duration;
    se.startTime = startTime;

    data.push_back(se);

    if (data.size() == 1) {
        sessionStart = startTime;
    }
}

size_t SessionData::getSessionNum() {
    return data.size();
}

vector<int> SessionData::getTiming() {
    auto v = vector<int>();

    for (auto it = data.begin(); it != data.end(); it++) {
        v.push_back(it->duration);
    }

    return v;
}

vector<seconds> SessionData::getTimeDistances() {
    auto v = vector<seconds>();

    auto it = data.begin();
    auto prev = it;

    while (++it != data.end()) {
        v.push_back(duration_cast<seconds>(it->startTime - prev->startTime));
        prev = it;
    }

    return v;
}

seconds SessionData::getSessionLength() {
    return duration_cast<seconds>(system_clock::now() - sessionStart);
}

