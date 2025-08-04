#include "artifacts.hpp"

artifacts::artifacts(WINDOW * a, int y, int x,int p): key (a, y, x){
    character = 'A';
    if(p == 3) number = 1;
    else if(p == 1 || p == 2) number = 2;
    else number = 3;
    mvwaddch(n, posY, posX, character);
};

//genera un numero randomico per assegnare la tipologia di artefatto
int artifacts::generateArt(){
    int n = rand() % number;
    return n;
}
