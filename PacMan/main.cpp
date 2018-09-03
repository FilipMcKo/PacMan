#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "Board.h"
#include "PacMan.h"
#include "Berry.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100

using namespace std;

void firstPlayer(int, PacMan *, Board *, Berry *);
void secondPlayer(int, PacMan *, Board *, Berry *);
void startPosition();
void gameOver(Board *, PacMan *);
void eatBerry(Board *, PacMan *, Berry *);
void showMenu();
bool unplayablePositionOfPacMan(Board *, PacMan*);
bool playablePositionOfBerry(Board *, Berry *);

const int boardSize=15;
int movementDirection1=0, menu1=33, menu2=7, menu3=7, menu4=7, menuInc=0, menuConfirm=1, menuScroll=0;
const char horizontal=205, vertical=186, w=119, s=115, a=97, d=100;
char playAgainChoice, movementDirection2=0;
bool breakTheLoop=1, playAgain=1;
string pacManName1, pacManName2;
clock_t start;

int main()
{
    Board testBoard(15);
    testBoard.setPosition(1,5,horizontal);
    testBoard.setPosition(1,6,horizontal);
    testBoard.setPosition(1,8,vertical);
    testBoard.setPosition(1,10,horizontal);
    testBoard.setPosition(2,4,vertical);
    testBoard.setPosition(2,7,vertical);
    testBoard.setPosition(2,8,vertical);
    testBoard.setPosition(2,10,vertical);
     testBoard.setPosition(1,10,vertical);
    testBoard.setPosition(3,4,vertical);
    testBoard.setPosition(3,7,vertical);
    testBoard.setPosition(3,9,horizontal);
    testBoard.setPosition(4,5,horizontal);
    testBoard.setPosition(4,6,horizontal);
    testBoard.setPosition(5,2,horizontal);
    testBoard.setPosition(5,3,horizontal);
    testBoard.setPosition(6,1,vertical);
    testBoard.setPosition(6,4,vertical);
    testBoard.setPosition(7,2,horizontal);
    testBoard.setPosition(7,3,horizontal);

    //testBoard.showBoard();
    while(1)
    {
        breakTheLoop=1;
        playAgain=1;
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),menu1);
        cout<<" Single Player \n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),menu2);
        cout<<"  Multiplayer  \n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),menu3);
        cout<<"  High Score   \n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),menu4);
        cout<<"     Exit      \n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        while(1)
        {
            menuConfirm=getch();
            if(menuConfirm==KEY_ENTER)
            {
                break;
            }

            system("cls");
            showMenu();
        }


        switch(menuInc)
        {
        case 0:
        {
            system("cls");
            cout<<"Enter your nickname: ";
            cin>>pacManName1;
            cout<<"Press any key to start";
            getch();
            system("cls");
            Board firstBoard(boardSize);
            firstBoard=testBoard;
            firstBoard.originalSign1=firstBoard.getSign(1,1);
            PacMan pacMan(257, pacManName1, 1, 1);
            Berry berry(&firstBoard);
            firstBoard.setPosition(pacMan.getLocationX(),pacMan.getLocationY(),pacMan.getPacManInstance());


            while(playAgain)
            {
                start=clock();
                firstBoard.showBoard();
                while(breakTheLoop&&(pacMan.remainingTime>0))
                {
                    pacMan.remainingTime=pacMan.totalTime-(clock()-start)/CLOCKS_PER_SEC;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    cout<<"Eaten berries:  "<<pacMan.getEatenBerries()<<endl;
                    if (pacMan.remainingTime>0)
                        cout<<"Remaining time: "<<pacMan.remainingTime;
                    else
                        cout<<"Remaining time: 0";

                    movementDirection1=getch();
                    firstPlayer(movementDirection1, &pacMan, &firstBoard, &berry);
                    system("cls");
                    firstBoard.showBoard();
                    if (pacMan.remainingTime==0)
                    {
                        cout<<"You are out of time!\n";
                        cout<<"Your score is: "<<pacMan.getEatenBerries()<<endl<<endl;
                        Sleep(100);
                    }
                }

                while(1)
                {
                    cout<<"Do you want to play again? [Y]/[N]\n";
                    playAgainChoice=getch();
                    if (playAgainChoice=='y'||playAgainChoice=='Y')
                    {
                        system("cls");
                        pacMan.resetPacMan();
                        firstBoard.resetTheBoard();
                        while(unplayablePositionOfPacMan(&firstBoard, &pacMan))
                        {
                          firstBoard.resetTheBoard();
                        }
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
                        firstBoard.showBoard();
                        if (pacMan.remainingTime==0)
                        {
                            cout<<"You are out of time!\n";
                            cout<<"Your score is: "<<pacMan.getEatenBerries()<<endl<<endl;
                        }
                    }
                }
            }
            break;
        }

        case 1:
        {
            system("cls");
            cout<<"Enter first nickname: ";
            cin>>pacManName1;
            cout<<"Enter second nickname: ";
            cin>>pacManName2;
            cout<<"Press any key to start";
            getch();
            system("cls");
            Board firstBoard(boardSize);
            firstBoard.originalSign1=firstBoard.getSign(1,1);
            firstBoard.originalSign2=firstBoard.getSign(boardSize-2,boardSize-2);
            PacMan pacMan1(257, pacManName1, 1, 1);
            PacMan pacMan2(258, pacManName2, boardSize-2,boardSize-2);
            Berry berry(&firstBoard);
            firstBoard.setPosition(pacMan1.getLocationX(),pacMan1.getLocationY(),pacMan1.getPacManInstance());
            firstBoard.setPosition(pacMan2.getLocationX(),pacMan2.getLocationY(),pacMan2.getPacManInstance());

            while(playAgain)
            {
                start=clock();
                firstBoard.showBoard();
                while(breakTheLoop&&(pacMan1.remainingTime>0))
                {
                    pacMan1.remainingTime=pacMan1.totalTime-(clock()-start)/CLOCKS_PER_SEC;

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                    cout<<"Eaten berries:  "<<pacMan1.getEatenBerries()<<endl;

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                    cout<<"Eaten berries:  "<<pacMan2.getEatenBerries()<<endl;

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    if (pacMan1.remainingTime>0)
                        cout<<"Remaining time: "<<pacMan1.remainingTime;
                    else
                        cout<<"Remaining time: 0";


                    movementDirection1=getch();
                    if (movementDirection1==KEY_UP||movementDirection1==KEY_DOWN||movementDirection1==KEY_LEFT||movementDirection1==KEY_RIGHT)
                        firstPlayer(movementDirection1, &pacMan1, &firstBoard, &berry);
                    else
                        secondPlayer(movementDirection1, &pacMan2, &firstBoard, &berry);


                    system("cls");
                    firstBoard.showBoard();
                    if (pacMan1.remainingTime==0)
                    {
                        cout<<"You are out of time!\n";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout<<pacMan1.getPacManName()<<"'s score is: "<<pacMan1.getEatenBerries()<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                        cout<<pacMan2.getPacManName()<<"'s score is: "<<pacMan2.getEatenBerries()<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                        Sleep(3000);
                    }
                }

                while(1)
                {
                    cout<<"Do you want to play again? [Y]/[N]\n";
                    playAgainChoice=getch();
                    if (playAgainChoice=='y'||playAgainChoice=='Y')
                    {
                        system("cls");
                        pacMan1.resetPacMan();
                        pacMan2.resetPacMan();
                        firstBoard.resetTheBoard();
                        while(unplayablePositionOfPacMan(&firstBoard, &pacMan1)&&unplayablePositionOfPacMan(&firstBoard, &pacMan1))
                        {
                          firstBoard.resetTheBoard();
                        }

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
                        firstBoard.showBoard();
                        if (pacMan1.remainingTime==0)
                        {
                            cout<<"You are out of time!\n";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                            cout<<pacMan1.getPacManName()<<"'s score is: "<<pacMan1.getEatenBerries()<<endl;
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                            cout<<pacMan2.getPacManName()<<"'s score is: "<<pacMan2.getEatenBerries()<<endl;
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                        }
                    }
                }
            }
            break;
        }

        case 2:
            system("cls");
            cout<<"Multiplayer\n";
            getch();
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
        }
    }
}

void firstPlayer(int whatArrow, PacMan *pacMan, Board *board, Berry *berry)
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
    board->setPosition(pacMan->getPreviousPositionX(),pacMan->getPreviousPositionY(),board->originalSign1);

    board->originalSign1=board->getSign(pacMan->getLocationX(),pacMan->getLocationY());

    board->setPosition(pacMan->getLocationX(),pacMan->getLocationY(),pacMan->getPacManInstance());

    eatBerry(board, pacMan, berry);

    gameOver(board, pacMan);

    movementDirection1=0;
}

void secondPlayer(int whatLetter, PacMan *pacMan, Board *board, Berry *berry)
{

    pacMan->setPreviousPosition(pacMan->getLocationX(),pacMan->getLocationY());

    switch(whatLetter)
    {
    case KEY_W:
        if((pacMan->getLocationX()>1)&&(board->getSign(pacMan->getLocationX()-1,pacMan->getLocationY())!=horizontal))
        {
            pacMan->moveUp();
        }
        break;
    case KEY_S:
        if((pacMan->getLocationX()<board->getSize()-2)&&(board->getSign(pacMan->getLocationX()+1,pacMan->getLocationY())!=horizontal))
        {
            pacMan->moveDown();
        }
        break;
    case KEY_A:
        if((pacMan->getLocationY()>1)&&(board->getSign(pacMan->getLocationX(),pacMan->getLocationY()-1)!=vertical))
        {
            pacMan->moveLeft();
        }
        break;
    case KEY_D:
        if((pacMan->getLocationY()<board->getSize()-2)&&(board->getSign(pacMan->getLocationX(),pacMan->getLocationY()+1)!=vertical))
        {
            pacMan->moveRight();
        }
        break;
    default:
        break;
    }
    board->setPosition(pacMan->getPreviousPositionX(),pacMan->getPreviousPositionY(),board->originalSign1);

    board->originalSign1=board->getSign(pacMan->getLocationX(),pacMan->getLocationY());

    board->setPosition(pacMan->getLocationX(),pacMan->getLocationY(),pacMan->getPacManInstance());

    eatBerry(board, pacMan, berry);

    gameOver(board, pacMan);

    movementDirection2=0;
}

void gameOver(Board *board, PacMan *pacMan)
{
    if (unplayablePositionOfPacMan(board, pacMan))
    {
        breakTheLoop=0;
        board->gameOver();
    }
}

void eatBerry(Board *board, PacMan *pacMan, Berry *berry)
{
    if ((pacMan->getLocationX()==berry->getPositionX())&&(pacMan->getLocationY()==berry->getPositionY()))
    {
        pacMan->eatBerry();
        board->originalSign1=board->originalSignUnderBerry;
        berry->setPosition(board);
        pacMan->totalTime+=3;
    }
}

void showMenu()
{
    menuScroll=getch();

    switch(menuScroll)
    {
    case KEY_UP:
        if(menuInc==0)
            menuInc=3;
        else
            menuInc--;
        break;

    case KEY_DOWN:
        if(menuInc==3)
            menuInc=0;
        else
            menuInc++;
        break;

    default:
        break;
    }
    if(menuInc==0)
    {
        menu1=33;
        menu2=7;
        menu3=7;
        menu4=7;
    }
    else if(menuInc==1)
    {
        menu1=7;
        menu2=33;
        menu3=7;
        menu4=7;
    }
    else if(menuInc==2)
    {
        menu1=7;
        menu2=7;
        menu3=33;
        menu4=7;
    }
    else if(menuInc==3)
    {
        menu1=7;
        menu2=7;
        menu3=7;
        menu4=33;
    }
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),menu1);
    cout<<" Single Player \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),menu2);
    cout<<"  Multiplayer  \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),menu3);
    cout<<"  High Score   \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),menu4);
    cout<<"     Exit      \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);

}


bool unplayablePositionOfPacMan(Board *board, PacMan *pacMan)
{
    //0
    if ((board->getSign((pacMan->getLocationX()-1),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+1),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-1))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+1))==vertical)
                {
                    return 1;
                }
            }
        }
    }
    //1
    else if ((board->getSign((pacMan->getLocationX()-1),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+2),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-1))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+1))==vertical)
                {
                    return 1;
                }
            }
        }
    }

     //2
    else if ((board->getSign((pacMan->getLocationX()-2),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+1),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-1))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+1))==vertical)
                {
                    return 1;
                }
            }
        }
    }

     //3
    else if ((board->getSign((pacMan->getLocationX()-1),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+1),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-1))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+2))==vertical)
                {
                    return 1;
                }
            }
        }
    }

     //4
    else if ((board->getSign((pacMan->getLocationX()-1),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+1),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-2))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+1))==vertical)
                {
                    return 1;
                }
            }
        }
    }

      //5
    else if ((board->getSign((pacMan->getLocationX()-1),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+2),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-1))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+2))==vertical)
                {
                    return 1;
                }
            }
        }
    }

     //6
    else if ((board->getSign((pacMan->getLocationX()-1),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+2),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-2))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+1))==vertical)
                {
                    return 1;
                }
            }
        }
    }

     //7
    else if ((board->getSign((pacMan->getLocationX()-2),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+1),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-1))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+2))==vertical)
                {
                    return 1;
                }
            }
        }
    }

    //8
    else if ((board->getSign((pacMan->getLocationX()-2),pacMan->getLocationY()))==horizontal)
    {
        if ((board->getSign((pacMan->getLocationX()+1),pacMan->getLocationY()))==horizontal)
        {
            if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()-2))==vertical)
            {
                if (board->getSign(pacMan->getLocationX(),(pacMan->getLocationY()+1))==vertical)
                {
                    return 1;
                }
            }
        }
    }

    else return 0;
}
