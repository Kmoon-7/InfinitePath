#include "menu.hpp"

menu::menu(WINDOW *x): menuPause(x){
    posX = 45;
    posY = 23;
};

void menu::startMenu(){
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

//stampa la matrice bidimensionale(nome del gioco)
void menu::printTitle(int title[title_height][title_length]){ 
    for (int i = 0; i < title_height; i++){
        wmove (a, i + 9, 7);
        for (int j = 0; j < title_length; j++){
            switch(title[i][j]){
                case 1:
                    wprintw(a, "|");
                    break;
                case 0:
                    wprintw(a, " ");
                    break;
            }
        }
    }
    wrefresh(a);
};

//mostra i comandi e le istruzioni
void menu::instructions(){

    for (int i = 0; i < 24; i++){

        mvwprintw(a, i+5, 5, "%s", instructionsText[i]);
        wrefresh(a);
    }
    int c = 0;
    while (c != 10){  // torna indietro se viene premuto invio
        c = wgetch(a);
    }
    werase(a);
    wrefresh(a);
    box(a,0,0);
    wrefresh(a);
};