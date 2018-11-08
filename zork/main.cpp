//
// Created by nicke on 10/7/2018.
//
#include<ostream>

#include "Game.h"
#include "ItemContainer.h"
#include "Item.h"

using namespace std;

int main (int argc, char** argv){
    if (argc != 2){
        cout << "Wrong number of arguments" << endl;
        return EXIT_FAILURE;
    }
    
    Game game(argv[1]);
    game.start();

    return EXIT_SUCCESS;
}