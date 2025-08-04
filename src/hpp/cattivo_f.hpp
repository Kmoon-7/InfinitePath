#include "cattivo_r.hpp"

struct list_arrow{
    freccia *data;
    list_arrow *next;
};

class cattivo_f: public cattivo_r{

    protected:
        clock_t cl_arrow;
        double frequence_arrow;
        int direction_arrow;
        list_arrow *l_arrow;
        bool got;

    public:
        cattivo_f(WINDOW* w, int y, int x, int d, int min, int max):cattivo_r(w,y,x,d,min,max){
            cl_arrow = clock();
            l_arrow = NULL;
            life = 30;
            attack = 10;
            frequence_arrow = 3;
            got = false;
            carattere = 'f';
            print();
        }; // inizializzare con la Y e la X iniziale, la direzione del personaggio (0 = su, 1 = dx, 2 = giù, 3 = sx) e il valore minimo e massimo delle X o Y
           // (a seconda della direzione data) del percorso del nemico

        void pop(list_arrow *p); //call- elimina dalla lista di frecce la freccia data in input come puntatore all'elemento della lista (non alla freccia)
        void shoot(int y, int x);//call- prende la x e la y del personaggio e sceglie la direzione della freccia poi spara
        void inizialize_arrow(double, bool);
        list_arrow *getList(); //call- restituisce la lista di frecce del personaggio (vedi la struttura della lista in freccia.hpp)
        void arrow_walk();//call- fa avanzare tutte le frecce
        void getArrowFast();//call- velocizza lo sparo
        void getFast();
        void deleteArrows();
};

//le funzioni taggate con "call" sono state ideate per essere chiamate all'esterno della classe