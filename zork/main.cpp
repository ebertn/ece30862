//
// Created by nicke on 10/7/2018.
//
#include<ostream>

#include "Game.h"
#include "ObjectContainer.h"
#include "Item.h"

using namespace std;

int main (){
    // ItemContainer items;

    // for (int i = 0; i < 500; i++){
    //     //std::string name = "Item ";
    //     Item a = Item("Item " + std::to_string(i));
    //     items.add(a);
    // }

    // items.print();

    // while(1){
    //     Game game("hello");
    //     game.start();
    // }

    Game game("./xml_files/sample.txt.xml");
    game.start();
}