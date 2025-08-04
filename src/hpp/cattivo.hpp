#include "freccia.hpp"

class cattivo: public freccia{
    protected:
        int life;
        int attack;
        int Max;
        int Min;
        double frequence_walk;

    public:
        cattivo(WINDOW* w, int y, int x, int direzione, int min, int max):freccia(w,y,x,direzione){
            Max = max;
            Min = min;
            life = 20;
            attack = 5;
            frequence_walk = 0.5;
            carattere = 'n';
            print();
        }; // inizializzare con la Y e la X iniziale, la direzione del personaggio (0 = su, 1 = dx, 2 = giù, 3 = sx) e il valore minimo e massimo delle X o Y
           // (a seconda della direzione data) del percorso del nemico

        void walk();
        void movement();
        void decrese_life(int n);//call- decrementa la vita del personaggio con il valore inserito in input
        bool was_last();
        int getAttack();// call- restituisce l'int vita
};

//le funzioni taggate con "call" sono state ideate per essere chiamate all'esterno della classe
