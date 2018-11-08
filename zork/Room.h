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
#include "CreatureContainer.h"
#include "ContainerContainer.h"

struct Borders {
    std::string n;
    std::string s;
    std::string e;
    std::string w;
};

class Room : public ItemContainer {
public:
    Room(pugi::xml_node, ItemContainer&, ContainerContainer&, CreatureContainer&);
    virtual ~Room();

    virtual std::string getName();
    virtual std::string getDesc();
    virtual Borders getBorders();
    virtual std::string getType();
    virtual void print_room();

    ContainerContainer containers;
    CreatureContainer creatures;
    Borders borders; // 0 = n, 1 = s, 2 = e, 3 = w

    std::string status;
    std::vector<Trigger> triggers;    

private: 
    std::string name;
    std::string type;
    std::string description;
};


#endif