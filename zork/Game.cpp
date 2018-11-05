#include "Game.h"

using namespace std;

Game::Game(string filename){
    this->filename = filename;
}
Game::~Game(){}

void Game::start(){ 
    read_xml();
    //print_items();
    //print_rooms();
    //cout << "Num creatures: " << creatures.size() << endl;
    //execute_command("Add torch to MainCavern");
    //execute_command("Update torch to MainCavern");
    //execute_command("Delete torch");
    enter_room("Entrance");
    //execute_command("Delete MainCavern");
    //delete_obj("torch");
    //update("torch", "dog");
    // add("key", "Entrance");

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
        cout << "Containers: ";
        rooms.at(i).containers.print_containers();
        cout << "Creatures: ";
        rooms.at(i).creatures.print_creatures();
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
        cout << "Turnon Action: " << this->items.at(i).getTurnonAction() << endl;
        cout << "Turnon Print: " << this->items.at(i).getTurnonPrint() << endl;
        cout << endl;
    }
}

void Game::create_object(pugi::xml_node spec){
    string obj_name = (string) spec.name();
    if (obj_name == "room"){
        Room room = Room(spec, this->items, this->containers, this->creatures); 
        this->rooms.add_room(room); 
    } else if (obj_name == "item"){
        Item item = Item(spec); 
        this->items.add_item(item);
    } else if (obj_name == "container"){
        Container container = Container(spec, this->items); 
        this->containers.add_container(container);
    } else if (obj_name == "creature"){
        Creature creature = Creature(spec); 
        this->creatures.add_creature(creature);
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
        open(container);
    } else if (input.substr(0, 4) == "read"){
        string item = get_single_param(input);
        read(item);
    } else if (input.substr(0, 4) == "drop"){
        string item = get_single_param(input);
        drop(item);
    } else if (input.substr(0, 3) == "put"){
        str_tuple params = get_two_params(input, " in ");
        put(params.param1, params.param2);
    } else if (input.substr(0, 7) == "turn on"){
        string item = get_single_param(input.substr(5, -1));
        turnon(item);
    } else if (input.substr(0, 7) == ">attack"){
        str_tuple params = get_two_params(input, " with ");
        attack(params.param1, params.param2);
    } else {
        cout << "Invalid command" << endl;
    }
}

void Game::execute_command(string cmd){
    if (cmd.substr(0, 3) == "Add"){
        str_tuple params = get_two_params(cmd, " to ");
        add(params.param1, params.param2);
    } else if (cmd.substr(0, 6) == "Delete"){
        string object = get_single_param(cmd);
        delete_obj(object);
    } else if (cmd.substr(0, 6) == "Update"){
        str_tuple params = get_two_params(cmd, " to ");
        update(params.param1, params.param2);
    } else if (cmd.substr(0, 9) == "Game Over"){
        game_over();
    }
}

void Game::add(string object, string owner){
    string type_obj = getType(object);
    string type_own = getType(owner);

    if(type_obj != "bad" && type_own != "bad"){
        if (type_own == "room"){
            Room* room = rooms.get_room_by_name(owner);
            if (type_obj == "item"){
                Item new_item = Item(*items.get_item_by_name(object));
                room->add_item(new_item);
            } else if (type_obj == "creature"){
                Creature new_creature = Creature(*creatures.get_creature_by_name(object));
                room->creatures.add_creature(new_creature);
            } else if (type_obj == "container"){
                Container new_container = Container(*containers.get_container_by_name(object));
                room->containers.add_container(new_container);
            }

        } else if (type_own == "container"){
            Container* container = cur_room->containers.get_container_by_name(owner);
            if (type_obj == "item"){
                Item new_item = Item(*items.get_item_by_name(object));
                container->add_item(new_item);
            }
        }
    } else {
        cout << "Invalid add, bad object or owner" << endl;
    }  
}

void Game::delete_obj(string object){
    string type = getType(object);

    if (type == "item"){
        for (int i = 0; i < rooms.size(); i++){
            if(rooms.at(i).item_exists(object)){
                rooms.at(i).remove_item(object);
            }
        }
    } else if (type == "creature"){
        for (int i = 0; i < rooms.size(); i++){
            if(rooms.at(i).creatures.creature_exists(object)){
                rooms.at(i).creatures.remove_creature(object);
            }
        }
    } else if (type == "container"){
        for (int i = 0; i < rooms.size(); i++){
            if(rooms.at(i).containers.container_exists(object)){
                rooms.at(i).containers.remove_container(object);
            }
        }
    } else if (type == "room"){
        if (rooms.get_room_by_name(object)->getName() != this->cur_room->getName()){
            if(rooms.room_exists(object)){
                if(get_room_by_name(cur_room->getBorders().n)->getName() == object){
                    cur_room->borders.n = "";
                } else if(get_room_by_name(cur_room->getBorders().s)->getName() == object){
                    cur_room->borders.s = "";
                } else if(get_room_by_name(cur_room->getBorders().e)->getName() == object){
                    cur_room->borders.e = "";
                } else if(get_room_by_name(cur_room->getBorders().w)->getName() == object){
                    cur_room->borders.w = "";
                }
                rooms.remove_room(object);
            }
        }
    }
}

void Game::update(string object, string status){
    string type = getType(object);

    if (type == "item"){
        for (int i = 0; i < rooms.size(); i++){
            if(rooms.at(i).item_exists(object)){
                //rooms.at(i).remove_item(object);
                rooms.at(i).get_item_by_name(object)->status = status;
            } else if (player_inv.item_exists(object)){
                player_inv.get_item_by_name(object)->status = status;          
            }
        }
    } else if (type == "creature"){
        for (int i = 0; i < rooms.size(); i++){
            if(rooms.at(i).creatures.creature_exists(object)){
                //rooms.at(i).creatures.remove_creature(object);
                rooms.at(i).creatures.get_creature_by_name(object)->status = status;

            }
        }
    } else if (type == "container"){
        for (int i = 0; i < rooms.size(); i++){
            if(rooms.at(i).containers.container_exists(object)){
                // rooms.at(i).containers.remove_container(object);
                rooms.at(i).containers.get_container_by_name(object)->status = status;
            }
        }
    } else if (type == "room"){
        if (rooms.get_room_by_name(object)->getName() != cur_room->getName()){
            if(rooms.room_exists(object)){
                // rooms.remove_room(object);
                rooms.get_room_by_name(object)->status = status;
            }
        }
    }

}

string Game::getType(string object){
    if (items.item_exists(object)){
        return "item";
    }
    if (rooms.room_exists(object)){
        return "room";
    }
    if (creatures.creature_exists(object)){
        return "creature";
    }
    if (containers.container_exists(object)){
        return "container";
    } 
    if (object == "inventory") {
        return "inventory";
    } else {
        return "bad";
    }
}

void Game::game_over(){
    cout << "Game Over" << endl;
    this->game_running = 0;
}

void Game::take(string item_name){
    if (cur_room->item_exists(item_name)){
        Item removed = cur_room->remove_item(item_name);
        player_inv.add_item(removed);
        cout << "Item " << item_name << " added to inventory." << endl;
    } else {
        cout << "There is no " << item_name << " in this room." << endl;
    }
}

void Game::drop(string item_name){
    if (player_inv.item_exists(item_name)){
        Item removed = player_inv.remove_item(item_name);
        cur_room->add_item(removed);
        cout << item_name << " dropped." << endl;
    } else {
        cout << "You are not carrying " << item_name << endl;
    }
}

void Game::attack(string creature_name, string item){
    // if(!player_inv.item_exists(item)){
    //     cout << "You don't have a " << item << endl;
    //     return;
    // }

    // Creature* creature = cur_room->creatures.get_creature_by_name(creature_name);

    // for (int i = 0; i < creature->vulnerabilities.size(); i++){
    //     if (creature->vulnerabilities.at(i) == item){
    //         for(int j = 0; j < creature->attack.conditions.size(); j++){
    //             if (condition_is_true(creature->attack.conditions.at(j))){
    //                 for(int k = 0; k < creature->attack.actions.size(); k++){
    //                     cout << "You assult the creature with the " << item << endl;
    //                     execute_command(creature->attack.actions.at(k));
    //                 }
    //             }
    //         }
    //     }
    // }
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

void Game::turnon(string item_name){
    if (player_inv.item_exists(item_name)){
        cout << "You activate the " << item_name << endl;
        Item* item = player_inv.get_item_by_name(item_name);
        execute_command(item->getTurnonAction());
        cout << item->getTurnonPrint() << endl;
    } else {
        cout << "You are not carrying " << item_name << endl;
    }
}

void Game::open(std::string container_name){
    if(cur_room->containers.container_exists(container_name)){
        Container* container = containers.get_container_by_name(container_name);
        if (container->size() > 0){
            cout << container_name << " contains ";
            container->print_items();

            for (int i = 0; i < container->size(); i++){
                Item removed = container->remove_item(container->at(i).getName());
                cur_room->add_item(removed);
            }
        } else {
            cout << container_name << " is empty" << endl;
        }
    } else {    
        cout << "There is no container " << container_name << endl;
    }
}

void Game::put(string item_name, string container_name){
    if(player_inv.item_exists(item_name)){
        Container* container = containers.get_container_by_name(container_name);
        for (int i = 0; i < container->accept.size(); i++){
            if (item_name == container->accept.at(i)){
                Item removed = player_inv.remove_item(item_name);
                container->add_item(removed);
                cout << "Item " << item_name << " added to " << container_name << endl;
                return;
            }
        }
        cout << item_name << " cannot be put into " << container_name << endl;

    } else {
        cout << "You are not carrying " << item_name << endl;
    }
}

string Game::condition_type(pugi::xml_node spec){
    if (spec.child_value("has") == "") {
        return "owner";
    } else {
        return "status";
    }
}

bool Game::condition_is_true(pugi::xml_node spec){
    string type = condition_type(spec); 

    if (type == "owner"){
        string owner = spec.child_value("owner");
        string object = spec.child_value("object");
        string has = spec.child_value("has");

        string owner_type = getType(owner);
        string object_type = getType(object);

        if (owner_type == "container"){
            if (!cur_room->containers.container_exists(object)) return false;
            Container* container = cur_room->containers.get_container_by_name(owner);
            bool has_it = container->item_exists(object);

            return !(has_it ^ (has == "yes"));
        } else if (owner_type == "room"){
            if (owner_type != cur_room->getName()) return false;
            Room* room = cur_room;
            bool has_it;
            if (object_type == "item"){
                has_it = room->item_exists(object);
                for (int i = 0; i < room->containers.size(); i++){
                    has_it |= room->containers.at(i).item_exists(object);
                }
            } else if (object_type == "container"){
                has_it = room->containers.container_exists(object);
            } else if (object_type == "creature"){
                has_it = room->creatures.creature_exists(object);
            }
            return !(has_it ^ (has == "yes"));
        } else if(owner_type == "inventory"){
            bool has_it = player_inv.item_exists(object);

            return !(has_it ^ (has == "yes"));
        }
    } else {
        string object = spec.child_value("object");
        string status = spec.child_value("status");

        string object_type = getType(object);
        
        if (object_type == "item"){
            if(cur_room->item_exists(object)){
                if (cur_room->get_item_by_name(object)->status == status){
                    return true;
                }
            }

            for (int i = 0; i < cur_room->containers.size(); i++){
                if (cur_room->containers.at(i).item_exists(object)){
                    return true;
                }
            }
        } else if (object_type == "room"){
            return cur_room->status == status;
        } else if (object_type == "container"){
            if(cur_room->containers.container_exists(object)){
                return cur_room->containers.get_container_by_name(object)->status == status;
            }            
        } else if (object_type == "creature"){
            if(cur_room->creatures.creature_exists(object)){
                return cur_room->creatures.get_creature_by_name(object)->status == status;
            } 
        }
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

    string param1 = params.substr(0, split); 
    string param2 = params.substr(split + delim.length(), -1);

    return (str_tuple){.param1 = param1, .param2 = param2};
}