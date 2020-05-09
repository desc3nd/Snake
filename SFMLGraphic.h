
#ifndef SNAKE_SFMLGRAPHIC_H
#define SNAKE_SFMLGRAPHIC_H
#include<SFML/Graphics.hpp>
#include"Snake.h"

class SFMLGraphic: public sf::Drawable
{
Snake &snake;
int height;
int width;
int ScreenX;
int ScreenY;
int shapeAmount;
    int nrOfButtons;
    sf::CircleShape shape[40][40];
    sf::RectangleShape gameBackGround;
    sf::RectangleShape lostBackGround;
    sf::RectangleShape menuButtons[4];
    sf::Texture texture[4];
    sf::Texture w8Texture;
    sf::RectangleShape w8;
    sf::Text text;
    sf::Font font;
    sf::Text points[13];
    sf::Text yourScore;
    sf::Text playernr[11];
    sf::Text bestOutcomes[11];
    void drawGameOver();
    void drawPointsText();
    void drawYourScoreText();
    void drawNumbers();
public:
    explicit SFMLGraphic(Snake &x);
    int getScreenX();
    int getScreenY();
    void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    void drawBoard();
    void drawMenu();
    void drawW8menu();
};


#endif //SNAKE_SFMLGRAPHIC_H
