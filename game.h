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
        map(36, 15), snake(&map, Vec2(15, 10), 5, Vec2(1, 0)),
        game_over(false), paused(false), time_step(300), score(0) {}

    void spawn_fruit() {
        Vec2 v;
        do {
            v.x = rand() % map.get_width();
            v.y = rand() % map.get_height();
        } while (map.get(v) != EMPTY);
        map.set(v, FRUIT);
    }

    void display(bool game_over) {
        // Get terminal width and height.
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int t_width = w.ws_col;
        int t_height = w.ws_row;

        int x_offset = (t_width - map.get_width() - 2) / 2;
        int y_offset = (t_height - map.get_height() - 2) / 2;

        // Clear the terminal.
        set_cursor_pos(0, 0);
        cout << string(t_width * t_height, ' ');


        set_cursor_pos(x_offset, y_offset - 2);
        cout << "score: " << score;
        map.draw(x_offset, y_offset);

        if (game_over) {
            set_cursor_pos(t_width / 2 - 5, t_height / 2 - 1);
            cout << "Game over!";
        }
        set_cursor_pos(x_offset, y_offset + map.get_height() + 4);
        cout << "w - up, s - down, a - left, d - right,";
        set_cursor_pos(x_offset, y_offset + map.get_height() + 6);
        cout << "p - pause\r\n\r\n";
    }

    void run() {
        int time_elapsed = 0;
        spawn_fruit();
        display(/*game_over=*/false);
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
                time_elapsed = 0;
                if (result == DIE) {
                    game_over = true;
                } else if (result == EAT) {
                    ++score;
                    spawn_fruit();
                }
                display(game_over);
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
