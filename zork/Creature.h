#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>
#include <iostream>

#include "Trigger.h"
#include "pugixml-1.9/src/pugixml.hpp"

struct Attack {
    std::vector<pugi::xml_node> conditions;
    std::string print;
    std::vector<std::string> actions;
};

class Creature {
public:
    Creature(pugi::xml_node);
    Creature(const Creature&);
    virtual ~Creature();

    virtual std::string getName();
    virtual std::string getStatus();
    virtual std::string getDesc();

    std::string status;
    std::vector<std::string> vulnerabilities;
    Attack attack;
    std::vector<Trigger> triggers;


private:
    std::string name;
    std::string description;
};

#endif