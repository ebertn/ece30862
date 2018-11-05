#ifndef CREATURECONTAINER_H
#define CREATURECONTAINER_H

#include <string>
#include <vector>
#include <iostream>

#include "Creature.h"

// To be used only with Rooms, Items, Containers, and Creatures
class CreatureContainer {
public:
    CreatureContainer();
    ~CreatureContainer();

    virtual void add_creature(Creature&);
    virtual void print_creatures();
    virtual Creature* get_creature_by_name(std::string);
    virtual int get_creature_index_by_name(std::string);
    virtual size_t size();
    virtual Creature& at(int i);
    virtual Creature remove_creature(std::string);
    virtual bool creature_exists(std::string);

protected:
    std::vector<Creature> creatures;
};

#endif