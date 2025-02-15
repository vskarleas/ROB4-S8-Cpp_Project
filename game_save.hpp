#ifndef GAME_SAVE_HPP
#define GAME_SAVE_HPP

#include <string>

struct SaveState
{
    int score1;
    int score2;
    float paddle1Y;
    float paddle2Y;
    float ballX;
    float ballY;
    float ballVelX;
    float ballVelY;
    int ballType;
};

class GameSave
{
public:
    static void DeleteSave();
    static bool SaveGame(const SaveState &state, const std::string &filename);
    static bool LoadGame(SaveState &state, const std::string &filename);
    static bool SaveExists();
};

#endif