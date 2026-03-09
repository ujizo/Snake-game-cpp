#pragma once

extern bool gameOver;
extern const int width;
extern const int height;
extern int x, y, fruitX, fruitY, score;
extern int tailX[100], tailY[100];
extern int nTail;
extern int gameSpeed;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
extern eDirecton dir;

void Setup();
void Draw();
void Input();
void Logic();
void ShowMenu();
void ShowGameOver();
void DrawBorder();
void GenerateFruit();