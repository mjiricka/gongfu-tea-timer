#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <vector>
#include <chrono>
#include <string>


using std::vector;
using std::string;
using std::chrono::system_clock;
using std::chrono::seconds;


/**
 * Provides info about current Gong Fu Cha session.
 */
class SessionData {
public:
    SessionData();

    void addSession(seconds duration, system_clock::time_point startTime);
    size_t getSessionNum();
    vector<seconds> getTiming();
    vector<seconds> getTimeDistances();
    seconds getSessionLength();
    system_clock::time_point getSessionStart();
    system_clock::time_point getCurrentSessionEnd();
    void deleteSession(size_t sessionNum);
    void setTitle(string title);
    string getTitle();

private:
    struct Steep {
        seconds duration;
        system_clock::time_point startTime;
    };

    struct Session {
        string title;
        vector<Steep> steeps;
    };

    Session currentSession;
};


#endif /* SESSIONDATA_H */
