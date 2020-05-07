//
// Created by Marcinek on 01.05.2020.
//

#include "SnakeSFMLController.h"
#include<iostream>

SnakeSFMLController::SnakeSFMLController(Snake &x, SFMLGraphic &y) :snake(x),view(y) {
    nrOfTurns=0;
    modeChoosen=false;
    enter=false;
    move=3;
}
bool SnakeSFMLController::getChoosen() {
    return modeChoosen;
}

bool SnakeSFMLController::getEnterStatus() {
    return enter;
}

void SnakeSFMLController::StartGame() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        enter=true;
        view.drawBoard();
    }

}
void SnakeSFMLController::menuControl( sf::Event &event)
{
    int x = 361; //szerokosc kwadratu +pozycja
    int x2 = 638; //-||-
    int y = 125;//wysokosc +pozycja
    int y2 = 248;// -||-

    if (event.mouseButton.x < x2 && event.mouseButton.x > x && event.mouseButton.y < y2 && event.mouseButton.y > y)
    {
        snake.setGameMode(Easy);
        view.drawW8menu();
        play();
        modeChoosen=true;

    }
    y=y+200;//plus space between
    y2=y2+200;//plus space between
    if (event.mouseButton.x < x2 && event.mouseButton.x > x && event.mouseButton.y < y2 && event.mouseButton.y > y)
    {
        snake.setGameMode(Medium);
        view.drawW8menu();
        play();
        modeChoosen=true;

    }
    y=y+200;//plus space between
    y2=y2+200;//plus space between
    if (event.mouseButton.x < x2 && event.mouseButton.x > x && event.mouseButton.y < y2 && event.mouseButton.y > y)
    {
        snake.setGameMode(Hard);
        view.drawW8menu();
        play();
        modeChoosen=true;
    }
    y=y+200;//plus space between
    y2=y2+200;//plus space between
    if (event.mouseButton.x < x2 && event.mouseButton.x > x && event.mouseButton.y < y2 && event.mouseButton.y > y)
    {
        exit(1);
    }
}

void SnakeSFMLController::play() {
    if (nrOfTurns % 2 == 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//            snake.Movement(2);
//            snake.Debug_Display();
//            view.drawBoard();
            move = 2;
            nrOfTurns++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//            snake.Movement(1);
//            snake.Debug_Display();
//            view.drawBoard();
            move = 1;
            nrOfTurns++;
        }
    }
   else
        {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//            snake.Movement(3);
//            snake.Debug_Display();
//            view.drawBoard();
            move = 3;
            nrOfTurns++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//             snake.Movement(4);
//            snake.Debug_Display();
//            view.drawBoard();
            move = 4;
            nrOfTurns++;
        }
    }
}

void SnakeSFMLController::moving(int x) {
    if(x==move)
    {
        snake.Movement((x));
    }

}
//int SnakeSFMLController::getMove() {
//    return move;
//}

