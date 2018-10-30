#include <string>
#include <vector>

class Trigger {
public:
    Trigger();
    ~Trigger();

private:
    std::string type;
    std::string command;

    std::vector<std::string> print;
    std::vector<std::string> action;
    std::vector<std::string> conditions;
}