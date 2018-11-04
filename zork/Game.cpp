#include "Game.h"

using namespace std;

Game::Game(string filename){
    this->filename = filename;
}
Game::~Game(){}

void Game::start(){ 
    read_xml();
    //print_rooms();
    //print_items();

    enter_room("Entrance");
    while(this->game_running) {
        cout << "> ";
        handle_input();
    }
}

void Game::read_xml(){
    
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(this->filename.c_str());

    if (!result){
        cout << "Bad file: " + this->filename << endl;
        return;
    }

    pugi::xml_node top = doc.first_child();

    // Create items
    for (pugi::xml_node panel = top.child("item"); panel != NULL; 
                                panel = panel.next_sibling("item")){
        create_object(panel);
    }
    // Create containers
    for (pugi::xml_node panel = top.child("container"); panel != NULL; 
                                panel = panel.next_sibling("container")){
        create_object(panel);
    }
    // Create creatures
    for (pugi::xml_node panel = top.child("creature"); panel != NULL; 
                                panel = panel.next_sibling("creature")){
        create_object(panel);
    }
    // Create rooms
    for (pugi::xml_node panel = top.child("room"); panel != NULL; panel = panel.next_sibling("room")){
        create_object(panel);
    }
}

void Game::print_rooms(){
    for (int i = 0; i < this->rooms.size(); i++){
        cout << "Name: " << this->rooms.at(i).getName() << endl;
        cout << "Desc: " << this->rooms.at(i).getDesc() << endl;
        cout << "Items: ";
        this->rooms.at(i).print_items();
        cout << "Borders: " << endl;
        cout << "    n: " << this->rooms.at(i).getBorders().n << endl;
        cout << "    s: " << this->rooms.at(i).getBorders().s << endl;
        cout << "    e: " << this->rooms.at(i).getBorders().e << endl;
        cout << "    w: " << this->rooms.at(i).getBorders().w << endl;
        cout << endl;
    }
}

void Game::print_items(){ 
    for (int i = 0; i < this->items.size(); i++){
        cout << "Name: " << this->items.at(i).getName() << endl;
        cout << "Status: " << this->items.at(i).getStatus() << endl;
        cout << "Desc: " << this->items.at(i).getDesc() << endl;
        cout << "Writing: " << this->items.at(i).getWriting() << endl;
        cout << endl;
    }
}

void Game::create_object(pugi::xml_node spec){
    string obj_name = (string) spec.name();
    if (obj_name == "room"){
        Room room = Room(spec, this->items); 
        this->rooms.push_back(room); 
    } else if (obj_name == "item"){
        Item item = Item(spec); 
        this->items.add_item(item);
    } else if (obj_name == "container"){

    } else if (obj_name == "creature"){

    }
}

void Game::move(string dir){
    Borders borders = this->cur_room->getBorders();
    if (dir == "n" && !borders.n.empty()){
        enter_room(borders.n);
    } else if (dir == "s" && !borders.s.empty()){
        enter_room(borders.s);
    } else if (dir == "e" && !borders.e.empty()){
        enter_room(borders.e);
    } else if (dir == "w" && !borders.w.empty()){
        enter_room(borders.w);
    } else {
        cout << "Can't go that way." << endl;
    }
}

void Game::enter_room(string name){
    this->cur_room = get_room_by_name(name);
    cout << this->cur_room->getDesc() << endl;
}

Room* Game::get_room_by_name(std::string name){
    for (int i = 0; i < this->rooms.size(); i++){
        if (this->rooms.at(i).getName() == name){
            return &this->rooms.at(i);
        }
    }
    return NULL;
}

void Game::handle_input(){
    //cout << "Currently in: " << this->cur_room->getName() << endl;
    string input;
    getline(cin, input);

    if (input == "n" || input == "s" || input == "e" || input == "w"){
        move(input);
    } else if (input == "i"){
        print_inv();
    } else if (input.substr(0, 4) == "take"){
        string item = get_single_param(input);
        take(item);
    } else if (input == "open exit"){
        if (this->cur_room->getType() == "exit"){
            game_over();
        } else {
            cout << "This room is not an exit" << endl;
        }
    } else if (input.substr(0, 4) == "open"){
        string container = get_single_param(input);
        cout << container << endl;
    } else if (input.substr(0, 4) == "read"){
        string item = get_single_param(input);
        read(item);
    } else if (input.substr(0, 4) == "drop"){
        string item = get_single_param(input);
        drop(item);
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

void Game::game_over(){
    cout << "Game Over" << endl;
    this->game_running = 0;
}

// string owner is a room or container name
void Game::add(string object, string owner){
    //string type;
    //if (items.item_exists(object)) type = "item";
    //if (containers.)
}

void Game::take(string item_name){
    if (cur_room->item_exists(item_name)){
        Item removed = cur_room->remove_item(item_name);
        player_inv.add_item(removed);
    } else {
        cout << "There is no " << item_name << " in this room." << endl;
    }
}

void Game::drop(string item_name){
    if (player_inv.item_exists(item_name)){
        Item removed = player_inv.remove_item(item_name);
        cur_room->add_item(removed);
    } else {
        cout << "You are not carrying " << item_name << endl;
    }
}

void Game::print_inv(){
    cout << "Inventory: ";
    this->player_inv.print_items();
}

void Game::read(string item_name){
    if (player_inv.item_exists(item_name)){
        string writing = (*this->player_inv.get_item_by_name(item_name)).getWriting();
        cout << (writing == "" ? "Nothing written." : writing) << endl;
    } else {
        cout << "You are not carrying " << item_name << endl;
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