#ifndef TEA_SESSION_H
#define TEA_SESSION_H

#include "Settings.h"


/**
 * TODO
 */
class TeaSession {
public:
    TeaSession(Settings &settings);
    void run();
private:
    Settings settings;
};


#endif /* TEA_SESSION_H */
