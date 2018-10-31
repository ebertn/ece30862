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
    std::vector<Room> rooms;

    virtual void read_xml();
    virtual void handle_input();
    virtual void create_object(pugi::xml_node);
    static std::string get_single_param(std::string);
    static str_tuple get_two_params(std::string, std::string);
};

#endif