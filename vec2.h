#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
    int x;
    int y;

    Vec2(){}

    Vec2(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Vec2 const operator+(const Vec2& that) {
        return Vec2(x + that.x, y + that.y);
    }
};

#endif // VEC2_H
