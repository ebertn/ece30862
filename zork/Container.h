#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>

#include "Item.h"
#include "ObjectContainer.h"

class Container : public ObjectContainer<Item> {
public:
    Container();
    virtual ~Container();

private:
    std::string name;
    std::string status;
    std::string description;

    std::vector<std::string> accept;
    ObjectContainer<Trigger> triggers;
};

#endif