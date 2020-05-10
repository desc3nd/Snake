
#include<iostream>
#include "Snake.h"
#include <bits/stdc++.h>
Snake::Snake(int height, int width)
{
    this->height=height;
    this->width=width;
    this->state=Running;
    elapsedTime=0;
    ate=false;
    //zerowanie
    for(int Segments=0; Segments<100; Segments++)
    {
        snakeSegments[Segments]->row=0;
        snakeSegments[Segments]->col=0;
    }
    for(int row=0; row<100;row++)
    {
        for(int col=0; col<100; col++)
        {
            board[row][col].hasHead=false;
            board[row][col].hasBody=false;
            board[row][col].hasTrap=false;
            board[row][col].hasFood=false;
        }
    }

    for(int playerNumber=0; playerNumber<13; playerNumber++)
    {
        points[playerNumber]=0;
    }
    loadOutcome();
    points[10]=0;
    currentPlayer=loadNrPlayer();
    for(int col=0; col<width; col++)
    {
        board[0][col].hasTrap=true;
        board[height-1][col].hasTrap=true;
    }
    for(int row=0; row<height; row++ ) {
        board[row][0].hasTrap = true;
        board[row][width - 1].hasTrap = true;
    }
    snakeLenght=1;
    snakeSegments[snakeLenght]->col=width/2;
    snakeSegments[snakeLenght]->row=height/2;
    board[snakeSegments[snakeLenght]->row][snakeSegments[snakeLenght]->col].hasHead=true;

    findFood();
}

int  Snake::getPoints(int  x) const
{
    if(x>12 || x<0)
    {
        std::cerr<<"blad rozmiarow getPoints";
        return -1;
    }
    return points[x];
}
float Snake::getElapsedTime() const
{
    return elapsedTime;
}
int Snake::headCol() const
{
    int col=head()%10;
    return col;
}

int Snake::headRow()const
{
    int row=head()/10;
    return row;
}
int Snake::getWidth() const
{
    return width;
}

int Snake::getHeight() const
{
    return height;
}

GameStatus Snake::getGameStatus() const
{
    return state;
}
void Snake::setGameMode(GameMode mode)
{
    if (mode == Easy)
    {
        elapsedTime=0.7;
    }
    if (mode == Medium)
    {

        elapsedTime=0.5;
    }
    if (mode == Hard)
    {

        elapsedTime=0.4;
    }
}
int Snake::head () const
{
    for(int row=0; row < height; row++)
    {
        for (int col=0; col < width; col++)
        {
            if (board[row][col].hasHead)
            {
                return row*10+col;
            }
        }
    }
    return 0;
}
char Snake::getCharInfo(int x, int y) const
{
    if(x>height || x<0 || y>width || y<0)
    {
        std::cerr<<"blad rozmiarow getchar";
        exit(1);
    }
    else if(board[x][y].hasTrap)
    {
        return '*';
    }
    else if(board[x][y].hasHead)
    {
        return 'O';
    }
    else if(board[x][y].hasBody)
    {
        return 'o';
    }
    else if(board[x][y].hasFood)
    {
        return 'f';
    }
    return ' ';
}

void Snake::CheckIfLose()
{
    int row =headRow();
    int col=headCol();
    if ((board[row][col].hasHead && board[row][col].hasTrap) || (board[row][col].hasHead && board[row][col].hasBody))
    {
        state=Lost;
        points[12]=points[currentPlayer];
        return;
    }
}
void Snake::Debug_Display() const
{
    for(int row=0; row<height; row++)
    {
        for(int col=0; col<width; col++)
        {
            if(board[row][col].hasTrap)
            {
                std::cout<<"*";
            }
            else if(board[row][col].hasBody)
            {
                std::cout<<"o";
            }
            else if(board[row][col].hasHead)
            {
                std::cout<<"O";
            }

            else if(board[row][col].hasFood)
            {
                std::cout<<"f";
            }
            else
                std::cout<<"_";
        }
        std::cout<<std::endl;
    }
    debugPoints();
}
void Snake::findFood()
{
    bool ifGood=false;
    if (state == Lost)
    {
        return;
    }
    int col = rand() % width;
    int row = rand() % height;
    while(!ifGood)
    {
        if(board[row][col].hasFood || board[col][row].hasBody || board[col][row].hasTrap || board[col][row].hasHead)
        {
            col=rand() %width;
            row=rand() %height;
        }
        else
        {
            board[row][col].hasFood=true;
            ifGood=true;
        }

    }
}
void Snake::eat()
{
    int col=headCol();
    int row=headRow();
    if( board[row][col].hasFood)
    {
        snakeLenght++;
        board[row][col].hasFood=false;
        findFood();
        snakeSegments[snakeLenght]->col=col;
        snakeSegments[snakeLenght]->row=row;
        points[currentPlayer]++;
        ate=true;
    }
    else
    {
        ate=false;
    }
}
void Snake::Movement(int x)
{
    if(x>4 || x<0 )
    {
        return;
    }
    CheckIfLose();
    if(state==Lost)
    {
        return;
    }
    eat();
    board[snakeSegments[snakeLenght]->row][snakeSegments[snakeLenght]->col].hasHead=false;

    if(ate)
    {
        board[snakeSegments[snakeLenght]->row][snakeSegments[snakeLenght]->col].hasBody=true;
        turn(x);
        board[snakeSegments[snakeLenght]->row][snakeSegments[snakeLenght]->col].hasHead=true;
        return;
    }
    else
    {
        for (int i = 1; i < snakeLenght; i++)
        {
            board[snakeSegments[i]->row][snakeSegments[i]->col].hasBody=false;
        }

        for (int i = 1; i < snakeLenght; i++)
        {
            snakeSegments[i]->row=snakeSegments[i+1]->row;
            snakeSegments[i]->col=snakeSegments[i+1]->col;
            board[snakeSegments[i]->row][snakeSegments[i]->col].hasBody=true;
        }
        turn(x);
        board[snakeSegments[snakeLenght]->row][snakeSegments[snakeLenght]->col].hasHead=true;
    }
}
void Snake::saveOutcome()
{
    std::ofstream outcome;
    outcome.open("bazaWynikow.txt");
    sortPoints();
    if(!outcome)
    {
        std::cerr<<"can't open bazaWynikow.txt";
    }
    else
    {
        for (int playerNumber = 0; playerNumber < 11; playerNumber++)
        {
            outcome<<points[playerNumber]<<std::endl;
        }
    }
    outcome.close();

}

void Snake::loadOutcome()
{
    std::ifstream outcome;
    outcome.open("bazaWynikow.txt");
    if(!outcome)
    {
        std::cerr<<"can't load bazaWynikow.txt";
    }

    for (int playerNumber = 0; playerNumber < 11; playerNumber++)
    {
        outcome>>points[playerNumber];
    }
    outcome.close();

}
int Snake::loadNrPlayer() const
{
    for(int playerNumber=0; playerNumber<11;playerNumber++)
    {
        if(points[playerNumber]==0)
        {
            return playerNumber;
        }

    }
    return 10;
}
void Snake::sortPoints()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (points[j] < points[j + 1])
            {
                std::swap(points[j], points[j + 1]);
            }
        }
    }

}
void Snake::debugPoints() const
{
    for (int playerNumber = 0; playerNumber < 11; playerNumber++)
    {
        std::cout<<playerNumber<<" "<<points[playerNumber]<<std::endl;
    }

}

void Snake::turn(int turn)
{
    if(turn<0 || turn>4)
    {
        return;
    }
    if(turn==1)//dol
    {
        snakeSegments[snakeLenght]->row++;
    }
    if(turn==2)//gora
    {
        snakeSegments[snakeLenght]->row--;
        ;
    }
    if(turn==3)//prawo
    {
        snakeSegments[snakeLenght]->col++;

    }
    if(turn==4)//lewo
    {
        snakeSegments[snakeLenght]->col--;
    }

}