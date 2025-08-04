#include <ncurses.h>

class menuPause {
    protected:
        WINDOW *a;
        const char *options[3] = {"riprendi", "ricomincia", "esci dal gioco"};
        int result;
        int posX;
        int posY;
    public:
        menuPause(WINDOW *x);
        void startMenu();
        void choise(const char *A[], int, int);
        int getResult();
};