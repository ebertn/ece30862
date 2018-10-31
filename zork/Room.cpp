#include "Room.h"

Room::Room(){
    this->borders = new Room[4];
}

Room::~Room(){
    delete this->borders;
}