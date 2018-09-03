#include "PacMan.h"
#include <iostream>

using namespace std;



PacMan::PacMan(int pacManInstance, string pacManName, int locationX, int locationY)
{
    this->locationX=locationX;
    this->locationY=locationY;
    this->eatenBerries=0;
    this->pacManInstance=pacManInstance;
    this->totalTime=15;
    this->remainingTime=1;
    this->pacManName=pacManName;
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
void PacMan::eatBerry()
{
    this->eatenBerries++;
}

void PacMan::resetBerryCount()
{
    this->eatenBerries=0;
}
int PacMan::getEatenBerries()
{
    return eatenBerries;
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

void PacMan::resetPacMan()
{
    this->locationX=1;
    this->locationY=1;
    this->eatenBerries=0;
    this->pacManInstance=257;
    this->totalTime=15;
    this->remainingTime=1;
}

string PacMan::getPacManName()
{
return this->pacManName;
}

PacMan::~PacMan()
{

}
