#ifndef GAME_H
#define GAME_H

#include <map.h>
#include <snake.h>
#include <input.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string>

enum button {UP = 119, DOWN = 115, LEFT = 97, RIGHT = 100, PAUSE = 112};

class Game {
public:
    Game() :
        map(30, 15), snake(&map, Vec2(15, 10), 5, Vec2(1, 0)),
        game_over(false), paused(false), time_step(300), score(0) {}

    void spawn_fruit() {
        Vec2 v;
        do {
            v.x = rand() % map.get_width();
            v.y = rand() % map.get_height();
        } while (map.get(v) != EMPTY);
        map.set(v, FRUIT);
    }

    void display() {
        // Get terminal width and height.
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int t_width = w.ws_col;
        int t_height = w.ws_row;

        int x_offset = (t_width - map.get_width()) / 2;
        int y_offset = (t_height - map.get_height()) / 2;


        for (int j = 0; j < 30; ++j) {
            cout << "\r\n";
        }
        cout << string(x_offset, ' ');
        cout << "score: " << score << "\r\n\r\n";
        map.draw(x_offset);
        for (int j = 0; j < y_offset; ++j) {
            cout << "\r\n";
        }
    }

    void run() {
        int time_elapsed = 0;
        spawn_fruit();
        display();
        while (!game_over) {
            bool moved = false;
            move_result result;

            if (kbhit()) {
                int c = getch();
                if (c == PAUSE) {
                    paused = !paused;
                }
                if (!paused) {
                    switch (c) {
                        case UP:
                        if (snake.get_dir() == Vec2(0, 1)) {
                            break;
                        }
                        result = snake.move(Vec2(0, -1));
                        moved = true;
                        break;

                        case DOWN:
                        if (snake.get_dir() == Vec2(0, -1)) {
                            break;
                        }
                        result = snake.move(Vec2(0, 1));
                        moved = true;
                        break;

                        case LEFT:
                        if (snake.get_dir() == Vec2(1, 0)) {
                            break;
                        }
                        result = snake.move(Vec2(-1, 0));
                        moved = true;
                        break;

                        case RIGHT:
                        if (snake.get_dir() == Vec2(-1, 0)) {
                            break;
                        }
                        result = snake.move(Vec2(1, 0));
                        moved = true;
                        break;

                        default:
                        break;
                    }
                }

            }
            if (time_elapsed >= time_step) {
                result = snake.move();
                moved = true;
            }

            if (moved) {
                display();
                time_elapsed = 0;
                if (result == DIE) {
                    game_over = true;
                } else if (result == EAT) {
                    ++score;
                    spawn_fruit();
                }
            }

            this_thread::sleep_for(std::chrono::milliseconds(10));
            if (!paused) {
                time_elapsed += 10;
            }
        }
    }

private:
    Map map;
    Snake snake;
    bool game_over;
    bool paused;
    int time_step;
    int score;
};

#endif // GAME_H
