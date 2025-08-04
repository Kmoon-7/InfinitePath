#include "mapTwo.hpp"

mapTwo::mapTwo(WINDOW * x, int my, int mx): mapOne (x, my, mx){
    createMap(map_Two);

    Val_enemyOne[0] = 5;
    Val_enemyOne[1] = 8;
    Val_enemyOne[2] = 1;
    Val_enemyOne[3] = 8;
    Val_enemyOne[4] = 86;

    Val_enemyTwo[0] = 29;
    Val_enemyTwo[1] = 48;
    Val_enemyTwo[2] = 1;
    Val_enemyTwo[3] = 48;
    Val_enemyTwo[4] = 102;

    Val_enemyThree[0] = 15;
    Val_enemyThree[1] = 102;
    Val_enemyThree[2] = 3;
    Val_enemyThree[3] = 64;
    Val_enemyThree[4] = 102;

    doorPrev[0] = 5;
    doorPrev[1] = 107;

    doorNext[0] = 24;
    doorNext[1] = 107;

    main[0] = 7;
    main[1] = 106;

    mainPrev[0] = 26;
    mainPrev[1] = 106;
};

void mapTwo::build_Art(int ability){
    art = new artifacts(a, 22, 64, ability);
}

void mapTwo::build_Key(){
    Key = new key(a, 26, 24);
}

