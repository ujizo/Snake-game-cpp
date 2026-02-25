#include "fruit.h"
#include <cstdlib>

Fruit::Fruit() : isEaten(true) {}

void Fruit::spawn(const Snake& snake) {
    do {
        position.x = rand() % (WIDTH - 2) + 1;
        position.y = rand() % (HEIGHT - 2) + 1;
    } while (snake.isPointInBody(position));
    isEaten = false;
}

Point Fruit::getPosition() const {
    return position;
}

bool Fruit::getIsEaten() const {
    return isEaten;
}

void Fruit::setEaten(bool eaten) {
    isEaten = eaten;
}