#include <iostream>
#include <input.h>
#include <game.h>

using namespace std;


int main(int argc, char **argv)
{
    set_conio_terminal_mode();

    Game game;
    game.run();

    return 0;
}
