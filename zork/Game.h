#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<string>

class Game {
public:
    Game(std::string);
    virtual ~Game();

private:
    void read_xml(std::string);
};

#endif