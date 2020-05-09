
#ifndef SNAKE_SNAKEVIEW_H
#define SNAKE_SNAKEVIEW_H

#include"Snake.h"
class SnakeView
{
    Snake &snake;
    int height;
    int width;
public:
    explicit SnakeView(Snake &x);

    void display();

};


#endif //SNAKE_SNAKEVIEW_H
