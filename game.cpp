#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

Game::Game() : score(0), gameOver(false), lastInput(RIGHT) {
    srand(static_cast<unsigned>(time(nullptr)));
    fruit.spawn(snake);
}

void Game::draw() {
    system("cls");
    for (int i = 0; i < WIDTH; ++i) std::cout << "*";
    std::cout << std::endl;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == 0 || x == WIDTH - 1) {
                std::cout << "*";
            } else {
                Point current(x, y);
                if (snake.getHead() == current)
                    std::cout << "O";
                else if (snake.isPointInBody(current, false))
                    std::cout << "o";
                else if (!fruit.getIsEaten() && fruit.getPosition() == current)
                    std::cout << "F";
                else
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < WIDTH; ++i) std::cout << "*";
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}

void Game::input() {
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
        case 'a': case 'A': lastInput = LEFT; break;
        case 'd': case 'D': lastInput = RIGHT; break;
        case 'w': case 'W': lastInput = UP; break;
        case 's': case 'S': lastInput = DOWN; break;
        case 'x': case 'X': gameOver = true; break;
        }
    }
    if (lastInput != STOP) {
        snake.setDirection(lastInput);
    }
}

void Game::logic() {
    bool grew = false;

    if (!fruit.getIsEaten() && snake.getHead() == fruit.getPosition()) {
        fruit.setEaten(true);
        score += 10;
        grew = true;
    }

    snake.move(grew);

    if (fruit.getIsEaten()) {
        fruit.spawn(snake);
    }

    Point head = snake.getHead();
    if (head.x <= 0 || head.x >= WIDTH - 1 || head.y < 0 || head.y >= HEIGHT) {
        gameOver = true;
    }

    if (snake.isPointInBody(head, false)) {
        gameOver = true;
    }
}

void Game::run() {
    // Небольшая пауза перед началом, чтобы увидеть первое поле
    draw();
    std::cout << "Press any key to start...";
    _getch();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(INITIAL_SPEED);
    }
    system("cls");
    std::cout << "********************" << std::endl;
    std::cout << "*    GAME OVER     *" << std::endl;
    std::cout << "********************" << std::endl;
    std::cout << "Your score: " << score << std::endl;
    std::cout << "Press any key to exit..." << std::endl;
    _getch();
}