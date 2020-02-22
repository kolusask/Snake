#include "snake.hpp"

Snake::Snake(const unsigned len, const int w, const int h)
    : width(w), height(h) {
    this->length = len;
    direct = RIGHT;
    back_dir = RIGHT;
    for(unsigned i = length + 1; i > 0; i--) sections.push_back(Section(i, 0));
}

Snake::Section::Section(const int x, const int y) {
    setXY(x, y);
    this->direct = Directions::RIGHT;
}

void Snake::Section::setXY(const int x, const int y) {
    this->X = x;
    this->Y = y;
}

void Snake::Section::move(const Directions dir) {
    switch(dir) {
        case Directions::UP:
            Y--;
            break;
        case Directions::DOWN:
            Y++;
            break;
        case Directions::LEFT:
            X--;
            break;
        case Directions::RIGHT:
            X++;
    }
}

void Snake::move(const Directions dir) {
    back_dir = sections[length - 1].direct;
    for(unsigned i = length - 1; i > 0; i--) sections[i] = sections[i - 1];
    sections[0].move(dir);
    direct = dir;
    fit();
}

void Snake::grow() {
    sections.push_back(Section(sections[length - 1].X, sections[length - 1].Y));
    length++;
    switch(back_dir) {
        case UP:
            sections[length - 1].move(DOWN);
            break;
        case DOWN:
            sections[length - 1].move(UP);
            break;
        case LEFT:
            sections[length - 1].move(RIGHT);
            break;
        case RIGHT:
            sections[length - 1].move(LEFT);
    }
    sections[length - 1].direct = back_dir;
}

void Snake::fit() {
    for(unsigned i = 0; i < length; i++) {
        if(sections[i].X == -1)
            sections[i].X = width - 1;
        else if(sections[i].X == width)
            sections[i].X = 0;
        if(sections[i].Y == -1)
            sections[i].Y = height - 1;
        else if(sections[i].Y == height)
            sections[i].Y = 0;
    }
}

Snake::~Snake() { sections.clear(); }
