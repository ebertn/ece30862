#include "Room.h" 

using namespace pugi;

Room::Room(pugi::xml_node spec, 
            ItemContainer& game_items, 
            ContainerContainer& game_containers,
            CreatureContainer& game_creatures){   
    this->type = "regular";

    for (pugi::xml_node node = spec.first_child(); node; node = node.next_sibling()){
        std::string node_name = node.name();
        if (node_name == "name"){
            this->name = node.child_value();
        } else if (node_name == "description"){
            this->description = node.child_value();
        } else if (node_name == "status"){
            this->status = node.child_value();
        } else if (node_name == "type"){
            this->type = node.child_value();
        } else if (node_name == "border"){

            std::string dir = node.child_value("direction");
            if (dir == "north"){
                this->borders.n = node.child_value("name");
            } else if(dir == "south"){
                this->borders.s = node.child_value("name");
            } else if (dir == "east"){
                this->borders.e = node.child_value("name");
            } else if (dir == "west"){
                this->borders.w = node.child_value("name");
            }

        } else if (node_name == "container"){
            Container new_container = Container(*(game_containers.get_container_by_name(node.child_value())));
            containers.add_container(new_container);          
        } else if (node_name == "item"){
            Item new_item = Item(*(game_items.get_item_by_name(node.child_value())));
            this->add_item(new_item);
        } else if (node_name == "creature"){
            Creature new_creature = Creature(*(game_creatures.get_creature_by_name(node.child_value())));
            this->creatures.add_creature(new_creature);       
        } else if (node_name == "trigger"){
            Trigger trigger = Trigger(node);
            this->triggers.push_back(trigger); 
        }
    }
}

Room::~Room(){
    //delete this->borders;
}



std::string Room::getName(){
    return this->name;
}

std::string Room::getDesc(){
    return this->description;
}

Borders Room::getBorders(){
    return this->borders;
}

std::string Room::getType(){
    return this->type;
}