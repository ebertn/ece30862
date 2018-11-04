#ifndef OBJECTCONTAINER_H
#define OBJECTCONTAINER_H

#include <string>
#include <vector>
#include <iostream>

#include "Item.h"

// To be used only with Rooms, Items, Containers, and Creatures
template <class T>
class ObjectContainer {
public:
    ObjectContainer();
    ~ObjectContainer();

    virtual void add_object(T&);
    virtual void print_objects();
    virtual T* get_object_by_name(std::string);
    virtual int get_object_index_by_name(std::string);
    virtual size_t size();
    virtual T& at(int i);
    virtual T remove_object(std::string);
    virtual bool object_exists(std::string);

protected:
    std::vector<T> objects;
};

#endif