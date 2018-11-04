#include "ItemContainer.h"

ItemContainer::ItemContainer() {}

ItemContainer::~ItemContainer() {}

void ItemContainer::add_item(Item& object){
    this->items.push_back(object);
} 

void ItemContainer::print_items(){
    if (this->items.size() == 0){
        std::cout << "empty" << std::endl;
        return;
    }
    for (int i = 0; i < this->items.size(); i++){
        if (i == 0){
            this->items.at(i).getName();
        } else {
            std::cout << ", " << this->items.at(i).getName();
        }
    }
    std::cout << std::endl;
}

Item& ItemContainer::at(int i){
    return this->items.at(i);
}
 
size_t ItemContainer::size(){
    return this->items.size();
}

// Returns the removed item
Item ItemContainer::remove_item(std::string name){
    int index = get_item_index_by_name(name);
    Item removed = Item(at(index));
    items.erase(items.begin() + index); 

    return removed;
    
}

Item* ItemContainer::get_item_by_name(std::string name){
    for (int i = 0; i < this->items.size(); i++){
        if (this->items.at(i).getName() == name){
            return &this->items.at(i);
        } 
    }
    return NULL;
}

int ItemContainer::get_item_index_by_name(std::string name){
    for (int i = 0; i < this->items.size(); i++){
        if (this->items.at(i).getName() == name){
            return i;
        } 
    }
    throw std::invalid_argument("No such item " + name);
}

bool ItemContainer::item_exists(std::string name){
    try {
        get_item_index_by_name(name);
    } catch (const std::invalid_argument& s) {
        return false;
    }
    return true;
}