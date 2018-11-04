#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "pugixml-1.9/src/pugixml.hpp"
#include "Container.h" 
#include "Item.h"
#include "Creature.h"
#include "Trigger.h"
#include "ObjectContainer.h"

struct Borders {
    std::string n;
    std::string s;
    std::string e;
    std::string w;
};

class Room : public ObjectContainer<Item> {
public:
    Room(pugi::xml_node, ObjectContainer<Item>&);
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
    //ObjectContainer<Container> containers;
    //ObjectContainer<Creature> creatures;
    //ObjectContainer<Trigger> triggers;    
};


#endif