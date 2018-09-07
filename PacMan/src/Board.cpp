#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;
Board::Board()
{

}

Board::Board(int boardSize)
{
    srand(time(0));
    this->boardSize=boardSize;
    matrix=new char*[boardSize];

    for (int i=0; i<boardSize; i++)
        matrix[i]=new char[boardSize];
    for (int i=1; i<boardSize-1; i++)
    {
        for (int j=1; j<boardSize-1; j++)
        {
            this->random=1+rand()%3;
            if(random==1)
                matrix[i][j]=186;
            else if(random==2)
                matrix[i][j]=205;
            else if(random==3)
                matrix[i][j]=206;
        }
    }

    for (int i=0, j=1; j<boardSize-1; j++)
        matrix[i][j]=205;
    for (int i=boardSize-1, j=1; j<boardSize; j++)
        matrix[i][j]=205;
    for (int i=1,j=0; i<boardSize-1; i++)
        matrix[i][j]=186;
    for (int i=1, j=boardSize-1; i<boardSize; i++)
        matrix[i][j]=186;

    matrix[0][0]=201;
    matrix[0][boardSize-1]=187;
    matrix[boardSize-1][0]=200;
    matrix[boardSize-1][boardSize-1]=188;

}

void Board::showBoard()
{
    for (int i=0; i<boardSize; i++)
    {
        for (int j=0; j<boardSize; j++)
        {
            if (matrix[i][j]==berryInstance)
            {
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 14 );
                cout<<matrix[i][j];
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
            }
            else if (matrix[i][j]==pacmanInstance1)
            {
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 12 );
                cout<<matrix[i][j];
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
            }
             else if (matrix[i][j]==pacmanInstance2)
            {
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 13 );
                cout<<matrix[i][j];
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
            }
            else
                cout<<matrix[i][j];
        }
        cout<<endl;
    }
}

void Board::setPosition(int positionX, int positionY, char berrieOrPacMan)
{
    matrix[positionX][positionY]=berrieOrPacMan;
}

char Board::getSign(int positionX, int positionY)
{
    if((positionX>=0)&&(positionY>=0))
    return matrix[positionX][positionY];
    else return 206;
}

void Board::gameOver()
{
    for (int i=boardSize/2-5; i<boardSize/2+6; i++)
        setPosition((boardSize/2+1),i,' ');
    for (int i=boardSize/2-5; i<boardSize/2+6; i++)
        setPosition((boardSize/2-1),i,' ');

    setPosition((boardSize/2),boardSize/2-5,' ');
    setPosition((boardSize/2),boardSize/2-4,'G');
    setPosition((boardSize/2),boardSize/2-3,'A');
    setPosition((boardSize/2),boardSize/2-2,'M');
    setPosition((boardSize/2),boardSize/2-1,'E');
    setPosition((boardSize/2),boardSize/2,' ');
    setPosition((boardSize/2),boardSize/2+1,'O');
    setPosition((boardSize/2),boardSize/2+2,'V');
    setPosition((boardSize/2),boardSize/2+3,'E');
    setPosition((boardSize/2),boardSize/2+4,'R');
    setPosition((boardSize/2),boardSize/2+5,' ');


}

int Board::getSize()
{
    return boardSize;
}

void Board::resetTheBoard()
{
    for (int i=1; i<boardSize-1; i++)
    {
        for (int j=1; j<boardSize-1; j++)
        {
            this->random=1+rand()%3;
            if(random==1)
                matrix[i][j]=186;
            else if(random==2)
                matrix[i][j]=205;
            else if(random==3)
                matrix[i][j]=206;
        }
    }

    for (int i=0, j=1; j<boardSize-1; j++)
        matrix[i][j]=205;
    for (int i=boardSize-1, j=1; j<boardSize; j++)
        matrix[i][j]=205;
    for (int i=1,j=0; i<boardSize-1; i++)
        matrix[i][j]=186;
    for (int i=1, j=boardSize-1; i<boardSize; i++)
        matrix[i][j]=186;

    matrix[0][0]=201;
    matrix[0][boardSize-1]=187;
    matrix[boardSize-1][0]=200;
    matrix[boardSize-1][boardSize-1]=188;
}

Board::~Board()
{
    delete []matrix;
}
