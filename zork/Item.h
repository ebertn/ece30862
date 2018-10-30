#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include "Trigger.h"

class Item {
public:
    Item(std::string);
    virtual ~Item();

    std::string getName();

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