//
// Created by Marcinek on 30.04.2020.
//

#include "SFMLGraphic.h"

SFMLGraphic::SFMLGraphic(Snake &x):snake(x)
{
    height=snake.getHeight();
    width=snake.getWidth();
    ScreenX=1000;
    ScreenY=1000;
}

int SFMLGraphic::getScreenX() {
    return ScreenX;
}

int SFMLGraphic::getScreenY() {
    return ScreenY;
}
