#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>

#include "Trigger.h"

class Creature {
public:
    Creature();
    virtual ~Creature();

    virtual std::string getName();
    virtual std::string getStatus();
    virtual std::string getDesc();
    virtual std::string getAttack();

    std::string status;

private:
    std::string name;
    std::string description;
    std::string attack;

    std::vector<std::string> vulnerabilities;
    std::vector<Trigger> triggers;
};

#endif