#include <string>
#include <vector>

#include "Item.h"

class Container {
public:
    Container();
    ~Container();

private:
    std::string name;
    std::string status;
    std::string description;

    std::vector<std::string> accept;
    std::vector<Item> items;
    std::vector<Trigger> triggers;
}