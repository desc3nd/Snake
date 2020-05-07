

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

enum GameMode{Easy,Medium,Hard};
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
    GameStatus state;
    int points[15];
    int snakeLenght=3;
    int currentPlayer;
    float elapsedTime;
    void findFood();
    void eat();
    void CheckIfLose();
    int head();
    int headCol();
    int headRow();
    int loadNrPlayer();
    void loadOutcome();

public:
    Snake(int height, int width);
    void Debug_Display();
    void Movement(int turn);
    char getCharInfo(int x, int y);
    int getWidth();
    int getHeight();
    GameStatus getGameStatus();
//    void control(char wasd);
//    void gameSpeed();
    void setGameMode(GameMode mode);
    void debugPoints();
    void saveOutcome();
    int getPoints(int x);
//    int getCurrentPlayer();
    void sortPoints();
    float getElapsedTime();
};


#endif //SNAKE_SNAKE_H
