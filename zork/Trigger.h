#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>
#include <vector>

class Trigger {
public:
    Trigger();
    virtual ~Trigger();

private:
    std::string type;
    std::string command;

    std::vector<std::string> print;
    std::vector<std::string> action;
    std::vector<std::string> conditions;
};

#endif