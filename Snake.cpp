#include<SFML/Graphics.hpp>
#include<iostream>
#include "Snake.h"
#include <bits/stdc++.h>
 Snake::Snake(int height, int width)
{
    this->height=height;
    this->width=width;
    this->state=Running;
    elapsedTime=0;
//    this->Mode=gameMode;
    for(int playerNumber=0; playerNumber<11; playerNumber++ )
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
     Startrow[snakeLenght] = width / 2;
     Startcol[snakeLenght] = height / 2;
     board[Startrow[snakeLenght]][Startcol[snakeLenght]].hasHead = true;

    findFood();
}

int  Snake::getPoints(int x) {
    return points[x];
}
float Snake::getElapsedTime() {
    return elapsedTime;
}
int Snake::headCol() {
    int col=head()%10;
    return col;
}

int Snake::headRow() {
    int row=head()/10;
    return row;
}
int Snake::getWidth() {
    return width;
}

int Snake::getHeight() {
    return height;
}

GameStatus Snake::getGameStatus() {
    return state;
}
void Snake::setGameMode(GameMode mode) {
    if (mode == Easy) {
        elapsedTime=0.7;
    }
    if (mode == Medium) {

        elapsedTime=0.5;
    }
    if (mode == Hard) {

        elapsedTime=0.4;
    }
}
int Snake::head() {
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
char Snake::getCharInfo(int x, int y)
{
    if(x>height || x<0 || y>width || y<0)
    {
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

void Snake::CheckIfLose() {
    int row =headRow();
    int col=headCol();
    if ((board[row][col].hasHead && board[row][col].hasTrap) || (board[row][col].hasHead && board[row][col].hasBody))
    {
        state=Lost;
        points[15]=points[currentPlayer];
        return;
    }
}
void Snake::Debug_Display()
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

//void Snake::gameSpeed() {
//   sf::Clock clk;
//while(true) {
//    if (clk.getElapsedTime().asSeconds() > 2)
//    {
//        Movement(3);
//        Debug_Display();
//        clk.restart();
//        break;
//    }
//}
//}
void Snake::findFood() {
    if (state == Lost) {
        return;
    }
    int col = rand() % width;
    int row = rand() % height;
    while (board[row][col].hasFood || board[col][row].hasBody || board[col][row].hasTrap || board[col][row].hasHead) {
        col=rand() %width;
        row=rand() %height;
        }
    board[row][col].hasFood=true;
    }
void Snake::eat() {
    int col=headCol();
    int row=headRow();
    if(board[row][col].hasHead && board[row][col].hasFood)
    {
        snakeLenght++;
        board[row][col].hasFood=false;
        findFood();
        Startrow[snakeLenght]=row;
        Startcol[snakeLenght]=col;
        points[currentPlayer]++;
    }
}
void Snake::Movement(int turn) {
    if(turn>4 || turn<0 )
    {
        return;
    }
    CheckIfLose();
    if(state==Lost)
    {
        return;
    }
    board[Startrow[snakeLenght]][Startcol[snakeLenght]].hasHead=false;
    for(int i=1; i<snakeLenght; i++)
    {
        board[Startrow[i]][Startcol[i]].hasBody=false;
    }
    eat();

       for (int i = 1; i < snakeLenght; i++) {
            //std::cout<<Startcol[i]<<" "<<i<< std::endl;
           Startcol[i] = Startcol[i + 1];
           Startrow[i] = Startrow[i + 1];
            //std::cout<<Startcol[i]<<" "<<i<< std::endl;
           board[Startrow[i]][Startcol[i]].hasBody = true;
   }
    if(turn==1)//dol
    {
        Startrow[snakeLenght]++;
    }
    if(turn==2)//gora
    {
        Startrow[snakeLenght]--;
    }
    if(turn==3)//prawo
    {
        Startcol[snakeLenght]++;
    }
    if(turn==4)//lewo
    {
        Startcol[snakeLenght]--;
    }
    board[Startrow[snakeLenght]][Startcol[snakeLenght]].hasHead=true;
 eat();

}
void Snake::saveOutcome() {
    std::ofstream outcome;
    outcome.open("bazaWynikow.txt");
   sortPoints();
    if(!outcome)
    {
        std::cerr<<"can't open bazaWynikow.txt";
    }
    else {
        for (int playerNumber = 0; playerNumber < 11; playerNumber++) {
            outcome<<points[playerNumber]<<std::endl;
        }
    }
    outcome.close();

}

void Snake::loadOutcome() {
    std::ifstream outcome;
    outcome.open("bazaWynikow.txt");
    if(!outcome)
    {
        std::cerr<<"can't load bazaWynikow.txt";
    }

        for (int playerNumber = 0; playerNumber < 11; playerNumber++) {
           outcome>>points[playerNumber];
        }
    outcome.close();

}
int Snake::loadNrPlayer() {
    for(int playerNumber=0; playerNumber<11;playerNumber++)
    {
        if(points[playerNumber]==0)
        {
            return playerNumber;
        }

    }
    return 10;
}
void Snake::sortPoints() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (points[j] < points[j + 1]) {
                std::swap(points[j], points[j + 1]);
            }
        }
    }

}
void Snake::debugPoints() {
    for (int playerNumber = 0; playerNumber < 11; playerNumber++)
    {
        std::cout<<playerNumber<<" "<<points[playerNumber]<<std::endl;
    }

}

//int Snake::getCurrentPlayer() {
//    return currentPlayer;
//}

//void Snake::control(char wasd) {
//    if(numberofturns%2==0)
//    {
//        if(wasd=='w')//gora
//        {
//            Movement(2);
//            numberofturns++;
//        }
//        if(wasd=='s')//dol
//        {
//            Movement(1);
//            numberofturns++;
//        }
//    }
//    else{
//        if(wasd=='a')//lewo
//        {
//            Movement(4);
//            numberofturns++;
//        }
//        if(wasd=='d')//prawo
//        {
//            Movement(3);
//            numberofturns++;
//        }
//    }
//}
