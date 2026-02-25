#ifndef FRUIT_H
#define FRUIT_H

#include "point.h"
#include "snake.h"

class Fruit {
private:
    Point position;
    bool isEaten;
public:
    Fruit();
    void spawn(const Snake& snake);
    Point getPosition() const;
    bool getIsEaten() const;
    void setEaten(bool eaten);
};

#endif