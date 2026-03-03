#include "Game.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    system("title Snake Game");
    system("mode con cols=70 lines=25");
    hideCursor();

    srand(time(NULL));

    ShowMenu();

    return 0;
}