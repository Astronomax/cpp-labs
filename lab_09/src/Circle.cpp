#include "Circle.hpp"
#include <cmath>
#include <cstdio>
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char* label) : Figure(id, x, y), radius(radius) {
    this->label = new char[strlen(label) + 1];
    strcpy((char*)this->label, label);
}

Circle::~Circle() {
    delete[] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

bool Circle::is_inside(int x, int y) const {
    return pow(this->x - x, 2) + pow(this->y - y, 2) <= pow(radius, 2);
}

void Circle::zoom(int factor) {
    radius *= factor;
}
