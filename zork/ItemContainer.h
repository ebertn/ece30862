#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include <string>
#include <vector>
#include <iostream>

#include "Item.h"

class ItemContainer {
public:
    ItemContainer();
    virtual ~ItemContainer();

    virtual void add(Item&);
    virtual void print();

protected:
    std::vector<Item> items;
};

#endif