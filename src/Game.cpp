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
                cout << "OO";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "()";
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
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

    gotoxy(width * 2 + 5, 2);
    cout << "SNAKE GAME";

    gotoxy(width * 2 + 5, 4);
    cout << "SCORE: " << score;

    gotoxy(width * 2 + 5, 6);
    cout << "LENGTH: " << nTail + 1;

    gotoxy(width * 2 + 5, 8);
    cout << "CONTROLS:";
    gotoxy(width * 2 + 5, 9);
    cout << "WASD - move";
    gotoxy(width * 2 + 5, 10);
    cout << "X - exit";

    gotoxy(width * 2 + 5, 12);
    cout << "FRUIT: ()";
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

    for (int i = 0; i < 40; i++) cout << "#";
    cout << endl;

    cout << "#" << "           GAME OVER!           " << "#" << endl;

    cout << "#" << "         FINAL SCORE: " << score << "        " << "#" << endl;

    cout << "#" << "         SNAKE LENGTH: " << nTail + 1 << "         " << "#" << endl;

    for (int i = 0; i < 40; i++) cout << "#";
    cout << endl;

    cout << "\nPress Enter to continue...";
    while (_getch() != 13);
}

void ShowMenu() {
    int choice = 0;

    while (true) {
        system("cls");

        cout << "##############################" << endl;
        cout << "#         Snake Game         #" << endl;
        cout << "##############################" << endl;
        cout << endl;
        cout << "SELECT DIFFICULTY:" << endl;
        cout << endl;
        cout << "1. EASY (Slow)" << endl;
        cout << "2. MEDIUM (Normal)" << endl;
        cout << "3. HARD (Fast)" << endl;
        cout << "4. EXIT" << endl;
        cout << endl;
        cout << "CONTROLS: W/A/S/D - movement" << endl;
        cout << "           X - exit game" << endl;
        cout << endl;
        cout << "Your choice (1-4): ";

        cin >> choice;

        if (choice == 4) {
            system("cls");
            exit(0);
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