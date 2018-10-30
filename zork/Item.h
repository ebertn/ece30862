#include <string>
#include <vector>
#include "Trigger.h"

class Item {
public:
    Item();
    ~Item();

private:
    std::string name;
    std::string status;
    std::string description;
    std::string writing;
    std::string turnon_print;
    std::string turnon_action;
    
    std::vector<Trigger> triggers;    
}