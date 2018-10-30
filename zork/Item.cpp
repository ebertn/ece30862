#include "Item.h"

Item::Item(std::string name) : name(name) {}
Item::~Item(){}

std::string Item::getName(){
    return this->name;
}