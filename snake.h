#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "point.h"
#include "constants.h"

class Snake {
private:
    std::vector<Point> body;
    Direction dir;
public:
    Snake();
    Direction getDirection() const;
    void setDirection(Direction newDir);
    Point getHead() const;
    bool isPointInBody(const Point& p, bool includeHead = true) const;
    void move(bool grew = false);
    const std::vector<Point>& getBody() const;
};

#endif