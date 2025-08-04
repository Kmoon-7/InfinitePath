#include "cattivo_f.hpp"

// Elimina una freccia dalla lista
void cattivo_f::pop(list_arrow *p){
    list_arrow *tmp = l_arrow;
    list_arrow *tmp_s = NULL;
    bool ok = (tmp != NULL);


    if(tmp == p)
        l_arrow = l_arrow->next;
    else {
        while(ok && tmp != p){
            if(tmp->next != NULL){
                tmp_s = tmp;
                tmp = tmp->next;
            } else ok = false;
        }
        if(ok)
            tmp_s->next = tmp->next;
    }
        
    if(ok){
        delete tmp->data;
        delete tmp;
    }
}

// Assegna una direzione alla freccia e spara
void cattivo_f::shoot(int y, int x){
    if(!dead){
        if((direction%2) != 0){
            if(posY == y){
                if(posX >= x)
                    direction_arrow = 3;
                else direction_arrow = 1;
            } else {
                if(posY > y)
                    direction_arrow = 0;
                else direction_arrow = 2;
            }
        } else {
            if(posX == x){
                if(posY >= y)
                    direction_arrow = 0;
                else direction_arrow = 2;
            } else {
                if(posX > x)
                    direction_arrow = 3;
                else direction_arrow = 1;
            }
        }
        inizialize_arrow(frequence_arrow, got);
    }
}

// Funzione da usare per sparare
void cattivo_f::inizialize_arrow(double f, bool g){
    cl_arrow = check_time(cl_arrow,f);
    if(check){
        list_arrow *tmp_l = new list_arrow;
        
        int tmpX = posX;
        int tmpY = posY;
        if (direction_arrow == 0)
            tmpY--;
        else if (direction_arrow == 1)
            tmpX++;
        else if (direction_arrow == 2)
            tmpY++;
        else tmpX--;

        tmp_l->data = new freccia(Window,tmpY,tmpX,direction_arrow);

        if(tmp_l->data->is_move_okay()){

            if(!enemy)
                tmp_l->data->is_mainC();

            if(g)
                tmp_l->data->getFast();

            tmp_l->next = l_arrow;
            l_arrow = tmp_l;

            l_arrow->data->print();
        } else {
            delete tmp_l->data;
            delete tmp_l;
        }
    }
}

list_arrow *cattivo_f::getList(){
    return (l_arrow);
}

void cattivo_f::arrow_walk(){
    list_arrow *tmp = l_arrow;

    while(tmp != NULL){
        tmp->data->walk();
        tmp = tmp->next;
    }
}

void cattivo_f::getArrowFast(){
    frequence_arrow = 1.5;
    got = true;
}

void cattivo_f::getFast(){
    frequence_walk = 0.4;
    carattere = 'F';
    print();
}

void cattivo_f::deleteArrows(){
    list_arrow *tmp = l_arrow;
    while(tmp != NULL){
        pop(tmp);
        tmp = l_arrow;
    }
}