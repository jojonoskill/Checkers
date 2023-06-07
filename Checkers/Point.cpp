#include "Point.h"

Point::Point() {
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
    this->z = 0;
}

Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
