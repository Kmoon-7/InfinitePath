#include <ncurses.h>
#include <cstdlib>
#include <ctime>

class key{
    protected:
        WINDOW *n;
        chtype character;
        int posY;
        int posX;
    public:
        key(WINDOW *a, int y, int x);
        void printArt();
        chtype getChar();
        int getX();
        int getY();
};
