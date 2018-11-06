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
            this->turnon_action = node.child("action").child_value();
            this->turnon_print = node.child("print").child_value();
        } else if (node_name == "trigger"){
            Trigger trigger = Trigger(node);
            this->triggers.push_back(trigger);
        }
    }
}

Item::Item(const Item& item){
    this->name = std::string(item.name);
    this->status = std::string(item.status);
    this->description = std::string(item.description);
    this->writing = std::string(item.writing);
    this->turnon_action = std::string(item.turnon_action);
    this->turnon_print = std::string(item.turnon_print);

    for(int i = 0; i < item.triggers.size(); i++){
        Trigger trigger = item.triggers.at(i);
        this->triggers.push_back(trigger);
    }
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
std::string Item::getTurnonAction(){
    return this->turnon_action;
}
std::string Item::getTurnonPrint(){
    return this->turnon_print;
}