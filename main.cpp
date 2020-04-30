
#include <iostream>
#include <chrono>
#include<SFML/Graphics.hpp>
#include"Snake.h"
#include "SnakeView.h"
#include "SFMLGraphic.h"
int main() {
    srand(time(0));
   Snake x(10,10,Easy);
   //x.Debug_Display();

  //  x.Movement(3);
    //x.Movement(3);
    SnakeView view(x);
   view.display();    //x.gameSpeed();
   SFMLGraphic graphic(x);
    sf::RenderWindow win(sf::VideoMode(graphic.getScreenX(), graphic.getScreenY()), "Saper");
    sf::Event event;
    while (win.isOpen()) {
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }
        }
    }




}