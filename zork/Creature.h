#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>

#include "Trigger.h"
#include "pugixml-1.9/src/pugixml.hpp"

class Creature {
public:
    Creature(pugi::xml_node);
    Creature(const Creature&);
    virtual ~Creature();

    virtual std::string getName();
    virtual std::string getStatus();
    virtual std::string getDesc();

    std::string status;

private:
    std::string name;
    std::string description;
    std::string attack;

    std::vector<std::string> vulnerabilities;
    std::vector<Trigger> triggers;
};

#endif