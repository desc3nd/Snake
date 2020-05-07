//
// Created by Marcinek on 01.05.2020.
//

#ifndef SNAKE_SNAKESFMLCONTROLLER_H
#define SNAKE_SNAKESFMLCONTROLLER_H
#include"SFMLGraphic.h"
#include"Snake.h"

class SnakeSFMLController{
        Snake &snake;
SFMLGraphic  &view;
int nrOfTurns;
bool modeChoosen;
bool enter;
int move;
public:
    SnakeSFMLController(Snake &x, SFMLGraphic &y);
    void play();
    void menuControl(sf::Event &event);
    bool getChoosen();
    bool getEnterStatus();
    void StartGame();
    //int getMove();
    void moving(int x);

};


#endif //SNAKE_SNAKESFMLCONTROLLER_H
