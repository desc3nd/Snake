
#include <iostream>
#include<SFML/Graphics.hpp>
#include"Snake.h"
#include "SnakeView.h"
#include "SFMLGraphic.h"
#include "SnakeSFMLController.h"

int main()
{
    bool matchStarted=false;
    srand(time(0));
    Snake x(10, 10);
    sf::Clock clk;
    SnakeView view(x);
    view.display();
    SFMLGraphic graphic(x);
    SnakeSFMLController ctrl(x, graphic);
    sf::RenderWindow win(sf::VideoMode(graphic.getScreenX(), graphic.getScreenY()), "Snake");
    win.setVerticalSyncEnabled(true);
//    x.Movement(20);
//    x.getCharInfo(30,60);
//    x.getPoints(30);
    sf::Event event;
    while (win.isOpen())
    {
            while (win.pollEvent(event))
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        ctrl.menuControl(event);
                    }
                }
                if (ctrl.getChoosen())
                {
                    ctrl.StartGame();
                    if (ctrl.getEnterStatus())
                    {
                        ctrl.play();
                        matchStarted=true;

                    }
                }
                if (event.type == sf::Event::Closed)
                {
                    x.saveOutcome();
                    x.Debug_Display();
                    win.close();
                }
            }
            if(clk.getElapsedTime().asSeconds()>x.getElapsedTime() && matchStarted && x.getGameStatus() == Running)
            {
                ctrl.moving();
                graphic.drawBoard();
                clk.restart();
                x.Debug_Display();
            }
            win.clear(sf::Color::Black);
            win.draw(graphic);
            win.display();
        }
    }
