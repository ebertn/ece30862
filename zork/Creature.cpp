#include "Creature.h"

Creature::Creature(pugi::xml_node spec){
    this->status = "none";
    for (pugi::xml_node node = spec.first_child(); node; node = node.next_sibling()){
        std::string node_name = node.name();

        if (node_name == "name"){
            this->name = node.child_value();
        } else if (node_name == "status"){
            this->status = node.child_value();
        } else if (node_name == "description"){
            this->description = node.child_value();
        } else if (node_name == "vulnerability"){
            std::string vulnerability = node.child_value();
            this->vulnerabilities.push_back(vulnerability);
        } else if (node_name == "attack"){

        } else if (node_name == "trigger"){

        }
    }
}

Creature::Creature(const Creature& creature){
    this->name = std::string(creature.name);
    this->status = std::string(creature.status);
    this->description = std::string(creature.description);

    for(int i = 0; i < creature.vulnerabilities.size(); i++){
        this->vulnerabilities.push_back(creature.vulnerabilities.at(i));
    }

    // Add triggers and attack
}

Creature::~Creature(){}

std::string Creature::getName(){
    return this->name;
}

std::string Creature::getStatus(){
    return this->status;
}

std::string Creature::getDesc(){
    return this->description;
}