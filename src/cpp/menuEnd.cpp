#include "menuEnd.hpp"

menuEnd::menuEnd(WINDOW *x): menu(x){
};

void menuEnd::startMenu(){
    werase(a);
    wrefresh(a);
    box(a,0,0);
    wrefresh(a);
    printTitle(title);
    choise(options, posY, posX);
    werase(a);
    wrefresh(a);
    box(a,0,0);
    wrefresh(a);
};