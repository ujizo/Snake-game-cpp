#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "fruit.h"

class Game {
private:
    Snake snake;
    Fruit fruit;
    int score;
    bool gameOver;
    Direction lastInput;
    void draw();
    void input();
    void logic();
public:
    Game();
    void run();
};

#endif