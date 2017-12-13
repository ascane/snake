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

    Vec2 operator+(const Vec2& that) const {
        return Vec2(x + that.x, y + that.y);
    }

    Vec2 operator-(const Vec2& that) const {
        return Vec2(x - that.x, y - that.y);
    }

    Vec2 operator*(int n) const {
        return Vec2(n * x, n * y);
    }

    bool operator==(const Vec2& that) const {
        return x == that.x && y == that.y;
    }
};

#endif // VEC2_H
