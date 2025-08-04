#include "mapThree.hpp"

mapThree::mapThree(WINDOW * x, int my, int mx): mapTwo (x, my, mx){
    createMap(map_Three);

    Val_enemyOne[0] = 12;
    Val_enemyOne[1] = 11;
    Val_enemyOne[2] = 2;
    Val_enemyOne[3] = 12;
    Val_enemyOne[4] = 22;

    Val_enemyTwo[0] = 15;
    Val_enemyTwo[1] = 102;
    Val_enemyTwo[2] = 3;
    Val_enemyTwo[3] = 62;
    Val_enemyTwo[4] = 102;

    Val_enemyThree[0] = 29;
    Val_enemyThree[1] = 20;
    Val_enemyThree[2] = 1;
    Val_enemyThree[3] = 29;
    Val_enemyThree[4] = 102;

    doorPrev[0] = 3;
    doorPrev[1] = 3;

    doorNext[0] = 3;
    doorNext[1] = 107;

    main[0] = 5;
    main[1] = 4;

    mainPrev[0] = 5;
    mainPrev[1] = 106;
};

void mapThree::build_Art(int ability){
    art = new artifacts(a, 7, 73, ability);
}

void mapThree::build_Key(){
    Key = new key(a, 29, 8);
}