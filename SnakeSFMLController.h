//
// Created by Marcinek on 01.05.2020.
//

#ifndef SNAKE_SNAKESFMLCONTROLLER_H
#define SNAKE_SNAKESFMLCONTROLLER_H
#include"SFMLGraphic.h"
#include"Snake.h"

class SnakeSFMLController
{
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
    bool getChoosen() const;
    bool getEnterStatus() const;
    void StartGame() ;
    void moving() const;

};


#endif //SNAKE_SNAKESFMLCONTROLLER_H
