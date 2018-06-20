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
    void addSession(int duration, system_clock::time_point startTime);
    size_t getSessionNum();
    vector<int> getTiming();
    vector<seconds> getTimeDistances();
    seconds getSessionLength();
    system_clock::time_point getSessionStart();
    system_clock::time_point getCurrentSessionEnd();

private:
    struct SessionEntry {
        int duration;
        system_clock::time_point startTime;
    };

    vector<SessionEntry> data;
    system_clock::time_point sessionStart;
};


#endif /* SESSIONDATA_H */
