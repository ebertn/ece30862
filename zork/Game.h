#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include "pugixml-1.9/src/pugixml.hpp"
#include "Room.h"
#include "Item.h"
#include "ItemContainer.h"

struct str_tuple {
    std::string param1;
    std::string param2;
};

class Game {
public:
    Game(std::string);
    virtual ~Game();

    virtual void start();

protected:

    std::string filename;
    int game_running; // 1 = running, 0 = GAME OVER
    std::vector<Room> rooms;
    ItemContainer items; // List of potential items. Used to make copies.
    ItemContainer player_inv;

    Room* cur_room;

    virtual void read_xml();
    virtual void handle_input();
    virtual void create_object(pugi::xml_node);
    virtual void print_rooms();
    virtual void print_items();
    virtual void move(std::string);
    virtual Room* get_room_by_name(std::string);
    virtual void enter_room(std::string);
    virtual void take(std::string);
    virtual void drop(std::string);
    virtual void read(std::string);
    virtual void add(std::string object, std::string owner);
    virtual void game_over();
    virtual void print_inv();

    static std::string get_single_param(std::string);
    static str_tuple get_two_params(std::string, std::string);
};

#endif