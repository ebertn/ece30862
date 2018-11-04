#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include <string>
#include <vector>
#include <iostream>

#include "Item.h"

// To be used only with Rooms, Items, Containers, and Creatures
class ItemContainer {
public:
    ItemContainer();
    ~ItemContainer();

    virtual void add_item(Item&);
    virtual void print_items();
    virtual Item* get_item_by_name(std::string);
    virtual int get_item_index_by_name(std::string);
    virtual size_t size();
    virtual Item& at(int i);
    virtual Item remove_item(std::string);
    virtual bool item_exists(std::string);

protected:
    std::vector<Item> items;
};

#endif