#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <vec2.h>
#include <map.h>

using namespace std;

enum move_result {OK, EAT, DIE};

class Snake {
  public:

    Snake(Map* map, Vec2 init_position, int init_length, Vec2 init_dir) {
        this->map = map;
        this->dir = init_dir;
        this->body.push_front(init_position);
        for (int i = 0; i < init_length; ++i) {
            Vec2 pos = init_position - init_dir * i;
            this->body.push_back(pos);
            map->set(pos, SNAKE);
        }
    }

    Vec2 get_dir() {
        return dir;
    }

    move_result move() {
        Vec2 next_pos = body.front() + dir;
        if (map->get(next_pos) == EMPTY) {
            map->set(next_pos, SNAKE);
            body.push_front(next_pos);
            map->set(body.back(), EMPTY);
            body.pop_back();
            return OK;
        } else if (map->get(next_pos) == FRUIT) {
            map->set(next_pos, SNAKE);
            body.push_front(next_pos);
            return EAT;
        } else {
            return DIE;
        }
    }

    move_result move(Vec2 new_dir) {
        dir = new_dir;
        return move();
    }

  private:
    deque<Vec2> body;
    Vec2 dir;
    Map* map;
};


#endif // SNAKE_H
