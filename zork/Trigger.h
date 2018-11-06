#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>
#include <vector>
#include <iostream>
#include "pugixml-1.9/src/pugixml.hpp"

class Trigger {
public:
    Trigger(pugi::xml_node);
    Trigger(const Trigger&);
    virtual ~Trigger();

    std::string command;
    std::string type;

    std::vector<std::string> print_actions;
    std::vector<pugi::xml_node> conditions;
};

#endif