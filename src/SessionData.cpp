#include "SessionData.h"
#include <cassert>
#include <vector>


using std::vector;
using std::chrono::system_clock;
using std::chrono::seconds;
using std::chrono::duration_cast;


SessionData::SessionData() {
    currentSession = Session();
}

void SessionData::addSession(seconds duration, system_clock::time_point startTime) {
    Steep steep;
    steep.duration = duration;
    steep.startTime = startTime;

    currentSession.steeps.push_back(steep);
}

size_t SessionData::getSessionNum() {
    return currentSession.steeps.size();
}

vector<seconds> SessionData::getTiming() {
    auto v = vector<seconds>();

    for (auto it = currentSession.steeps.begin(); it != currentSession.steeps.end(); it++) {
        v.push_back(it->duration);
    }

    return v;
}

vector<seconds> SessionData::getTimeDistances() {
    auto v = vector<seconds>();

    auto it = currentSession.steeps.begin();
    auto prev = it;

    while (++it != currentSession.steeps.end()) {
        // TODO: Maybe also add steeping length?
        v.push_back(duration_cast<seconds>(it->startTime - prev->startTime));
        prev = it;
    }

    return v;
}

seconds SessionData::getSessionLength() {
    return duration_cast<seconds>(system_clock::now() - getSessionStart());
}

system_clock::time_point SessionData::getSessionStart() {
    assert(currentSession.steeps.size() > 0);

    return currentSession.steeps.front().startTime;
}

system_clock::time_point SessionData::getCurrentSessionEnd() {
    assert(currentSession.steeps.size() > 0);
    auto dataLast = (currentSession.steeps.end() - 1);
    return (dataLast->startTime + dataLast->duration);
}

void SessionData::deleteSession(size_t sessionNum) {
    assert(sessionNum >= 0 && sessionNum < currentSession.steeps.size());

    currentSession.steeps.erase(currentSession.steeps.begin()+sessionNum);
}

void SessionData::setTitle(string title) {
    currentSession.title = title;
}

string SessionData::getTitle() {
    return currentSession.title;
}

