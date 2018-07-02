#ifndef ACTIONS_H
#define ACTIONS_H

#include <string>
#include <vector>
#include "Settings.h"
#include "App.h"


using std::string;
using std::vector;


/**
 * Interface for actions.
 */
class Action {
public:
    static Action* factory(vector<string> &input);
    virtual void execute(Settings &settings, App &app) = 0;
    virtual ~Action();
};


class Volume : public Action {
public:
    static bool isMine(vector<string> &input);

    Volume(string param);

    virtual void execute(Settings &settings, App &app);

private:
    string param;

    void set(Settings &settings, int volume);
    void print(Settings &settings);
};


class Info : public Action {
public:
    static bool isMine(vector<string> &input);

    virtual void execute(Settings &settings, App &app);
};


class Delete : public Action {
public:
    static bool isMine(vector<string> &input);

    Delete(string secondParam);

    virtual void execute(Settings &settings, App &app);

private:
    string param;
};


class Reset : public Action {
public:
    static bool isMine(vector<string> &input);

    virtual void execute(Settings &settings, App &app);
};


#endif /* ACTIONS_H */

