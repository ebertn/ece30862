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
            for (pugi::xml_node cond = node.child("condition"); cond; cond = cond.next_sibling("condition")){
                attack.conditions.push_back(cond);
            }
            attack.print = node.child("print").child_value();
            for (pugi::xml_node action = node.child("action"); action; action = action.next_sibling("action")){
                attack.actions.push_back(action.child_value(0));
            }
        } else if (node_name == "trigger"){

        }
    }
}

Creature::Creature(const Creature& creature){
    this->name = std::string(creature.name);
    this->status = std::string(creature.status);
    this->description = std::string(creature.description);
    this->attack.print = creature.attack.print;


    for(int i = 0; i < creature.vulnerabilities.size(); i++){
        this->vulnerabilities.push_back(creature.vulnerabilities.at(i));
    }

    for (int i = 0; i < attack.actions.size(); i++){
        this->attack.actions.push_back(creature.attack.actions.at(i));
    }

    // Add triggers
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