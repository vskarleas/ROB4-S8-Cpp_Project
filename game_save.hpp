// #############################################################################
// # File game_save.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef GAME_SAVE_HPP
#define GAME_SAVE_HPP

#include <string>

struct SaveState
{
    int score1;
    int score2;
    float paddle1_y; // Only need the y because on game initialisation the x is fixed
    float paddle2_y;
    float ball_x;
    float ball_y;
    float ball_vel_x;
    float ball_vel_y;
    int ball_type; // 0 for classic, 1 for square, 2 for triangle

    char player1_name[20];
    char player2_name[20];
};

struct HighScore
{
    int score;
    char name[20];
};

class Saving
{
public:
    // Deleting the file including the game's state (save)
    static void delete_save();

    // Deleting the file including the highscore data 
    static void delete_highscore();

    // Generating the game's state (save) to a file
    static bool save_game(const SaveState &state);

    // Loading the game's state from the file
    static bool load_game(SaveState &state);

    // Check if a save file exists or not
    static bool save_exists();

    // Saving the highscore to a file
    static bool save_highscore(const HighScore &score);

    // Loading the highscore from the file
    static bool load_highscore(HighScore &score);

    // Check if a highscore file exists or not
    static bool highscore_exists();
};

#endif