#include "Game.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>


bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int gameSpeed;
eDirecton dir;

void GenerateFruit() {
    bool validPosition;
    int attempts = 0;
    int maxAttempts = 1000;

    do {
        validPosition = true;
        fruitX = std::rand() % width;
        fruitY = std::rand() % height;

        if (fruitX == x && fruitY == y) {
            validPosition = false;
        }

        for (int i = 0; i < nTail && validPosition; i++) {
            if (tailX[i] == fruitX && tailY[i] == fruitY) {
                validPosition = false;
            }
        }

        attempts++;
        if (attempts > maxAttempts) {
            fruitX = std::rand() % width;
            fruitY = std::rand() % height;
            return;
        }
    } while (!validPosition);
}

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    score = 0;
    nTail = 0;
    fruitX = 5;
    fruitY = 5;
    GenerateFruit();
}

void DrawBorder() {
    gotoxy(0, 0);
    std::cout << "#";
    for (int i = 0; i < width; i++) {
        std::cout << "##";
    }
    std::cout << "#";

    for (int i = 0; i < height; i++) {
        gotoxy(0, i + 1);
        std::cout << "#";
        gotoxy(width * 2 + 1, i + 1);
        std::cout << "#";
    }

    gotoxy(0, height + 1);
    std::cout << "#";
    for (int i = 0; i < width; i++) {
        std::cout << "##";
    }
    std::cout << "#";
}

void Draw() {
    system("cls");
    DrawBorder();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            gotoxy(j * 2 + 1, i + 1);

            if (i == y && j == x) {
                std::cout << "OO";
            }
            else if (i == fruitY && j == fruitX) {
                std::cout << "()";
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "oo";
                        print = true;
                        break;
                    }
                }
                if (!print) {
                    std::cout << "  ";
                }
            }
        }
    }

    gotoxy(width * 2 + 5, 2);
    std::cout << "SNAKE GAME";

    gotoxy(width * 2 + 5, 4);
    std::cout << "SCORE: " << score;

    gotoxy(width * 2 + 5, 6);
    std::cout << "LENGTH: " << nTail + 1;

    gotoxy(width * 2 + 5, 8);
    std::cout << "CONTROLS:";
    gotoxy(width * 2 + 5, 9);
    std::cout << "WASD - move";
    gotoxy(width * 2 + 5, 10);
    std::cout << "X - exit";

    gotoxy(width * 2 + 5, 12);
    std::cout << "FRUIT: ()";
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
        case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
        case 'W':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
        case 'S':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
        case 'X':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        nTail++;
        GenerateFruit();
    }
}

void ShowGameOver() {
    system("cls");

    for (int i = 0; i < 40; i++) std::cout << "#";
    std::cout << std::endl;

    std::cout << "#" << "           GAME OVER!           " << "#" << std::endl;

    std::cout << "#" << "         FINAL SCORE: " << score << "        " << "#" << std::endl;

    std::cout << "#" << "         SNAKE LENGTH: " << nTail + 1 << "         " << "#" << std::endl;

    for (int i = 0; i < 40; i++) std::cout << "#";
    std::cout << std::endl;

    std::cout << "\nPress Enter to continue...";
    while (_getch() != 13);
}

void ShowMenu() {
    int choice = 0;

    while (true) {
        system("cls");

        std::cout << "##############################" << std::endl;
        std::cout << "#         Snake Game         #" << std::endl;
        std::cout << "##############################" << std::endl;
        std::cout << std::endl;
        std::cout << "SELECT DIFFICULTY:" << std::endl;
        std::cout << std::endl;
        std::cout << "1. EASY (Slow)" << std::endl;
        std::cout << "2. MEDIUM (Normal)" << std::endl;
        std::cout << "3. HARD (Fast)" << std::endl;
        std::cout << "4. EXIT" << std::endl;
        std::cout << std::endl;
        std::cout << "CONTROLS: W/A/S/D - movement" << std::endl;
        std::cout << "           X - exit game" << std::endl;
        std::cout << std::endl;
        std::cout << "Your choice (1-4): ";

        std::cin >> choice;

        if (choice == 4) {
            system("cls");
            std::exit(0);
        }

        if (choice >= 1 && choice <= 3) {
            switch (choice) {
            case 1: gameSpeed = 100; break;
            case 2: gameSpeed = 60; break;
            case 3: gameSpeed = 30; break;
            }

            system("cls");
            Setup();
            while (!gameOver) {
                Draw();
                Input();
                Logic();
                Sleep(gameSpeed);
            }

            ShowGameOver();
        }
    }
}