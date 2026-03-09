#include "Game.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::system("title Snake Game");
    std::system("mode con cols=70 lines=25");
    hideCursor();

    std::srand(std::time(NULL));

    ShowMenu();

    return 0;
}