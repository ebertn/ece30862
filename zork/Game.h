#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include "pugixml-1.9/src/pugixml.hpp"
#include "Room.h"

struct str_tuple {
    std::string param1;
    std::string param2;
};

class Game {
public:
    Game(std::string);
    virtual ~Game();

    virtual void start();

private:

    std::string filename;
    int game_running; // 1 = running, 0 = GAME OVER
    std::vector<Room> rooms;
    Room* cur_room;

    virtual void read_xml();
    virtual void handle_input();
    virtual void create_object(pugi::xml_node);
    virtual void print_rooms();
    virtual void move(std::string);
    virtual Room* get_room_by_name(std::string);
    virtual void enter_room(std::string);
    virtual void game_over();

    static std::string get_single_param(std::string);
    static str_tuple get_two_params(std::string, std::string);
};

#endif