#include "menuPause.hpp"

menuPause::menuPause(WINDOW *x){
    a = x;
    posX = 45;
    posY = 17;
};

void menuPause::startMenu(){
    werase(a);
    wrefresh(a);
    box(a,0,0);
    wrefresh(a);
    choise(options, posY, posX);
    werase(a);
    wrefresh(a);
    box(a,0,0);
    wrefresh(a);
};

void menuPause::choise(const char *options[], int posY, int posX){
    int choise = 0;
    int v = 0;

    while(choise != 10){
        for(int i = 0; i < 3; i++){
            if (i == v)
                wattron(a, A_REVERSE);
            mvwprintw(a, i+posY, posX, "%s", options[i]);
            wattroff(a, A_REVERSE);
        }
        choise = wgetch(a);

        switch(choise){
            case KEY_UP:
                v--;
                if (v == -1)
                    v = 2;
                break;
            case KEY_DOWN:
                v++;
                if (v == 3)
                    v = 0;
                break;
            default:
                break;
        }
    }
    result = v;
};

int menuPause::getResult(){
    return(result);
};