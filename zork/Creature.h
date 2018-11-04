#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>

#include "Trigger.h"

class Creature {
public:
    Creature();
    virtual ~Creature();

private:
    std::string name;
    std::string status;
    std::string description;
    std::string attack;

    std::vector<std::string> vulnerabilities;
    std::vector<Trigger> triggers;
};

#endif