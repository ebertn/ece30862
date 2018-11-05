#include "Creature.h"

Creature::Creature(){}
Creature::~Creature(){}

std::string Creature::getName(){
    return this->name;
}

std::string Creature::getStatus(){
    return this->status;
}

std::string Creature::getDesc(){
    return this->description;
}

std::string Creature::getAttack(){
    return this->attack;
}