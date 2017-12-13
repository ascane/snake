#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vec2.h>

using namespace std;

enum cell_type {EMPTY = 0, OBSTACLE = 1, SNAKE = 2, FRUIT = 3};
const string cell_type_char = ".X#o";

class Map {
public:
    Map(int width, int height) {
        this->width = width;
        this->height = height;
        this->data = new cell_type[width * height];
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                this->data[i + j * width] = EMPTY;
            }
        }
    }

    void reset() {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                this->data[i + j * width] = EMPTY;
            }
        }
    }

    int get_width() {
        return width;
    }

    int get_height() {
        return height;
    }

    cell_type get(Vec2 pos) {
        if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height) {
            return OBSTACLE;
        } else {
            return data[pos.x + pos.y * width];
        }
    }

    bool set(Vec2 pos, cell_type ct) {
        if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height) {
            return false;
        } else {
            data[pos.x + pos.y * width] = ct;
            return true;
        }
    }

    void draw() {
        cout << string(100, '\n');
        cout << string(width + 2, cell_type_char[OBSTACLE]);
        cout << "\r\n";
        for (int j = 0; j < height; ++j) {
            cout << cell_type_char[OBSTACLE];

            for (int i = 0; i < width; ++i) {
                cout << cell_type_char[data[i + j * width]];
            }
            cout << cell_type_char[OBSTACLE];
            cout << "\r\n";
        }
        cout << string(width + 2, cell_type_char[OBSTACLE]);
        cout << "\r\n";
    }

private:
    int width;
    int height;
    cell_type* data;
};

#endif // MAP_H