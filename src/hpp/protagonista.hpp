#include "cattivo_f.hpp"

class protagonista: public cattivo_f{
    
    protected:
        int life_Max = 30;
        bool quit ;
        bool door_open;
        bool next_room;
        bool prev_room;
        bool first_room;
        int y_room, x_room;
        bool Artifact;
        double frequence_walk;
        double frequence_arrow;
        bool got;
        
    public:
        protagonista(WINDOW* w, int y, int x, int v, int yl, int xl, int yp, int xp):cattivo_f(w,y,x,0,yl,xl){
            life = v;
            y_room = yp;
            x_room = xp;
            quit = false;
            next_room = false;
            prev_room = false;
            enemy = false;
            door_open = false;
            first_room = false;
            Artifact = false;
            got = false;
            frequence_walk = 0.1;
            frequence_arrow = 1;
            carattere = 'P';
            print();
        };// inizializzare con la Y e la X iniziale, la vita del personaggio e il valore Y e X della posizione della posta (exit)

        void add_life(int n);// call- incrementa con l'input il valore della vita
        void walk();
        void movement();
        void getk();//call- prende i valori digitati sulla tastiera e chiama le funzioni di movimento e spara
        void move_next_room();
        void is_first_room();//call- mette la bool first room true
        bool move_prev_room();
        bool getNext();//call- restituisce la bool next_room
        bool getQuit();//call- restituisce la bool quit
        bool getPrev();//call- restituisce la bool prec_room
        int getLife();//call- restituisce l'int vita
        bool getArtifact();//call- restituisce la bool Artefatto
        bool getOpen();//call- restituisce la bool door_open
        void check_hit_by(chtype c);
        void getFast();
        bool is_move_okay();
        bool getFirst_room();
        void OpenDoor();
        void getArrowFast();
};
