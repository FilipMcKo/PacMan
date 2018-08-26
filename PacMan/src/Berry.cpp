#include "Berry.h"
#include "Board.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;

Berry::Berry(Board *board)
{
    berryInstance='O';
    srand(time(0));
    positionX=1+rand()%(board->getSize()-2);
    positionY=1+rand()%(board->getSize()-2);
    board->originalSignUnderBerry=board->getSign(positionX,positionY);
    board->setPosition(positionX, positionY, berryInstance);
}

Berry::~Berry()
{

}

void Berry::setPosition(Board *board)
{
    srand(time(0));
    positionX=1+rand()%(board->getSize()-2);
    positionY=1+rand()%(board->getSize()-2);
    board->originalSignUnderBerry=board->getSign(positionX,positionY);
    board->setPosition(positionX, positionY, berryInstance);
}

int Berry::getPositionX()
{
    return positionX;
}

int Berry::getPositionY()
{
    return positionY;
}
