#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <vector>
#include <chrono>


using std::vector;
using std::chrono::system_clock;
using std::chrono::seconds;


/**
 * Provides info about current Gong Fu Cha session.
 */
class SessionData {
public:
    void addSession(seconds duration, system_clock::time_point startTime);
    size_t getSessionNum();
    vector<seconds> getTiming();
    vector<seconds> getTimeDistances();
    seconds getSessionLength();
    system_clock::time_point getSessionStart();
    system_clock::time_point getCurrentSessionEnd();
    void deleteSession(size_t sessionNum);

private:
    struct SessionEntry {
        seconds duration;
        system_clock::time_point startTime;
    };

    vector<SessionEntry> data;
};


#endif /* SESSIONDATA_H */
