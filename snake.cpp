#include "snake.h"

Snake::Snake() {
    // Начальное положение: голова в центре, тело слева
    body.push_back(Point(WIDTH / 2, HEIGHT / 2));
    body.push_back(Point(WIDTH / 2 - 1, HEIGHT / 2));
    body.push_back(Point(WIDTH / 2 - 2, HEIGHT / 2));
    dir = RIGHT;
}

Direction Snake::getDirection() const {
    return dir;
}

void Snake::setDirection(Direction newDir) {
    // Запрет разворота на 180 градусов
    if ((dir == UP && newDir != DOWN) ||
        (dir == DOWN && newDir != UP) ||
        (dir == LEFT && newDir != RIGHT) ||
        (dir == RIGHT && newDir != LEFT)) {
        dir = newDir;
    }
}

Point Snake::getHead() const {
    return body.back();
}

bool Snake::isPointInBody(const Point& p, bool includeHead) const {
    size_t end = includeHead ? body.size() : body.size() - 1;
    for (size_t i = 0; i < end; ++i) {
        if (body[i] == p) return true;
    }
    return false;
}

void Snake::move(bool grew) {
    Point newHead = getHead();
    switch (dir) {
    case LEFT:  newHead.x--; break;
    case RIGHT: newHead.x++; break;
    case UP:    newHead.y--; break;
    case DOWN:  newHead.y++; break;
    default: break;
    }
    body.push_back(newHead);
    if (!grew) {
        body.erase(body.begin());
    }
}

const std::vector<Point>& Snake::getBody() const {
    return body;
}