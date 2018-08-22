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
        Board();
        Board(int);
        void showBoard();
        void setPosition(int, int, char);
        char getSign(int, int);
        int getSize();
        ~Board();
        friend class PacMan;
};

#endif // BOARD_H
