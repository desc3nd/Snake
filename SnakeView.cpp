using namespace std;
#include "SnakeView.h"
#include<iostream>
SnakeView::SnakeView(Snake &x) :snake(x)
{
height=snake.getHeight();
width=snake.getWidth();
}
void SnakeView::display()
{
    for(int row=0; row<height; row++)
    {
        for(int col=0; col<width; col++)
        {
            char charInf=snake.getCharInfo(row,col);
            cout<<charInf;
        }
        cout<<endl;
    }
}
