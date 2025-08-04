#include "protagonista.hpp"

void protagonista::add_life(int n) {
    life += n;
    if(life > life_Max)
        life = life_Max ;
}

void protagonista::movement(){
    delete_immage();
    position_pointer(true);

    if(!is_move_okay())
        position_pointer(false);

    print();
}

void protagonista::walk(){
    if(!dead){
        cl_walk = check_time(cl_walk,frequence_walk);
        if(check)
            movement();
    }
}

void protagonista::getk(){
    int n = wgetch(Window);

    if(n == 'w'){
        direction = 0;
        walk();
    }
    else if(n == 'd'){
        direction = 1;
        walk();
    }
    else if(n == 's'){
        direction = 2;
        walk();
    }
    else if(n == 'a'){
        direction = 3;
        walk();
    }
    else if(n == KEY_UP){
        direction_arrow = 0;
        inizialize_arrow(frequence_arrow, got);
    }
    else if(n == KEY_RIGHT){
        direction_arrow = 1;
        inizialize_arrow(frequence_arrow, got);
    }
    else if(n == KEY_DOWN){
        direction_arrow = 2;
        inizialize_arrow(frequence_arrow, got);
    }
    else if(n == KEY_LEFT){
        direction_arrow = 3;
        inizialize_arrow(frequence_arrow, got);
    }
    else if(n == 'q')
        quit = true;
}

void protagonista::move_next_room(){
    if(door_open){
        for(int i = 0; i < 6; i++){
            if(posY == Min+i)
                next_room = true;
        }
        next_room = next_room && posX == Max;    
    }
}

void protagonista::is_first_room(){
    first_room = true;
}

bool protagonista::move_prev_room(){
    bool tmp = true;

    for(int i = 0; i < 6; i++){
        prev_room = prev_room || (posY == y_room+i);
    }
    prev_room = prev_room && posX == x_room;
    
    if(first_room && prev_room){
        quit = true;
        prev_room = false;
        tmp = false;
    }

    return (tmp);
}

bool protagonista::getNext(){
    return (next_room);
}

bool protagonista::getQuit(){
    return (quit);
}

bool protagonista::getPrev(){
    return (prev_room);
}

int protagonista::getLife(){
    return (life);
}

bool protagonista::is_move_okay(){
    bool tmp;
    chtype testch;

    move_next_room();
    tmp = move_prev_room();

    if(posX > 2 && posX < map_length+3 && posY > 1 && posY < map_height+1){
        testch = mvwinch(Window, posY, posX);
        
        check_hit_by(testch);
        tmp = tmp && ((testch == ' ')||(testch == 'C')||(testch == 'A')) && !quit;
    } else tmp = false;
    
    return (tmp);
}

void protagonista::check_hit_by(chtype c){
    if(c == 'C')
        door_open = true;

    if(c == 'A')
        Artifact = true;
    freccia::check_hit_by(c);
}

bool protagonista::getArtifact(){
    return (Artifact);
}

bool protagonista::getOpen(){
    return (door_open);
}

void protagonista::getFast(){
    frequence_walk = 0.05;
}

void protagonista::getArrowFast(){
    frequence_arrow = 0.5;
    got = true;
}

bool protagonista::getFirst_room(){
    return (first_room);
}

void protagonista::OpenDoor(){
    door_open = true;
}