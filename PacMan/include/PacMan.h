#ifndef PACMAN_H
#define PACMAN_H
#include <iostream>
#include "Board.h"

using namespace std;

class PacMan
{
    int locationX, locationY, eatenBerries, previousPositionX, previousPositionY;
    char pacManInstance;
    Board board;
    public:
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void eatBerrie();
        int getLocationX();
        int getLocationY();
        char getPacManInstance();
        void setPreviousPosition(int, int);
        int getPreviousPositionX();
        int getPreviousPositionY();
        PacMan();
        ~PacMan();
};

#endif // PACMAN_H
