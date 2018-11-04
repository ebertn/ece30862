#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "pugixml-1.9/src/pugixml.hpp"
#include "Container.h" 
#include "Item.h"
#include "Creature.h"
#include "Trigger.h"
#include "ItemContainer.h"

struct Borders {
    std::string n;
    std::string s;
    std::string e;
    std::string w;
};

class Room : public ItemContainer {
public:
    Room(pugi::xml_node, ItemContainer&);
    virtual ~Room();

    virtual std::string getName();
    virtual std::string getDesc();
    virtual Borders getBorders();
    virtual std::string getType();

private: 
    std::string name;
    std::string status;
    std::string type;
    std::string description;
    
    Borders borders; // 0 = n, 1 = s, 2 = e, 3 = w
    //std::vector<Container> containers;
    //std::vector<Creature> creatures;
    //std::vector<Trigger> triggers;    
};


#endif