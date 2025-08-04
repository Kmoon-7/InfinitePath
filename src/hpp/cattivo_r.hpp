#include "cattivo.hpp"

class cattivo_r: public cattivo{
    protected:

    public:
        cattivo_r(WINDOW* w, int y, int x, int d, int min, int max):cattivo(w,y,x,d,min,max){
            carattere = 'N';
            print();
        }// inizializzare con la Y e la X iniziale, la direzione del personaggio (0 = su, 1 = dx, 2 = giù, 3 = sx) e il valore minimo e massimo delle X o Y
        //  (a seconda della direzione data) del percorso del nemico

        void run_after(int n);//call- da chiamare prima di cammino e salva la posizione del nemico
};

//le funzioni taggate con "call" sono state ideate per essere chiamate all'esterno della classe