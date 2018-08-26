#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "Board.h"
#include "PacMan.h"
#include "Berry.h"
#include "Timer.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;


void singlePlayer(int, PacMan *, Board *, Berry *);
void startPosition();
void gameOver(Board *, PacMan *);
void eatBerry(Board *, PacMan *, Berry *);
int c=0;
char horizontal=205, vertical=186, playAgainChoice;
bool breakTheLoop=1, playAgain=1;
clock_t start;

int main()
{

    Board firstBoard(17);
    firstBoard.originalSign=firstBoard.getSign(1,1);
    PacMan pacMan;
    Berry berry(&firstBoard);
    firstBoard.setPosition(pacMan.getLocationX(),pacMan.getLocationY(),pacMan.getPacManInstance());

    cout<<"Press any key to start";
    getch();
    system("cls");


    while(playAgain)
    {
        start=clock();
        firstBoard.showBoard(berry.getPositionX(),berry.getPositionY());
        while(breakTheLoop&&pacMan.remainingTime)
        {
            pacMan.remainingTime=pacMan.totalTime-(clock()-start)/CLOCKS_PER_SEC;
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
            cout<<"Eaten berries:  "<<pacMan.getEatenBerries()<<endl;
            cout<<"Remaining time: "<<pacMan.remainingTime;
            c=getch();
            singlePlayer(c, &pacMan, &firstBoard, &berry);
            system("cls");
            firstBoard.showBoard(berry.getPositionX(),berry.getPositionY());
            if (pacMan.remainingTime==0)
            {
                cout<<"You are out of time!\n";
                cout<<"Your score is: "<<pacMan.getEatenBerries()<<endl<<endl;
                Sleep(3000);
            }
        }

        while(1)
        {
            cout<<"Do you want ot play again? [Y]/[N]\n";
            playAgainChoice=getch();
            if (playAgainChoice=='y'||playAgainChoice=='Y')
            {
                system("cls");
                pacMan.resetPacMan();
                firstBoard.resetTheBoard();
                berry.setPosition(&firstBoard);
                breakTheLoop=1;
                break;
            }
            else if (playAgainChoice=='n'||playAgainChoice=='N')
            {
                playAgain=0;
                break;
            }
            else
            {
                system("cls");
                firstBoard.showBoard(berry.getPositionX(),berry.getPositionY());
                if (pacMan.remainingTime==0)
                {
                    cout<<"You are out of time!\n";
                    cout<<"Your score is: "<<pacMan.getEatenBerries()<<endl<<endl;
                }
            }
        }



    }

    return 0;
}

void singlePlayer(int whatArrow, PacMan *pacMan, Board *board, Berry *berry)
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

    eatBerry(board, pacMan, berry);

    gameOver(board, pacMan);

    c=0;
}

void gameOver(Board *board, PacMan *pacMan)
{
    if ((board->getSign((pacMan->getLocationX()-1),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+1),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-1))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+1))==vertical)
                {
                    board->gameOver();
                    breakTheLoop=0;
                }
            }
        }
    }
}

void eatBerry(Board *board, PacMan *pacMan, Berry *berry)
{
    if ((pacMan->getLocationX()==berry->getPositionX())&&(pacMan->getLocationY()==berry->getPositionY()))
    {
        pacMan->eatBerry();
        board->originalSign=board->originalSignUnderBerry;
        berry->setPosition(board);
        pacMan->totalTime+=3;
    }
}
