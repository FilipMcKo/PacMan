#ifndef BOARD_H
#define BOARD_H
#include <iostream>



using namespace std;


class Board
{
    int boardSize, positionX, positionY;
    char **matrix;
    char berryInstance=271,
    pacmanInstance1=257,
    pacmanInstance2=258;

    short random;
    public:
        char originalSign1;
        char originalSign2;
        char originalSignUnderBerry;
        char getSign(int, int);
        int getSize();
        void showBoard();
        void setPosition(int, int, char);
        void gameOver();
        void resetTheBoard();
        Board();
        Board(int);
        ~Board();
        //friend class PacMan;
};

#endif // BOARD_H
