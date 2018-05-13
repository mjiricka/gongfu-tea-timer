#include "SessionData.h"
#include <vector>


using std::vector;



void SessionData::addSession(int duration) {
    SessionEntry se;
    se.duration = duration;

    data.push_back(se);
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

