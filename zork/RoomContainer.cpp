#include "RoomContainer.h"

using namespace std;

RoomContainer::RoomContainer() {}

RoomContainer::~RoomContainer() {}

void RoomContainer::add_room(Room& object){
    this->rooms.push_back(object);
} 

void RoomContainer::print_rooms(){
    if (this->rooms.size() == 0){
        std::cout << "empty" << std::endl;
        return;
    }
    for (int i = 0; i < this->rooms.size(); i++){
        if (i == 0){
            this->rooms.at(i).getName();
        } else {
            std::cout << ", " << this->rooms.at(i).getName();
        }
    }
    std::cout << std::endl;
}

Room& RoomContainer::at(int i){
    return this->rooms.at(i);
}
 
size_t RoomContainer::size(){
    return this->rooms.size();
}

// Returns the removed room
Room RoomContainer::remove_room(std::string name){
    int index = get_room_index_by_name(name);
    Room removed = Room(at(index));
    rooms.erase(rooms.begin() + index); 

    return removed;
}

Room* RoomContainer::get_room_by_name(std::string name){
    for (int i = 0; i < this->rooms.size(); i++){
        if (this->rooms.at(i).getName() == name){
            return &this->rooms.at(i);
        } 
    }
    return NULL;
}

int RoomContainer::get_room_index_by_name(std::string name){
    for (int i = 0; i < this->rooms.size(); i++){
        if (this->rooms.at(i).getName() == name){
            return i;
        } 
    }
    throw std::invalid_argument("No such room " + name);
}

bool RoomContainer::room_exists(std::string name){
    try {
        get_room_index_by_name(name);
    } catch (const std::invalid_argument& s) {
        return false;
    }
    return true;
}