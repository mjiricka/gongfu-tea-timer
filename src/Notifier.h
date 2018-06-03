#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <gio/gio.h>


class Notifier {
public:
    Notifier();
    ~Notifier();

    void notify();

private:
    GApplication *application;
};


#endif /* NOTIFIER_H */
