
#ifndef SNAKE_SFMLGRAPHIC_H
#define SNAKE_SFMLGRAPHIC_H
#include<SFML/Graphics.hpp>
#include"Snake.h"

class SFMLGraphic {
Snake &snake;
int height;
int width;
int ScreenX;
int ScreenY;
public:
    explicit SFMLGraphic(Snake &x);
    int getScreenX();
    int getScreenY();
};


#endif //SNAKE_SFMLGRAPHIC_H
