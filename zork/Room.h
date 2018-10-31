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

class Room : public ItemContainer {
public:
    Room(pugi::xml_node);
    virtual ~Room();  

private: 
    std::string name;
    std::string status;
    std::string type;
    std::string description;
    
    Room* borders; // 0 = n, 1 = s, 2 = e, 3 = w
    std::vector<Container> containers;
    std::vector<Creature> creatures;
    std::vector<Trigger> triggers;    
};

#endif