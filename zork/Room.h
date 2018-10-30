#include <string>
#include <vector>
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Trigger.h"

class Room {
public:
    Room();
    ~Room();

private: 
    std::string name;
    std::string status;
    std::string type;
    std::string description;
    
    std::vector<Room> borders;
    std::vector<Container> containers;
    std::vector<Item> items;
    std::vector<Creature> creatures;
    std::vector<Trigger> triggers;    
}