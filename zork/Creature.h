#include <string>
#include <vector>

#include "Trigger.h"

class Creature {
public:
    Creature();
    ~Creature();

private:
    std::string name;
    std::string status;
    std::string description;
    std::string attack;

    std:vector<std::string> vulnerabilities;
    std::vector<Trigger> triggers;
}