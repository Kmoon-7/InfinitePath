#include "cattivo_r.hpp"

// Da chiamare prima di cammino e salva la posizione del nemico
void cattivo_r::run_after(int n){
        if((direction%2) != 0){
        if(n <= posX)
            direction = 3;
        else direction = 1;
    } else {
        if(n >= posY)
            direction = 2;
        else direction = 0;
    }

    walk();
}