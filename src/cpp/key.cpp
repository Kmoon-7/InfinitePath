#include "key.hpp"

key::key(WINDOW *a, int y, int x){
    n = a;
    character = 'C';
    posY = y;
    posX = x;
    printArt();
};

void key::printArt(){
    mvwaddch(n, posY, posX, character);
};

chtype key::getChar(){
    return character;
}

int key::getX(){
    return (posX);
}

int key::getY(){
    return (posY);
}
