#include "Trigger.h"

using namespace std;

Trigger::Trigger(pugi::xml_node spec) {
    this->command = "";
    for (pugi::xml_node node = spec.first_child(); node; node = node.next_sibling()){
        std::string node_name = node.name();

        if (node_name == "type"){
            this->type = node.child_value();
        } else if (node_name == "command"){
            this->command = node.child_value();
        } else if (node_name == "condition"){
            this->conditions.push_back(node);
        } else if (node_name == "print"){
            string print = node.child_value();
            print = "PRINT " + print;

            this->print_actions.push_back(print);
        } else if (node_name == "action"){
            this->print_actions.push_back(node.child_value());
        } 
    }
}

Trigger::Trigger(const Trigger& trigger){
    this->type = std::string(trigger.type);
    this->command = std::string(trigger.command);

    for(int i = 0; i < trigger.conditions.size(); i++){
        this->conditions.push_back(trigger.conditions.at(i)); 
    }

    for(int i = 0; i < trigger.print_actions.size(); i++){
        this->print_actions.push_back(trigger.print_actions.at(i)); 
    }
}

Trigger::~Trigger() {}