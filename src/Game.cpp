#include "Game.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
using namespace std;

// Определение глобальных переменных
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
        fruitX = rand() % width;
        fruitY = rand() % height;

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
            fruitX = rand() % width;
            fruitY = rand() % height;
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
    setColor(CYAN);
    gotoxy(0, 0);
    cout << "#";
    for (int i = 0; i < width; i++) {
        cout << "##";
    }
    cout << "#";

    for (int i = 0; i < height; i++) {
        gotoxy(0, i + 1);
        cout << "#";
        gotoxy(width * 2 + 1, i + 1);
        cout << "#";
    }

    gotoxy(0, height + 1);
    cout << "#";
    for (int i = 0; i < width; i++) {
        cout << "##";
    }
    cout << "#";
}

void Draw() {
    system("cls");
    DrawBorder();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            gotoxy(j * 2 + 1, i + 1);

            if (i == y && j == x) {
                setColor(LIGHT_GREEN);
                cout << "OO";
            }
            else if (i == fruitY && j == fruitX) {
                setColor(LIGHT_RED);
                cout << "()";
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        setColor(GREEN);
                        cout << "oo";
                        print = true;
                        break;
                    }
                }
                if (!print) {
                    cout << "  ";
                }
            }
        }
    }

    setColor(BRIGHT_WHITE);
    gotoxy(width * 2 + 5, 2);
    cout << "SNAKE GAME";

    setColor(LIGHT_YELLOW);
    gotoxy(width * 2 + 5, 4);
    cout << "SCORE: " << score;

    setColor(LIGHT_CYAN);
    gotoxy(width * 2 + 5, 6);
    cout << "LENGTH: " << nTail + 1;

    setColor(LIGHT_MAGENTA);
    gotoxy(width * 2 + 5, 8);
    cout << "CONTROLS:";
    gotoxy(width * 2 + 5, 9);
    cout << "WASD - move";
    gotoxy(width * 2 + 5, 10);
    cout << "X - exit";

    setColor(LIGHT_RED);
    gotoxy(width * 2 + 5, 12);
    cout << "FRUIT: ()";

    setColor(WHITE);
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

    setColor(LIGHT_RED);
    for (int i = 0; i < 40; i++) cout << "#";
    cout << endl;

    setColor(LIGHT_YELLOW);
    cout << "#" << "           GAME OVER!           " << "#" << endl;

    setColor(LIGHT_CYAN);
    cout << "#" << "         FINAL SCORE: " << score << "        " << "#" << endl;

    setColor(LIGHT_MAGENTA);
    cout << "#" << "         SNAKE LENGTH: " << nTail + 1 << "         " << "#" << endl;

    setColor(LIGHT_RED);
    for (int i = 0; i < 40; i++) cout << "#";
    cout << endl;

    setColor(BRIGHT_WHITE);
    cout << "\nPress Enter to continue...";

    while (_getch() != 13);
}

void ShowMenu() {
    int choice = 0;
    int key;

    while (true) {
        system("cls");

        setColor(LIGHT_YELLOW);
        gotoxy(25, 2);
        cout << "##############################";
        gotoxy(25, 3);
        cout << "#         Snake Game         #";
        gotoxy(25, 4);
        cout << "##############################";

        setColor(LIGHT_CYAN);
        gotoxy(25, 6);
        cout << "SELECT DIFFICULTY:";

        setColor(choice == 0 ? LIGHT_GREEN : WHITE);
        gotoxy(27, 8);
        cout << (choice == 0 ? "> " : "  ") << "EASY (Slow)";

        setColor(choice == 1 ? LIGHT_GREEN : WHITE);
        gotoxy(27, 10);
        cout << (choice == 1 ? "> " : "  ") << "MEDIUM (Normal)";

        setColor(choice == 2 ? LIGHT_GREEN : WHITE);
        gotoxy(27, 12);
        cout << (choice == 2 ? "> " : "  ") << "HARD (Fast)";

        setColor(choice == 3 ? LIGHT_RED : WHITE);
        gotoxy(27, 14);
        cout << (choice == 3 ? "> " : "  ") << "EXIT";

        setColor(LIGHT_MAGENTA);
        gotoxy(22, 16);
        cout << "CONTROLS: W/A/S/D - movement";
        gotoxy(22, 17);
        cout << "           X - exit game";

        key = _getch();

        switch (key) {
        case 72: // Вверх
            choice = (choice > 0) ? choice - 1 : 3;
            break;
        case 80: // Вниз
            choice = (choice < 3) ? choice + 1 : 0;
            break;
        case 13: // Enter
            if (choice == 3) {
                setColor(WHITE);
                system("cls");
                exit(0);
            }

            switch (choice) {
            case 0: gameSpeed = 100; break;
            case 1: gameSpeed = 60; break;
            case 2: gameSpeed = 30; break;
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
            break;
        }
    }
}