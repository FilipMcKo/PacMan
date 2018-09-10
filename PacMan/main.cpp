#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream> //highscore file
#include <vector>
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
void saveTheScore(string, int);
void updateHighScore();
void showHighScore();
bool unplayablePositionOfPacMan(Board *, PacMan*);

const int boardSize=15;
int movementDirection1=0, menu1=33, menu2=7, menu3=7, menu4=7, menuInc=0, menuConfirm=1, menuScroll=0;
const char horizontal=205, vertical=186, w=119, s=115, a=97, d=100;
char playAgainChoice, movementDirection2=0;
bool breakTheLoop=1, playAgain=1;
string pacManName1, pacManName2;
clock_t start;
struct PersonResult
{
    string nameOfPerson;
    int scoreOfPerson;
};

vector <PersonResult> peopleAndScores;
vector <PersonResult> vectorSorter(vector <PersonResult>);

int main()
{
    /* Board testBoard(17);
     testBoard.setPosition(1,5,horizontal);
     testBoard.setPosition(1,6,horizontal);
     //testBoard.setPosition(1,8,vertical);
     //testBoard.setPosition(1,10,horizontal);
     testBoard.setPosition(2,4,vertical);
     testBoard.setPosition(2,7,vertical);
     //testBoard.setPosition(2,8,vertical);
     //testBoard.setPosition(2,10,vertical);
     testBoard.setPosition(3,4,vertical);
     testBoard.setPosition(3,7,vertical);
     //testBoard.setPosition(3,9,horizontal);
     testBoard.setPosition(4,5,horizontal);
     testBoard.setPosition(4,6,horizontal);
     testBoard.setPosition(9,2,horizontal);
     testBoard.setPosition(9,3,horizontal);
     testBoard.setPosition(10,1,vertical);
     testBoard.setPosition(10,4,vertical);
     testBoard.setPosition(11,2,horizontal);
     testBoard.setPosition(11,3,horizontal);

     //testBoard.showBoard();*/
    updateHighScore();
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
                        saveTheScore(pacMan.getPacManName(), pacMan.getEatenBerries());
                        updateHighScore();
                        Sleep(100);
                    }

                    else if(breakTheLoop==0)
                    {
                        cout<<"You entered a no way out area."<<endl;
                        saveTheScore(pacMan.getPacManName(), pacMan.getEatenBerries());
                        updateHighScore();
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
            showHighScore();
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
    gameOver(board, pacMan);

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
    //a moze tu jest taki blad, ze te zmienne tymczasowe m2n itd nie sa na biezaca kasowane tak jak powinny byc
    // i mam ten stack overflow o ktorym mowil michal i moze powiny to byc zmienne globalne, ktorym tutj przypisywane
    //sa po prostu kolejno noewe wartosci!!! worth a try

    char //m2m1=board->getSign((pacMan->getLocationX()-2),(pacMan->getLocationY()-1)),
    //m2n= board->getSign((pacMan->getLocationX()-2),(pacMan->getLocationY()  )),
    //m2p1=board->getSign((pacMan->getLocationX()-2),(pacMan->getLocationY()+1)),
    //m1m2=board->getSign((pacMan->getLocationX()-1),(pacMan->getLocationY()-2)),
    //m1m1=board->getSign((pacMan->getLocationX()-1),(pacMan->getLocationY()-1)),
    m1n= board->getSign((pacMan->getLocationX()-1),(pacMan->getLocationY()  )),
    //m1p1=board->getSign((pacMan->getLocationX()-1),(pacMan->getLocationY()+1)),
    //m1p2=board->getSign((pacMan->getLocationX()-1),(pacMan->getLocationY()+2)),
    //nm2= board->getSign((pacMan->getLocationX()  ),(pacMan->getLocationY()-2)),
    nm1= board->getSign((pacMan->getLocationX()  ),(pacMan->getLocationY()-1)),
    np1= board->getSign((pacMan->getLocationX()  ),(pacMan->getLocationY()+1)),
    //np2= board->getSign((pacMan->getLocationX()  ),(pacMan->getLocationY()+2)),
    //p1m2=board->getSign((pacMan->getLocationX()+1),(pacMan->getLocationY()-2)),
    //p1m1=board->getSign((pacMan->getLocationX()+1),(pacMan->getLocationY()-1)),
    p1n= board->getSign((pacMan->getLocationX()+1),(pacMan->getLocationY()  ));
    //p1p1=board->getSign((pacMan->getLocationX()+1),(pacMan->getLocationY()+1)),
    //p1p2=board->getSign((pacMan->getLocationX()+1),(pacMan->getLocationY()+2)),
    //p2m1=board->getSign((pacMan->getLocationX()+2),(pacMan->getLocationY()-1)),
    //p2n= board->getSign((pacMan->getLocationX()+2),(pacMan->getLocationY()  ));
    //p2p1=board->getSign((pacMan->getLocationX()+2),(pacMan->getLocationY()+1));

    //0
    if ((m1n==horizontal)&&(p1n==horizontal)&&(nm1==vertical)&&(np1==vertical))
    {
        return 1;
    }
    /* //1
     else if ( (m1n==horizontal)&&(p2n==horizontal)&&(nm1==vertical)&&(np1==vertical)&&(p1p1==vertical)&&(p1m1==vertical) )
     {
         return 1;
     }

     //2
     else if ( (m2n==horizontal)&&(p1n==horizontal)&&(np1==vertical)&&(nm1==vertical)&&(m1p1==vertical)&&(m1m1==vertical) )
     {
         return 1;
     }

     //3
     else if ( (nm1==vertical)&&(np2==vertical)&&(p1n==horizontal)&&(p1p1==horizontal)&&(m1n==horizontal)&&(m1p1==horizontal) )
     {
         return 1;
     }

     //4
     else if ( (np1==vertical)&&(nm2==vertical)&&(p1m1==horizontal)&&(p1n==horizontal)&&(m1m1==horizontal)&&(m1n==horizontal) )
     {
         return 1;
     }

     //5
     else if ( (m1n==horizontal)&&(m1p1==horizontal)&&(p2n==horizontal)&&(p2p1==horizontal)
               &&(nm1==vertical)&&(p1m1==vertical)&&(np2==vertical)&&(p1p2==vertical) )
     {
         return 1;
     }

     //6
     else if ( (m1m1==horizontal)&&(m1n==horizontal)&&(p2n==horizontal)&&(p2m1==horizontal)
               &&(nm2==vertical)&&(np1==vertical)&&(p1m2==vertical)&&(p1p1==vertical) )
     {
         return 1;
     }

     //7
     else if ( (m2n==horizontal)&&(m2p1==horizontal)&&(p1n==horizontal)&&(p1p1==horizontal)
               &&(m1m1==vertical)&&(nm1==vertical)&&(m1p2==vertical)&&(np2==vertical) )
     {
         return 1;
     }

     //8
     else if ( (m2m1==horizontal)&&(m2n==horizontal)&&(p1m1==horizontal)&&(p1n==horizontal)
               &&(m1m2==vertical)&&(nm2==vertical)&&(m1p1==vertical)&&(np1==vertical) )
     {
         return 1;
     }


    */
    else
        return 0;
}


void saveTheScore(string nickName, int score)
{
    ofstream highScore;
    highScore.open("highScore.txt", ios::out | ios::ate | ios::in); //flags set to add things at the end

    if (highScore.is_open())
    {
        highScore<<nickName<<endl;
        highScore<<score<<endl;
        highScore.close();
    }

    else
        cout<<"Error occurred!"<<endl;
}


void updateHighScore()
{
    string tempValue;
    ifstream highScore;
    highScore.open("highScore.txt");  //default flag is ios::in

    if (highScore.is_open())
    {
        while(!highScore.eof())
        {
            PersonResult tempPerson;
            highScore>>tempPerson.nameOfPerson;
            highScore>>tempPerson.scoreOfPerson;
            peopleAndScores.push_back(tempPerson);
        }
        highScore.close();

    }

    else
        cout<<"There is no high score yet."<<endl;
}

void showHighScore()
{
    peopleAndScores=vectorSorter(peopleAndScores);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
    cout<<"\nTHE TOP 10 PLAYERS\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    if (peopleAndScores.size()>10)
    {
        for (int i=0; i<10; i++)
        {
            cout.setf(ios::left);
            cout.width(4);
            cout<<i+1;
            cout.setf(ios::left);
            cout.width(9);
            cout<<peopleAndScores[i].nameOfPerson<<"    ";
            cout<<peopleAndScores[i].scoreOfPerson<<endl;
        }
    }

    else
    {
        for (int i=0; i<peopleAndScores.size()-1; i++)
        {
            cout.setf(ios::left);
            cout.width(4);
            cout<<i+1;
            cout.setf(ios::left);
            cout.width(9);
            cout<<peopleAndScores[i].nameOfPerson<<"    ";
            cout<<peopleAndScores[i].scoreOfPerson<<endl;
        }
    }
}


vector <PersonResult> vectorSorter(vector <PersonResult> peoplesAndScores)
{
    PersonResult tempPerson;

    for (int j=0; j<peoplesAndScores.size()-1; j++)
    {
        for (int i=0; i<peoplesAndScores.size()-1; i++)
        {
            if (peoplesAndScores[i+1].scoreOfPerson>peoplesAndScores[i].scoreOfPerson)
            {
                tempPerson=peoplesAndScores[i];
                peoplesAndScores[i]=peoplesAndScores[i+1];
                peoplesAndScores[i+1]=tempPerson;
            }
        }

    }

      return peoplesAndScores;
}
