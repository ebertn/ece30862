#include "Game.h"

using namespace std;

Game::Game(string filename){
    this->filename = filename;
}
Game::~Game(){}

void Game::start(){
    //handle_input(); 
    read_xml();
}

void Game::read_xml(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(this->filename.c_str());

    if (!result){
        cout << "Bad file: " + this->filename << endl;
        return;
    }

    pugi::xml_node top = doc.first_child();

    for (pugi::xml_node panel = top.first_child(); panel != NULL; panel = panel.next_sibling()){
        create_object(panel);
    }
}

void Game::create_object(pugi::xml_node spec){
    if (spec.name() == "room"){
        Room room = Room(spec);
        this->rooms.push_back(room);
    } else if (spec.name() == "item"){

    } else if (spec.name() == "container"){

    } else if (spec.name() == "creature"){

    }
}

void Game::handle_input(){
    string input;
    getline(cin, input);

    if (input == "n" || input == "s" || input == "e" || input == "w"){
        
    } else if (input == "i"){
        
    } else if (input.substr(0, 4) == "take"){
        string item = get_single_param(input);
        cout << item << endl;
    } else if (input == "open exit"){
        
    } else if (input.substr(0, 4) == "open"){
        string container = get_single_param(input);
        cout << container << endl;
    } else if (input.substr(0, 4) == "read"){
        string item = get_single_param(input);
        cout << item << endl;
    } else if (input.substr(0, 4) == "drop"){
        string item = get_single_param(input);
        cout << item << endl;
    } else if (input.substr(0, 3) == "put"){
        str_tuple params = get_two_params(input, "in");
        cout << "Param1 = " + params.param1 << endl;
        cout << "Param2 = " + params.param2 << endl;
    } else if (input.substr(0, 7) == "turn on"){
        string item = get_single_param(input.substr(5, -1));
        cout << item << endl;
    } else if (input.substr(0, 7) == ">attack"){
        str_tuple params = get_two_params(input, "with");
        cout << "Param1 = " + params.param1 << endl;
        cout << "Param2 = " + params.param2 << endl;
    } else {
        cout << "Invalid command" << endl;
    }
}

string Game::get_single_param(string input){
    int space_loc = input.find(" ");

    if (space_loc == string::npos){
        cout << "Please include parameter(s)";
        return "";
    }

    return input.substr(space_loc + 1, input.length());
} 

str_tuple Game::get_two_params(string input, string delim){
    string params = get_single_param(input);
    if (params == "") return (str_tuple){.param1 = "", .param2 = ""};
    int split = params.find(delim);

    string param1 = params.substr(0, split - 1); 
    string param2 = params.substr(split + delim.length() + 1, -1);

    return (str_tuple){.param1 = param1, .param2 = param2};
}