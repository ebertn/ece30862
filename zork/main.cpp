//
// Created by nicke on 10/7/2018.
//
#include<ostream>

#include "ItemContainer.h"
#include "Item.h"

using namespace std;

int main (){
    ItemContainer items;

    for (int i = 0; i < 500; i++){
        //std::string name = "Item ";
        Item a = Item("Item " + std::to_string(i));
        items.add(a);
    }

    items.print();
}