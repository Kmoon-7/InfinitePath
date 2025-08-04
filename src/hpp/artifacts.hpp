#include "key.hpp"

class artifacts: public key{
    protected:
        chtype character;
        int number;
    public:
        artifacts(WINDOW * a, int y, int x, int p);
        int generateArt();
};