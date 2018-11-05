#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>

#include "Item.h"
#include "ItemContainer.h"
#include "pugixml-1.9/src/pugixml.hpp"

class Container : public ItemContainer {
public:
    Container(pugi::xml_node, ItemContainer& game_items);
    Container(const Container&);
    virtual ~Container();

    virtual std::string getName();
    virtual std::string getStatus();
    virtual std::string getDesc();

    std::string status;
    std::vector<std::string> accept;

private:
    std::string name;
    std::string description;

    std::vector<Trigger> triggers;
};

#endif