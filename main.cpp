// #############################################################################
// # File main.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "game.hpp"

int main(int argc, char *argv[])
{
    Game game;
    bool success = game.Initialize();

    if (success)
    {
        game.RunLoop();
    }

    game.Shutdown();
    return 0;
}