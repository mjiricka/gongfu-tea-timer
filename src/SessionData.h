#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <vector>


using std::vector;



/**
 * Provides info about current Gong Fu Cha session.
 */
class SessionData {
public:
    void addSession(int duration);
    size_t getSessionNum();
    vector<int> getTiming();

private:
    struct SessionEntry {
        int duration;
    };

    vector<SessionEntry> data;
};


#endif /* SESSIONDATA_H */
