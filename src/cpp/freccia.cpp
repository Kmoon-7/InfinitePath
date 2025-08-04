#include "freccia.hpp"

//restituisce la Y della posizione del personaggio
int freccia::getY(){
    return (posY);
}

//restituisce la X della posizione del personaggio
int freccia::getX(){
    return (posX);
}

//converte il bool antagonista a false
void freccia::is_mainC(){
    enemy = false;
}

//passa il char colpito_da
chtype freccia::getHit_by(){
    return (hit_by);
}

//restituisce il bool morto
bool freccia::getDead(){
    return (dead);
}

//restituisce il bool colpito
bool freccia::getBeen_hit(){
    return (been_hit);
}

//ritorna l'int direzione
int freccia::getDirezionection(){
    return (direction);
}

//in base al booleano messo in input fa andare avanti (true) o
//in dietro (false) il puntatore nella direzione indicata dalla 
//variabile direzione
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

//cancella il la zona dove si trova il personaggio
void freccia::delete_immage(){
    mvwaddch(Window, posY, posX, ' ');
    wrefresh(Window);
}

//restituisce true se le conzioni per spostarsi sono
//rispettate e false altrimenti
//controlla se ha colpito il protagonista
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

//controlla da chi è stato colpito
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

//stampa il personaggio
void freccia::print(){
    mvwaddch(Window, posY, posX, carattere);
    wrefresh(Window);
}

//sposta il personaggio e se incontra un ostacolo
// lo fa morire
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

//fa camminare il personaggio
void freccia::walk(){
    if(!dead){
        cl_walk = check_time(cl_walk,frequence_walk);
        if(check)
            movement();
    }
}

//fa diventare più veloce la freccia
void freccia::getFast(){
    frequence_walk = 0.08;
}

//resetta been_hit
void freccia::resetBeen_hit(){
    been_hit = false;
    hit_by = 'z';
}

//chiama la funzione cancella e mette il bool morto a true
void freccia::death(){
    delete_immage();
    is_Dead();
}

//mette il bool morto a true
void freccia::is_Dead(){
    dead = true;
}