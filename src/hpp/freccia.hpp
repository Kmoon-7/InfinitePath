#include <ncurses.h>
#include <ctime>
#include <time.h>
#define map_length 105
#define map_height 32

class freccia{
    protected:
        int posY, posX, direction;
        bool dead;
        clock_t cl_walk;
        double frequence_walk;
        bool been_hit;
        bool enemy;
        chtype hit_by;
        bool check;
        WINDOW *Window;
        chtype carattere;

    public:
        freccia(WINDOW* w, int y, int x, int direzione){
            Window = w;
            posY = y;
            posX = x;
            direction = direzione;
            cl_walk = clock();
            dead = false;
            been_hit = false;
            frequence_walk = 0.1;
            enemy = true;
            hit_by = 'z';
            carattere = '.';
        };

        int getX();//call- restituisce l'int posX
        int getY();//call- restituisce l'int posY
        void is_mainC();//call- passa la bool enemy su false
        chtype getHit_by();//call- passa il char colpito_da
        bool getDead();//call- restituisce la bool morto
        bool getBeen_hit();//call- restituisce la bool colpito
        int getDirezionection();//call- ritorna l'int direzione
        void position_pointer(bool c);
        void delete_immage();
        bool is_move_okay();
        void check_hit_by(chtype c);
        void print();
        void movement();
        clock_t check_time(clock_t clock_x, double freq);
        void walk();
        void getFast();
        void resetBeen_hit();
        void death();
        void is_Dead();
};