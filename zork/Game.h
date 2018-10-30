#include<iostream>
#include<string>

class Game {
public:
    Game(std::string);
    ~Game();

private:
    void read_xml(std::string);
    void add();
}