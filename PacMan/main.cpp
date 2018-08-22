#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include "Board.h"
#include "PacMan.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;


void movePacMan(int, PacMan *, Board *);
void startPosition();
int c=0;
char horizontal=205, vertical=186;

int main()
{


    Board firstBoard(20);
    firstBoard.originalSign=firstBoard.getSign(1,1);
    PacMan pacMan;
    firstBoard.setPosition(pacMan.getLocationX(),pacMan.getLocationY(),pacMan.getPacManInstance());
    firstBoard.showBoard();

    while(1)
    {
        c=getch();
        movePacMan(c, &pacMan, &firstBoard);
        system("cls");
        firstBoard.showBoard();
    }



    return 0;
}

void movePacMan(int whatArrow, PacMan *pacMan, Board *board)
{

    pacMan->setPreviousPosition(pacMan->getLocationX(),pacMan->getLocationY());

    switch(whatArrow)
    {
    case KEY_UP:
        if((pacMan->getLocationX()>1)&&(board->getSign(pacMan->getLocationX()-1,pacMan->getLocationY())!=horizontal))
        {
            pacMan->moveUp();
        }
        break;
    case KEY_DOWN:
        if((pacMan->getLocationX()<board->getSize()-2)&&(board->getSign(pacMan->getLocationX()+1,pacMan->getLocationY())!=horizontal))
        {
            pacMan->moveDown();
        }
        break;
    case KEY_LEFT:
        if((pacMan->getLocationY()>1)&&(board->getSign(pacMan->getLocationX(),pacMan->getLocationY()-1)!=vertical))
        {
            pacMan->moveLeft();
        }
        break;
    case KEY_RIGHT:
        if((pacMan->getLocationY()<board->getSize()-2)&&(board->getSign(pacMan->getLocationX(),pacMan->getLocationY()+1)!=vertical))
        {
            pacMan->moveRight();
        }
        break;
    default:
        break;
    }
    board->setPosition(pacMan->getPreviousPositionX(),pacMan->getPreviousPositionY(),board->originalSign);

    board->originalSign=board->getSign(pacMan->getLocationX(),pacMan->getLocationY());

    board->setPosition(pacMan->getLocationX(),pacMan->getLocationY(),pacMan->getPacManInstance());

    c=0;
}
