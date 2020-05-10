#include "SFMLGraphic.h"
#include<iostream>
SFMLGraphic::SFMLGraphic(Snake &x):snake(x)
{
    height = snake.getHeight();
    width = snake.getWidth();
    ScreenX = 1000;
    ScreenY = 1000;
    nrOfButtons=4;
    shapeAmount=20;
    for (int i = 0; i < shapeAmount; i++)
    {
        for (int j = 0; j < shapeAmount; j++)
        {
            shape[i][j].setRadius(40);
            shape[i][j].setFillColor(sf::Color::Transparent);
        }
    }
    if(!texture[0].loadFromFile("Easy.png")|| !texture[1].loadFromFile("Medium.png")|| !texture[2].loadFromFile("Hard.png") || !texture[3].loadFromFile("Exit.png") || !w8Texture.loadFromFile("PressToStart.png"))
    {
        std::cerr<<"blad przy wczytaniu tekstury";
    }
    if(!font.loadFromFile("arial.ttf"))
    {
        std::cerr<<"blad przy wczytaniu czcionki";
    }
    drawMenu();

}
int SFMLGraphic::getScreenX() const
{
    return ScreenX;
}

int SFMLGraphic::getScreenY() const
{
    return ScreenY;
}

void SFMLGraphic::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
int pointsAmount=10;
    for(int i=0;i<nrOfButtons;i++)
    {
        target.draw(menuButtons[i],states);
    }
    target.draw(w8,states);
    target.draw(gameBackGround,states);
    for(int i=0; i<shapeAmount; i++)
    {
        for (int j = 0; j < shapeAmount; j++)
        {
            target.draw(shape[i][j], states);
        }
    }
    target.draw(lostBackGround,states);
    target.draw(text,states);
    for(int i=0; i<pointsAmount; i++)
    {
        target.draw(points[i],states);
        target.draw(bestOutcomes[i],states);
        target.draw(playernr[i],states);
    }
    target.draw(bestOutcomes[10],states);
    target.draw(playernr[10],states);
    target.draw(bestOutcomes[0],states);
    target.draw(points[12],states);

    target.draw(yourScore,states);
}

void SFMLGraphic::drawBoard()
{
    int thickness=180;
    gameBackGround.setSize(sf::Vector2f(ScreenX-thickness,ScreenY-thickness));
    gameBackGround.setFillColor(sf::Color::Black);
    gameBackGround.setPosition(sf::Vector2f(thickness/2,thickness/2));
    gameBackGround.setOutlineThickness(thickness);
    gameBackGround.setOutlineColor(sf::Color::White);
    for(int row=0; row<height; row++)
    {  int positionY=row*100;
        for(int col=0; col<width; col++)
        {
            int positionX=col*100;
            if(snake.getCharInfo(row,col)==' ')
            {
                shape[row][col].setFillColor(sf::Color::Transparent);
            }
            if(snake.getCharInfo(row,col)=='f')
            {
                shape[row][col].setPosition(positionX,positionY);
                shape[row][col].setFillColor(sf::Color::Red);
            }
            if( snake.getCharInfo(row,col)=='O')
            {
                shape[row][col].setPosition(positionX,positionY);
                shape[row][col].setFillColor(sf::Color::Magenta);
            }
            if(snake.getCharInfo(row,col)=='o')
            {
                shape[row][col].setPosition(positionX,positionY);
                shape[row][col].setFillColor(sf::Color::Yellow);
            }

            if(snake.getGameStatus()==Lost)
            {
                drawGameOver();
                drawPointsText();
                drawYourScoreText();
                drawNumbers();
            }

        }
    }
}

void SFMLGraphic::drawMenu()
{
    int spaceBetween=125;
    for(int i=0;i<nrOfButtons;i++)
    {
        menuButtons[i].setPosition(sf::Vector2f((ScreenX/2-278/2),(spaceBetween)));
        menuButtons[i].setSize(sf::Vector2f(277,123));//rozmiar obrazka
        menuButtons[i].setTexture(&texture[i]);
        spaceBetween+=ScreenY/5;
    }

}

void SFMLGraphic::drawW8menu()
{
    w8.setTexture(&w8Texture);
    w8.setSize(sf::Vector2f(ScreenX,ScreenY));
}

void SFMLGraphic::drawGameOver()
{
    lostBackGround.setSize(sf::Vector2f(ScreenX,ScreenY));
    lostBackGround.setFillColor(sf::Color::Black);
    text.setFont(font);
    text.setPosition(sf::Vector2f(250,0));
    text.setCharacterSize(100);
    text.setString("Game Over");
}

void SFMLGraphic::drawPointsText()
{
    int current=12;
    int nbOfPlayers=10;
    int outcome=snake.getPoints(current);
    std::string _str= std::to_string(outcome);
    points[current].setFont(font);
    points[current].setFillColor(sf::Color::Red);
    points[current].setPosition(sf::Vector2f(600,150));
    points[current].setCharacterSize(50);
    points[current].setString(_str);
    int outcomePosition=300;
    snake.sortPoints();
    for(int player=0; player<nbOfPlayers;player++)
    {
        outcomePosition+=50;
        points[player].setFont(font);
        points[player].setPosition(sf::Vector2f(550,outcomePosition));
        points[player].setCharacterSize(40);
        int outcome=snake.getPoints(player);
        std::string _str = std::to_string(outcome);
        points[player].setString(_str);
    }

}

void SFMLGraphic::drawYourScoreText()
{

    yourScore.setFont(font);
    yourScore.setPosition(sf::Vector2f(350,150));
    yourScore.setFillColor(sf::Color::Red);
    yourScore.setCharacterSize(50);
    yourScore.setString("Your score:");

}

void SFMLGraphic::drawNumbers()
{
   float position=300;
    for(int i=1; i<=10; i++)
    {
        position+=50;
        playernr[i].setFont(font);
        playernr[i].setCharacterSize(40);
        playernr[i].setPosition(250,position);
        playernr[i].setString("Player");
        std::string _str= std::to_string(i);
        bestOutcomes[i].setFont(font);
        bestOutcomes[i].setPosition(sf::Vector2f(400,position));
        bestOutcomes[i].setCharacterSize(40);
        bestOutcomes[i].setString(_str);

    }
    bestOutcomes[0].setFont(font);
    bestOutcomes[0].setPosition(sf::Vector2f(350,220));
    bestOutcomes[0].setCharacterSize(50);
    bestOutcomes[0].setString("Best scores:");

}

