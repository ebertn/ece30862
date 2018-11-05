#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>

#include "Item.h"
#include "ItemContainer.h"

class Container : public ItemContainer {
public:
    Container(pugi::xml_node, ItemContainer& game_items);
    Container(const Container&);
    virtual ~Container();

    virtual std::string getName();
    virtual std::string getStatus();
    virtual std::string getDesc();

    std::string status;

private:
    std::string name;
    std::string description;

    std::vector<std::string> accept;
    std::vector<Trigger> triggers;
};

#endif