#include <string>
#include <vector>

#include "Item.h"

class ItemContainer {
public:
    ItemContainer();
    ~ItemContainer();

    void add(Addable&);

protected:
    std::vector<Item> items;
}