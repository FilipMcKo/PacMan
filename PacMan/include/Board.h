#ifndef BOARD_H
#define BOARD_H
#include <iostream>

using namespace std;


class Board
{
    int boardSize, positionX, positionY;
    char **matrix;
    short random;
    public:
        char originalSign;
        char originalSignUnderBerry;
        char getSign(int, int);
        int getSize();
        void showBoard(int, int);
        void setPosition(int, int, char);
        void gameOver();
        void resetTheBoard();
        Board();
        Board(int);
        ~Board();
        friend class PacMan;
};

#endif // BOARD_H
