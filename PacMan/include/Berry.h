#ifndef BERRY_H
#define BERRY_H
#include <iostream>
#include "Board.h"

using namespace std;


class Berry
{
    int positionX, positionY;
    char berryInstance;
    public:
        Berry(Board *);
        ~Berry();
        void setPosition(Board *);
        int getPositionX();
        int getPositionY();

};

#endif // BERRY_H
