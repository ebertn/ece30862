#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include "pugixml-1.9/src/pugixml.hpp"
#include "Trigger.h"

class Item {
public:
    Item(pugi::xml_node);
    Item(const Item&);
    virtual ~Item();

    virtual std::string getName();
    virtual std::string getStatus();
    virtual std::string getDesc();
    virtual std::string getWriting();

private:
    std::string name;
    std::string status;
    std::string description;
    std::string writing;
    std::string turnon_print;
    std::string turnon_action;
    
    std::vector<Trigger> triggers;   
};

#endif