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
        int totalTime, remainingTime;
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void eatBerry();
        void resetBerryCount();
        void resetPacMan();
        int getEatenBerries();
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
