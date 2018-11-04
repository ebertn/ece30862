#include "Item.h"

using namespace std;

Item::Item(pugi::xml_node spec){
    this->status = "none";
    for (pugi::xml_node node = spec.first_child(); node; node = node.next_sibling()){
        std::string node_name = node.name();

        if (node_name == "name"){
            this->name = node.child_value();
        } else if (node_name == "status"){
            this->status = node.child_value();
        } else if (node_name == "description"){
            this->description = node.child_value();
        } else if (node_name == "writing"){
            this->writing = node.child_value();
        } else if (node_name == "turnon"){

        } else if (node_name == "trigger"){

        }
    }
}

Item::Item(const Item& item){
    this->name = std::string(item.name);
    this->status = std::string(item.status);
    this->description = std::string(item.description);
    this->writing = std::string(item.writing);
    // Add turnon and triggers
}

Item::~Item(){}

std::string Item::getName(){
    return this->name;
}
std::string Item::getStatus(){
    return this->status;
}
std::string Item::getDesc(){
    return this->description;
}
std::string Item::getWriting(){
    return this->writing;
}