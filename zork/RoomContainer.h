#ifndef ROOMCONTAINER_H
#define ROOMCONTAINER_H

#include <string>
#include <vector>
#include <iostream>

#include "Room.h"

// To be used only with Rooms, Items, Containers, and Creatures
class RoomContainer {
public:
    RoomContainer();
    ~RoomContainer();

    virtual void add_room(Room&);
    virtual void print_rooms();
    virtual Room* get_room_by_name(std::string);
    virtual int get_room_index_by_name(std::string);
    virtual size_t size();
    virtual Room& at(int i);
    virtual Room remove_room(std::string);
    virtual bool room_exists(std::string);

protected:
    std::vector<Room> rooms;
};

#endif