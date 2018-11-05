#include "Container.h"

Container::Container(pugi::xml_node spec, ItemContainer& game_items){
    this->status = "none";
    for (pugi::xml_node node = spec.first_child(); node; node = node.next_sibling()){
        std::string node_name = node.name();

        if (node_name == "name"){
            this->name = node.child_value();
        } else if (node_name == "status"){
            this->status = node.child_value();
        } else if (node_name == "description"){
            this->description = node.child_value();
        } else if (node_name == "item"){
            Item new_item = Item(*(game_items.get_item_by_name(node.child_value())));
            this->add_item(new_item);
        } else if (node_name == "accept"){
            std::string accept_item = node.child_value();
            this->accept.push_back(accept_item);
        } else if (node_name == "trigger"){

        }
    }
}

Container::Container(const Container& container){
    this->name = std::string(container.name);
    this->status = std::string(container.status);
    this->description = std::string(container.description);

    for(int i = 0; i < container.items.size(); i++){
        Item item = Item(container.items.at(i));
        this->add_item(item); 
    }

    for (int i = 0; i < container.accept.size(); i++){
        this->accept.push_back(container.accept.at(i));
    }

    // Add triggers and accept
}

Container::~Container(){}

std::string Container::getName(){
    return this->name;
}

std::string Container::getStatus(){
    return this->status;
}

std::string Container::getDesc(){
    return this->description;
}