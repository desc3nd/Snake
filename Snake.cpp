#include<SFML/Graphics.hpp>
#include<iostream>
#include "Snake.h"
#include<chrono>
 Snake::Snake(int height, int width, GameMode gameMode)
{
    this->height=height;
    this->width=width;
    this->state=Running;
    this->Mode=gameMode;
    for(int col=0; col<width; col++)
    {
        board[0][col].hasTrap=true;
        board[height-1][col].hasTrap=true;
    }
    for(int row=0; row<height; row++ ) {
        board[row][0].hasTrap = true;
        board[row][width - 1].hasTrap = true;
    }
    if((width/2 -2)>0 )
   {
     snakeLenght=3;
     Startrow[snakeLenght] = width / 2;
     Startcol[snakeLenght] = height / 2;
     Startrow[snakeLenght - 1] = width / 2;
     Startcol[snakeLenght - 1] = height / 2 - 1;
     Startrow[snakeLenght - 2] = width / 2;
     Startcol[snakeLenght - 2] = height / 2 - 2;
        if (gameMode == Easy) {
            snakeLenght=1;
        }
        if (gameMode == Medium) {
            snakeLenght=2;
            board[Startrow[snakeLenght - 1]][Startcol[snakeLenght - 1]].hasBody = true;
        }
        if (gameMode == Hard) {
            snakeLenght=3;
            board[Startrow[snakeLenght - 1]][Startcol[snakeLenght - 1]].hasBody = true;
            board[Startrow[snakeLenght - 2]][Startcol[snakeLenght - 2]].hasBody = true;
        }
        board[Startrow[snakeLenght]][Startcol[snakeLenght]].hasHead = true;

    }
else
{
        std::cerr<<"mamy blad w rozmiarach";
}
    findFood();
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
            else if(board[row][col].hasTail)
            {
                std::cout<<"t";
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
    std::cout<<head()<<" "<<headRow()<<" "<<headCol();
}

//void Snake::gameSpeed() {
//   sf::Clock clk;
//
//       if (clk.getElapsedTime().asSeconds() > 2) {
//           Movement(3);
//           clk.restart();
//       }
//
//}
void Snake::findFood() {
    if (state == Lost) {
        return;
    }
    while (true) {
        int col = rand() % width;
        int row = rand() % height;
        if (board[row][col].hasFood || board[col][row].hasBody || board[col][row].hasTrap || board[col][row].hasTail ||
            board[col][row].hasHead) {
            col = rand() % width;
            row = rand() % height;
        } else {
            board[row][col].hasFood = true;
            break;
        }
    }
}

void Snake::Movement(int turn) {
    if(state==Lost)
    {
        return;
    }

    board[Startrow[snakeLenght]][Startcol[snakeLenght]].hasHead=false;
    for(int i=1; i<snakeLenght; i++)
    {
        board[Startrow[i]][Startcol[i]].hasBody=false;
    }
for(int i = 1; i<snakeLenght; i++ )
{
    std::cout<<Startcol[i]<<" "<<i<< std::endl;
    Startcol[i]=Startcol[i+1];
    Startrow[i]=Startrow[i+1];
    std::cout<<Startcol[i]<<" "<<i<< std::endl;
    board[Startrow[i]][Startcol[i]].hasBody=true;
}
    if(turn==1)
    {
        Startrow[snakeLenght]++;
    }
    if(turn==2)
    {
        Startrow[snakeLenght]--;
    }
    if(turn==3)
    {
        Startcol[snakeLenght]++;
    }
    if(turn==4)
    {
        Startcol[snakeLenght]--;
    }
    board[Startrow[snakeLenght]][Startcol[snakeLenght]].hasHead=true;
    eat();
    CheckIfLose();
}

void Snake::control(char wasd) {
    if(numberofturns%2==0)
    {
        if(wasd=='w')//gora
        {
            Movement(2);
            numberofturns++;
        }
        if(wasd=='s')//dol
        {
            Movement(1);
            numberofturns++;
        }
    }
    else{
        if(wasd=='a')//lewo
        {
            Movement(4);
            numberofturns++;
        }
        if(wasd=='d')//prawo
        {
            Movement(3);
            numberofturns++;
        }
    }
}

void Snake::CheckIfLose() {
    int row =headRow();
    int col=headCol();
            if ((board[row][col].hasHead && board[row][col].hasTrap) || (board[row][col].hasHead && board[row][col].hasBody))
            {
                state=Lost;
                return;
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
int Snake::headCol() {
    int col=head()%10;
    return col;
}

int Snake::headRow() {
    int row=head()/10;
    return row;
}

void Snake::eat() {
    int col=headCol();
    int row=headRow();
    board[row][col+1].hasFood=true;
    if(board[row][col].hasHead && board[row][col].hasFood)
    {
        snakeLenght++;
        findFood();
    }
}

char Snake::getCharInfo(int x, int y)
{
         if(board[x][y].hasTrap)
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


int Snake::getWidth() {
    return width;
}

int Snake::getHeight() {
    return height;
}





