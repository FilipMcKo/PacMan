#include "PacMan.h"
#include <iostream>

using namespace std;

PacMan::PacMan()
{
    this->locationX=1;
    this->locationY=1;
    this->eatenBerries=0;
    this->pacManInstance=176;
}

void PacMan::moveUp()
{
    this->locationX--;
}
void PacMan::moveDown()
{
    this->locationX++;
}
void PacMan::moveRight()
{
    this->locationY++;
}
void PacMan::moveLeft()
{
    this->locationY--;
}
void PacMan::eatBerrie()
{
    this->eatenBerries++;
}

int PacMan::getLocationX()
{
    return this->locationX;
}
int PacMan::getLocationY()
{
    return this->locationY;
}
char PacMan::getPacManInstance()
{
    return pacManInstance;
}
void PacMan::setPreviousPosition(int previousPositionX, int previousPositionY)
{
    this->previousPositionX=previousPositionX;
    this->previousPositionY=previousPositionY;
}
int PacMan::getPreviousPositionX()
{
    return this->previousPositionX;
}
int PacMan::getPreviousPositionY()
{
    return this->previousPositionY;
}

PacMan::~PacMan()
{

}
