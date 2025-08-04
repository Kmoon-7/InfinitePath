#include "cattivo.hpp"


//tognie dalla vita il punteggio attacco dato in input
// e chiama morte se l'int vita è minore o uguale a 0
void cattivo::decrese_life(int n){
    life -= n;
    if (life <= 0)
         death();
}

//restituisce true se si è usciti dallo spazio delimitato
// e false altrimenti
bool cattivo::was_last(){
    bool tmp;
    if((direction%2) != 0){
        if(direction == 1)
            tmp = (posX > Max);
        else tmp = (posX < Min);
    } else {
        if(direction == 0)
            tmp = (posY < Min);
        else tmp = (posY > Max);
    }
    return tmp;
}

void cattivo::walk(){
    if(!dead){
        cl_walk = check_time(cl_walk,frequence_walk);
        if(check)
            movement();
    }
}

//controlla che non ci siano ostacoli (se no indietreggia) e
// di non uscire dallo spazio delimitato (inertedo la direzione di marcia altrimenti)
void cattivo::movement(){
    delete_immage();
    position_pointer(true);
    bool tmp = was_last();
    if((!is_move_okay()) || tmp){
        position_pointer(false);
        if(tmp){
            if(direction >= 2)
                direction = direction - 2;
            else direction = direction + 2;
        }
    }

    print();
}

//ritorna il punteggio di attacco
int cattivo::getAttack(){
    return (attack);
}
