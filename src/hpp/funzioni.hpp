#include "mapThree.hpp"
#include "menuEnd.hpp"
#include "windows.hpp"
#include <cmath>

struct l_enemy{
    void *data;
    int position;
    int kind;
    l_enemy *next;
};

typedef l_enemy *p_l_enemy;

class funzioni{

    struct level{
        level *prev;
        int room;
        int Enemy[3];
        bool key_b;
        bool artifact;
        level *next;
    };

    typedef level *p_level;

    protected:
        int life_main;
        WINDOW *W;
        p_level list_levels;
        mapOne *map_one;
        mapTwo *map_two;
        mapThree *map_three;
        p_l_enemy list_enemy;
        protagonista *avatar;
        key *Key;
        artifacts *artifact;
        windows *wins;

        bool check_end;
        bool check_game;
        bool forward;
        int ability;
        bool lifePlus;

        int maxY, maxX;

        int posY,posX;


        void getAbility();
        void time_out();
        void menuStart();
        int extract_random(int max);
        void End();
        void save_datas();
        void move_door(bool prev);
        void f_artifact();
        void f_key();
        p_l_enemy closer(p_l_enemy a, p_l_enemy b, int y, int x);
        void been_hit(int i, int y, int x);
        void check_arrow_main();
        void check_arrow_enemy(cattivo_f *p);
        void check_M_caracter();
        void check_enemy();
        void check_life();
        void shoot();
        void walk();
        void inizialize_mainC();
        void inizialize_enemy();
        void inizialize_key_art();
        void inizialize_map();
        void new_room();        
        void start_game();  
        void cleanMemory();

    public:
        funzioni(WINDOW *w, int my, int mx){
            maxY = my;
            maxX = mx;
            W = w;
            life_main = 30;
            check_game = true;
            list_levels = NULL;
            map_one = NULL;
            map_two = NULL;
            map_three = NULL;
            list_enemy = NULL;
            avatar = NULL;
            Key = NULL;
            artifact = NULL;
            forward = true;
            posY = 0;
            posX = 0;
            ability = 0;
            wins = NULL;
            lifePlus = false;
        };

        void play();//call- fa iniziare il gioco
};






