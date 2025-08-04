#include "funzioni.hpp"
#include <ncurses.h>
#include <ctime>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char ** argv){
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    maxY = (maxY/2)-20;
    maxX = (maxX/2)-56;
    WINDOW *W = newwin (36, 111, maxY, maxX);
    wrefresh(W);
    nodelay(W, true);
    keypad(W, true);
    box(W, 0, 0);
    wrefresh(W);
    funzioni *game = new funzioni(W, maxY, maxX);
    game->play();
    endwin();
    return 0;
}
