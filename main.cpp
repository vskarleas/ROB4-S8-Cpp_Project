// #############################################################################
// # File main.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "game.hpp"

/* It creates a game object and runs the game's loop  */
int main(int argc, char *argv[])
{
    Game game;

    if (game.initialise())
    {
        game.loop();
    }

    game.close();
    return 0;
}