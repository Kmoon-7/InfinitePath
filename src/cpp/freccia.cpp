#include "freccia.hpp"

int freccia::getY(){
    return (posY);
}

int freccia::getX(){
    return (posX);
}

void freccia::is_mainC(){
    enemy = false;
}

chtype freccia::getHit_by(){
    return (hit_by);
}

bool freccia::getDead(){
    return (dead);
}

bool freccia::getBeen_hit(){
    return (been_hit);
}

int freccia::getDirezionection(){
    return (direction);
}

// In base alla direzione sposta il personaggio
void freccia::position_pointer(bool c){
    if(c == true){
        switch(direction){
            case 0:
                posY--;
                break;
            case 1:
                posX++;
                break;
            case 2:
                posY++;
                break;
            case 3:
                posX--;
                break;
        }
    }
    else {
        switch(direction){
            case 0:
                posY++;
                break;
            case 1:
                posX--;
                break;
            case 2:
                posY--;
                break;
            case 3:
                posX++;
                break;
        }
    }
}

void freccia::delete_immage(){
    mvwaddch(Window, posY, posX, ' ');
    wrefresh(Window);
}

// Restituisce true se le conzioni per spostarsi sono rispettate e false altrimenti
// controlla se ha colpito il protagonista
bool freccia::is_move_okay(){
    bool tmp;
    chtype testch;

    if(posX > 2 && posX < map_length+3 && posY > 1 && posY < map_height+1){
        testch = mvwinch(Window, posY, posX);
        
        check_hit_by(testch);
        tmp = (testch == ' ');
    } else tmp = false;
    return (tmp);
}

void freccia::check_hit_by(chtype c){
    if(!enemy){
        if(c == 'n' || c == 'N' || c == 'f' || c == 'F'){
            been_hit = true;
            hit_by = c;
        }
    } else {
        if(c == 'P')
            been_hit = true;
    }
}

void freccia::print(){
    mvwaddch(Window, posY, posX, carattere);
    wrefresh(Window);
}

void freccia::movement(){
    delete_immage();
    position_pointer(true);

    if(!is_move_okay()){
        dead = true;
    } else print();
}

clock_t freccia::check_time(clock_t clock_x, double freq){ //clock_x ultimo passo, freq tempo
    clock_t now ;
    now = clock();
    if (((double)(now-clock_x)/CLOCKS_PER_SEC) >= freq){
        check = true;
    }
    else {
        check = false;
        now = clock_x;
    }
    return now;
}

void freccia::walk(){
    if(!dead){
        cl_walk = check_time(cl_walk,frequence_walk);
        if(check)
            movement();
    }
}

void freccia::getFast(){
    frequence_walk = 0.08;
}

void freccia::resetBeen_hit(){
    been_hit = false;
    hit_by = 'z';
}

void freccia::death(){
    delete_immage();
    is_Dead();
}

void freccia::is_Dead(){
    dead = true;
}