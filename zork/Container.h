#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>

#include "Item.h"
#include "ItemContainer.h"

class Container : public ItemContainer {
public:
    Container();
    virtual ~Container();

private:
    std::string name;
    std::string status;
    std::string description;

    std::vector<std::string> accept;
    std::vector<Trigger> triggers;
};

#endif