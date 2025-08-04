#include "windows.hpp"

windows::windows(int my, int mx){
    maxY = my;
    maxX = mx;
    life = newwin (window_s_height, window_xs_length, maxY+window_height+1, maxX);
    wrefresh(life);
    box(life, 0, 0);
    wrefresh(life);
    points = newwin (window_s_height, window_s_length, maxY+window_height+1, window_xs_length+1+maxX);
    wrefresh(points);
    box(points, 0, 0);
    wrefresh(points);
    ability = newwin (window_s_height, window_s_length*1.5, maxY+window_height+1, window_s_length+window_xs_length+2+maxX);
    wrefresh(ability);
    box(ability, 0, 0);
    wrefresh(ability);
    mapNumber = newwin (window_s_height, window_xs_length, maxY+window_height+1, window_s_length*2.5+window_xs_length+3+maxX);
    wrefresh(mapNumber);
    box(mapNumber, 0, 0);
    wrefresh(mapNumber);
    countLife = 1;
    countPoints = 0;
    countMaps = 1;
};

//inizializza le informazioni in basso
void windows::inizializeWindows(){
    mvwprintw(life, 1, 2, "vite: O O O   ");
    wrefresh(life);
    mvwprintw(points, 1, 2, "punteggio:       ");
    wrefresh(points);
    resetLifePlus();
    resetAbilities();
    printMap();
};

void windows::removeLife(int n){
    int r = n / 5;
    while (r > 0 && countLife <= 3){
        int i = countLife*2;
        chtype c = mvwinch(life, 1, 14-i);
        if (c == 'O'){
            mvwprintw(life, 1, 14-i, "C");
            wrefresh(life);
        }
        else if (c == 'C'){
            mvwprintw(life, 1, 14-i, " ");
            wrefresh(life);
            countLife++;
        }
        r--;
    }
};
void windows::addLife(int n){
    int r = n / 5;
    while (r > 0 && countLife >= 1){
        int i = countLife*2;
        chtype c = mvwinch(life, 1, 14-i);
        if ((c == ':' || c == 'O') && (countLife > 1)){
            countLife--;
            i = countLife*2;
            c = mvwinch(life, 1, 14-i);
            if (c == ' '){
                mvwprintw(life, 1, 14-i, "C");
                wrefresh(life);
            }
            else if (c == 'C'){
                mvwprintw(life, 1, 14-i, "O");
                wrefresh(life);
            }
        }
        else if (c == 'C'){
            mvwprintw(life, 1, 14-i, "O");
            wrefresh(life);
        }
        r--;
    }
};

void windows::addPoints(int n){
    countPoints += n;
    mvwprintw(points, 1, 13, "%d", countPoints);
    wrefresh(points);
};

void windows::resetCount(){
    countLife = 1;
    countPoints = 0;
    countMaps = 1;
}

void windows::printMap(){
    mvwprintw(mapNumber, 1, 2, "mappa n°:     ");
    wrefresh(mapNumber);
    mvwprintw(mapNumber, 1, 15, "%d", countMaps);
    wrefresh(mapNumber);
}

void windows::addMap(){
    countMaps++;
    printMap();
};

void windows::subMap(){
    if (countMaps > 1){
        countMaps--;
    }
    printMap();
};

void windows::addSpeed(){
    mvwprintw(ability, 1, 11, "velocità+");
    wrefresh(ability);
};

void windows::addArrows(){
    mvwprintw(ability, 1, 22, "frecce+");
    wrefresh(ability);
};

void windows::lifePlus(){
    mvwprintw(life, 1, 15, "+");
    wrefresh(life);
};

void windows::resetAbilities(){
    mvwprintw(ability, 1, 2, "abilità:                      ");
    wrefresh(ability);
}

void windows::resetLifePlus(){
    mvwprintw(life, 1, 14, "   ");
    wrefresh(life);
}