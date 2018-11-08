#include "ContainerContainer.h"

using namespace std;

ContainerContainer::ContainerContainer() {}

ContainerContainer::~ContainerContainer() {}

void ContainerContainer::add_container(Container& object){
    this->containers.push_back(object);
} 

void ContainerContainer::print_containers(){
    if (this->containers.size() == 0){
        std::cout << " empty" << std::endl;
        return;
    }

    for (int i = 0; i < this->containers.size(); i++){
        std::cout << std::endl << "    - " << this->containers.at(i).getName() << endl;
        std::cout << "        - Items: " << endl;
        std::cout << "            - ";
        this->containers.at(i).print_items();
        std::cout << "        - Triggers object: " << endl;
        if (this->containers.at(i).triggers.size() > 0){
            std::cout << "            - ";
            cout << this->containers.at(i).triggers.at(0).conditions.at(0).child_value("object") << endl;
        } else {
            std::cout << "            - ";
            cout << "None" << endl;
        }
    }

    std::cout << std::endl;
}

Container& ContainerContainer::at(int i){
    return this->containers.at(i);
}
 
size_t ContainerContainer::size(){
    return this->containers.size();
}

// Returns the removed container
Container ContainerContainer::remove_container(std::string name){
    int index = get_container_index_by_name(name);
    Container removed = Container(at(index));
    containers.erase(containers.begin() + index); 

    return removed;
}

Container* ContainerContainer::get_container_by_name(std::string name){
    for (int i = 0; i < this->containers.size(); i++){
        if (this->containers.at(i).getName() == name){
            return &this->containers.at(i);
        } 
    }
    return NULL;
}

int ContainerContainer::get_container_index_by_name(std::string name){
    for (int i = 0; i < this->containers.size(); i++){
        if (this->containers.at(i).getName() == name){
            return i;
        } 
    }
    throw std::invalid_argument("No such container " + name);
}

bool ContainerContainer::container_exists(std::string name){
    try {
        get_container_index_by_name(name);
    } catch (const std::invalid_argument& s) {
        return false;
    }
    return true;
}