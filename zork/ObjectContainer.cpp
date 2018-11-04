#include "ObjectContainer.h"

template <class T>
ObjectContainer<T>::ObjectContainer() {}

template <class T>
ObjectContainer<T>::~ObjectContainer() {}

template <class T>
void ObjectContainer<T>::add_object(T& object){
    this->objects.push_back(object);
} 

template <class T>
void ObjectContainer<T>::print_objects(){
    if (this->objects.size() == 0){
        std::cout << "empty" << std::endl;
        return;
    }
    for (int i = 0; i < this->objects.size(); i++){
        if (i == 0){
            this->objects.at(i).getName();
        } else {
            std::cout << ", " << this->objects.at(i).getName();
        }
    }
    std::cout << std::endl;
}

template <class T>
T& ObjectContainer<T>::at(int i){
    return this->objects.at(i);
}
 
template <class T>
size_t ObjectContainer<T>::size(){
    return this->objects.size();
}

// Returns the removed item
template <class T> 
T ObjectContainer<T>::remove_object(std::string name){
    int index = get_object_index_by_name(name);
    T removed = T(at(index));
    objects.erase(objects.begin() + index); 

    return removed;
    
}

template <class T>
T* ObjectContainer<T>::get_object_by_name(std::string name){
    for (int i = 0; i < this->objects.size(); i++){
        if (this->objects.at(i).getName() == name){
            return &this->objects.at(i);
        } 
    }
    return NULL;
}

template <class T>
int ObjectContainer<T>::get_object_index_by_name(std::string name){
    for (int i = 0; i < this->objects.size(); i++){
        if (this->objects.at(i).getName() == name){
            return i;
        } 
    }
    throw std::invalid_argument("No such item " + name);
}

template <class T>
bool ObjectContainer<T>::object_exists(std::string name){
    try {
        get_object_index_by_name(name);
    } catch (const std::invalid_argument& s) {
        return false;
    }
    return true;
}