#ifndef CONTAINERCONTAINER_H
#define CONTAINERCONTAINER_H

#include <string>
#include <vector>
#include <iostream>

#include "Container.h"

// To be used only with Rooms, Items, Containers, and Creatures
class ContainerContainer {
public:
    ContainerContainer();
    ~ContainerContainer();

    virtual void add_container(Container&);
    virtual void print_containers();
    virtual Container* get_container_by_name(std::string);
    virtual int get_container_index_by_name(std::string);
    virtual size_t size();
    virtual Container& at(int i);
    virtual Container remove_container(std::string);
    virtual bool container_exists(std::string);

protected:
    std::vector<Container> containers;
};

#endif