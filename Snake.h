

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

enum GameMode{Easy,Medium,Hard,Debug};
enum GameStatus{Running,Lost};
struct field
{
    bool hasHead;
    bool hasTail;
    bool hasBody;
    bool hasFood;
    bool hasTrap;
};

class Snake
{
    field board[100][100];
    int Startrow[100];
    int Startcol[100];
    int height;
    int width;
    GameMode Mode;
    GameStatus state;
    void findFood();

    int numberofturns=0;
    int snakeLenght=3;
    void eat();
    void CheckIfLose();
    int head();
    int headCol();
    int headRow();


public:
    Snake(int height, int width, GameMode gameMode);
    void Debug_Display();
    void Movement(int turn);
    char getCharInfo(int x, int y);
    int getWidth();
    int getHeight();
    void control(char wasd);
    void gameSpeed();
};


#endif //SNAKE_SNAKE_H
