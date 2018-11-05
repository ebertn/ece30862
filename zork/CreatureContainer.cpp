#include "CreatureContainer.h"

CreatureContainer::CreatureContainer() {}

CreatureContainer::~CreatureContainer() {}

void CreatureContainer::add_creature(Creature& object){
    this->creatures.push_back(object);
} 

void CreatureContainer::print_creatures(){
    if (this->creatures.size() == 0){
        std::cout << "empty" << std::endl;
        return;
    }
    for (int i = 0; i < this->creatures.size(); i++){
        if (i == 0){
            this->creatures.at(i).getName();
        } else {
            std::cout << ", " << this->creatures.at(i).getName();
        }
    }
    std::cout << std::endl;
}

Creature& CreatureContainer::at(int i){
    return this->creatures.at(i);
}
 
size_t CreatureContainer::size(){
    return this->creatures.size();
}

// Returns the removed creature
Creature CreatureContainer::remove_creature(std::string name){
    int index = get_creature_index_by_name(name);
    Creature removed = Creature(at(index));
    creatures.erase(creatures.begin() + index); 

    return removed;
}

Creature* CreatureContainer::get_creature_by_name(std::string name){
    for (int i = 0; i < this->creatures.size(); i++){
        if (this->creatures.at(i).getName() == name){
            return &this->creatures.at(i);
        } 
    }
    return NULL;
}

int CreatureContainer::get_creature_index_by_name(std::string name){
    for (int i = 0; i < this->creatures.size(); i++){
        if (this->creatures.at(i).getName() == name){
            return i;
        } 
    }
    throw std::invalid_argument("No such creature " + name);
}

bool CreatureContainer::creature_exists(std::string name){
    try {
        get_creature_index_by_name(name);
    } catch (const std::invalid_argument& s) {
        return false;
    }
    return true;
}