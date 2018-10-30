#include "ItemContainer.h"

ItemContainer::ItemContainer() {}
ItemContainer::~ItemContainer() {}

void ItemContainer::add(Item& item){
    this->items.push_back(item);
}

void ItemContainer::print(){
    for(auto& item: this->items){
        std::cout << item.getName() << std::endl;
    }
}