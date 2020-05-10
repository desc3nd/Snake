

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

enum GameMode{Easy,Medium,Hard};
enum GameStatus{Running,Lost};
struct field
{
    bool hasHead;
    bool hasBody;
    bool hasFood;
    bool hasTrap;
};
struct coord{
    int col;
    int row;
};

class Snake
{
    field board[100][100]{};
    coord snakeSegments[100][100]{};

    int height;
    int width;
    GameStatus state;
    int points[13];
    int snakeLenght;
    int currentPlayer;
    float elapsedTime;
    bool ate;
    void findFood();
    void eat();
    void CheckIfLose();
    int head() const;
    int headCol() const;
    int headRow() const;
    int loadNrPlayer() const;
    void loadOutcome();
  void turn(int turn);

public:
    Snake(int height, int width);
    void Debug_Display() const;
    void Movement(int x);
    char getCharInfo(int x, int y) const;
    int getWidth() const;
    int getHeight() const ;
    GameStatus getGameStatus() const;
    void setGameMode(GameMode mode);
    void debugPoints() const;
    void saveOutcome();
    int getPoints(int x ) const;
    void sortPoints();
    float getElapsedTime() const;
};


#endif //SNAKE_SNAKE_H
