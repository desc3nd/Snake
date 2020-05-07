
#include <iostream>
#include <chrono>
#include<SFML/Graphics.hpp>
#include"Snake.h"
#include "SnakeView.h"
#include "SFMLGraphic.h"
#include "SnakeSFMLController.h"

int main() {
    bool matchStarted=false;
    srand(time(0));
    Snake x(10, 10);
    sf::Clock clk;
    SnakeView view(x);
    view.display();
    SFMLGraphic graphic(x);
    SnakeSFMLController ctrl(x, graphic);
    sf::RenderWindow win(sf::VideoMode(graphic.getScreenX(), graphic.getScreenY()), "Saper");
    win.setVerticalSyncEnabled(true);
    sf::Event event;
    while (win.isOpen()) {
            while (win.pollEvent(event)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        std::cout << "X:" << event.mouseButton.x << std::endl;
                        std::cout << "Y:" << event.mouseButton.y << std::endl;
                        ctrl.menuControl(event);
                    }
                }
                if (ctrl.getChoosen()) {
                    ctrl.StartGame();
                    if (ctrl.getEnterStatus()) {
                        ctrl.play();
                        matchStarted=true;
                        //x.gameSpeed();
                    }
                }
                if (event.type == sf::Event::Closed) {
                    x.saveOutcome();
                    win.close();
                }
            }

            if(clk.getElapsedTime().asSeconds()>x.getElapsedTime() && matchStarted && x.getGameStatus() == Running)
            {
            for(int i=1; i<=4;i++)
            {
                ctrl.moving(i);
            }
            graphic.drawBoard();
            //x.Debug_Display();
            clk.restart();
            }
            win.clear(sf::Color::Black);
            win.draw(graphic);
            win.display();

        }
    }
