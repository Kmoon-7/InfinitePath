#include "mapOne.hpp"

//inizializza la mappa
mapOne::mapOne(WINDOW *x, int my, int mx){
    a = x;
    createMap(map_One);
    enemyOne = NULL;
    enemyTwo = NULL;
    enemyThree = NULL;
    
    Val_enemyOne[0] = 12;
    Val_enemyOne[1] = 11;
    Val_enemyOne[2] = 2;
    Val_enemyOne[3] = 12;
    Val_enemyOne[4] = 27;

    Val_enemyTwo[0] = 5;
    Val_enemyTwo[1] = 99;
    Val_enemyTwo[2] = 2;
    Val_enemyTwo[3] = 5;
    Val_enemyTwo[4] = 30;

    Val_enemyThree[0] = 22;
    Val_enemyThree[1] = 40;
    Val_enemyThree[2] = 1;
    Val_enemyThree[3] = 40;
    Val_enemyThree[4] = 70;

    doorPrev[0] = 3;
    doorPrev[1] = 3;

    doorNext[0] = 15;
    doorNext[1] = 107;

    main[0] = 5;
    main[1] = 4;

    mainPrev[0] = 17;
    mainPrev[1] = 106;

    mainC = NULL;
    Key = NULL;
    art = NULL;
}

void mapOne::create_enemy(int position, int type){

    if(position == 0){
        if(type == 0)
            enemyOne = new cattivo(a, Val_enemyOne[0], Val_enemyOne[1],Val_enemyOne[2], Val_enemyOne[3], Val_enemyOne[4]);
        else if(type == 1)
            enemyOne = new cattivo_r(a, Val_enemyOne[0], Val_enemyOne[1],Val_enemyOne[2], Val_enemyOne[3], Val_enemyOne[4]);
        else if(type == 2 || type == 3){
            enemyOne = new cattivo_f(a, Val_enemyOne[0], Val_enemyOne[1],Val_enemyOne[2], Val_enemyOne[3], Val_enemyOne[4]);
            if(type == 3){
                ((cattivo_f*)enemyOne)->getArrowFast();
                ((cattivo_f*)enemyOne)->getFast();
            }
        }
    }
    else if(position == 1){
        if(type == 0)
            enemyTwo = new cattivo(a, Val_enemyTwo[0], Val_enemyTwo[1],Val_enemyTwo[2], Val_enemyTwo[3], Val_enemyTwo[4]);
        else if(type == 1)
            enemyTwo = new cattivo_r(a, Val_enemyTwo[0], Val_enemyTwo[1],Val_enemyTwo[2], Val_enemyTwo[3], Val_enemyTwo[4]);
        else if(type == 2 || type == 3){
            enemyTwo = new cattivo_f(a, Val_enemyTwo[0], Val_enemyTwo[1],Val_enemyTwo[2], Val_enemyTwo[3], Val_enemyTwo[4]);
            if(type == 3){
                ((cattivo_f*)enemyTwo)->getArrowFast();
                ((cattivo_f*)enemyTwo)->getFast();
            }
        }
    } else {
        if(type == 0)
            enemyThree = new cattivo(a, Val_enemyThree[0], Val_enemyThree[1],Val_enemyThree[2], Val_enemyThree[3], Val_enemyThree[4]);
        else if(type == 1)
            enemyThree = new cattivo_r(a, Val_enemyThree[0], Val_enemyThree[1],Val_enemyThree[2], Val_enemyThree[3], Val_enemyThree[4]);
        else if(type == 2 || type == 3){
            enemyThree = new cattivo_f(a, Val_enemyThree[0], Val_enemyThree[1],Val_enemyThree[2], Val_enemyThree[3], Val_enemyThree[4]);
            if(type == 3){
                ((cattivo_f*)enemyThree)->getArrowFast();
                ((cattivo_f*)enemyThree)->getFast();
            }
        }
    }
}


int mapOne::delete_enemy(int position, int type){
    int i = type;

    if(position == 0){
        if(type == 0){
            if(((cattivo *)(enemyOne))->getDead())
                i = 4;
            delete (cattivo *)enemyOne;
        }   
        else if(type == 1){
            if(((cattivo_r *)(enemyOne))->getDead())
                i = 4;
            delete (cattivo_r *)enemyOne;
        } else {
            if(((cattivo_f *)(enemyOne))->getDead())
                i = 4;
            ((cattivo_f *)(enemyOne))->deleteArrows();
            delete (cattivo_f *)enemyOne;
        }
        enemyOne = NULL;
    }
    else if(position == 1){
        if(type == 0){
            if(((cattivo *)(enemyTwo))->getDead())
                i = 4;
            delete (cattivo *)enemyTwo;
        }
        else if(type == 1){
            if(((cattivo_r *)(enemyTwo))->getDead())
                i = 4;
            delete (cattivo_r *)enemyTwo;
        } else {
            if(((cattivo_f *)(enemyTwo))->getDead())
                i = 4;
            ((cattivo_f *)(enemyTwo))->deleteArrows();
            delete (cattivo_f *)enemyTwo;
        }
        enemyTwo = NULL;
    } 
    else if(position == 2){
        if(type == 0){
            if(((cattivo *)(enemyThree))->getDead())
                i = 4;
            delete (cattivo *)enemyThree;
        }
        else if(type == 1){
            if(((cattivo_r *)(enemyThree))->getDead())
                i = 4;
            delete (cattivo_r *)enemyThree;
        } else {
            if(((cattivo_f *)(enemyThree))->getDead())
                i = 4;
            ((cattivo_f *)(enemyThree))->deleteArrows();
            delete (cattivo_f *)enemyThree;
        }
        enemyThree = NULL;
    }

    return (i);
}

void *mapOne::getEnemy(int i){
    void *tmp;

    if(i == 0)
        tmp = enemyOne;
    else if(i == 1)
        tmp = enemyTwo;
    else tmp = enemyThree;

    return (tmp);
}

void mapOne::build_Art(int ability){
    art = new artifacts(a, 30, 11, ability);
}

void mapOne::build_Key(){
    Key = new key(a, 14, 63);
}

//stampa la matrice bidimensionale
void mapOne::createMap(int map[map_height][map_length]){
    box(a, 0, 0);
    wrefresh(a);
    for (int y = 1; y-1 < map_height; y++) { 

        wmove(a, y+1, 3);

        for (int x = 0; x < map_length; x++) {
            switch (map[y-1][x]) {
                case 0:
                    waddch(a, ' ');
                    break;
                case 1:
                    waddch(a, '*');
                    break;
            }
        }
    }
    wrefresh(a);
};

//Apre e chiude le porte quando viene chiamata
void mapOne::door(){
    chtype c = mvwinch(a, doorNext[0], doorNext[1]);
    if (c == '*')
        c = ' ';
    else c = '*';

    for (int i = 0; i < 6; i++){
        mvwaddch(a, doorNext[0] + i, doorNext[1], c);
        wrefresh(a);
    }
}

void mapOne::create_main(bool door, int life, int posY, int posX){
    int tmp0, tmp1;
    
    if(posY == 0 && posX == 0){
        if(door){
            tmp0 = main[0];
            tmp1 = main[1];
        } else {
            tmp0 = mainPrev[0];
            tmp1 = mainPrev[1];
        }
    } else {
        tmp0 = posY;
        tmp1 = posX;
    }
    

    mainC = new protagonista(a, tmp0, tmp1, life, doorNext[0], doorNext[1], doorPrev[0], doorPrev[1]);
}

protagonista *mapOne::getMain(){
    return mainC;
};

key *mapOne::getKey(){
    return Key;
};

artifacts *mapOne::getArt(){
    return art;
};

artifacts *mapOne::delete_Art(){
    
    delete art;
    art = NULL;
    return (art);
}

key *mapOne::delete_key(){
    door();
    wrefresh(a);
    
    delete Key;
    Key = NULL;
    return (Key);
}

int mapOne::ArtGenerator(){
    return (art->generateArt());
}

protagonista *mapOne::deleteMain(){
    mainC->deleteArrows();
    delete mainC;
    mainC = NULL;
    return (mainC);
}