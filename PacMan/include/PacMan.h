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
        void setPreviousPosition(int, int);
        int getEatenBerries();
        int getLocationX();
        int getLocationY();
        char getPacManInstance();
        int getPreviousPositionX();
        int getPreviousPositionY();
        PacMan(int);
        ~PacMan();
        friend class Board;
};

#endif // PACMAN_H
