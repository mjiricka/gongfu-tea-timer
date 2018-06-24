#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <gio/gio.h>


class Notifier {
public:
    void init();
    void destroy();

    void notify();
    bool isInited();

private:
    GApplication *application;
    bool _isInited = false;
};


#endif /* NOTIFIER_H */
