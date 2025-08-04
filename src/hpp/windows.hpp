#include <ncurses.h>

#define window_length 111
#define window_height 36

#define window_s_length 28
#define window_s_height 3

#define window_xs_length 19

class windows{
    protected:
        int countMaps;
        int countLife;
        int countPoints;
        int maxY, maxX;
        WINDOW *life;
        WINDOW *points;
        WINDOW *ability;
        WINDOW *mapNumber;

    public:
        windows(int my, int mx);
        void inizializeWindows();
        void removeLife(int n);
        void addLife(int n);
        void addPoints(int n);
        void addMap();
        void resetCount();
        void printMap();
        void subMap();
        void addSpeed();
        void addArrows();
        void resetAbilities();
        void lifePlus();
        void resetLifePlus();
}; 