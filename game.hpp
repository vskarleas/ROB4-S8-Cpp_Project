// #############################################################################
// # File game.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "paddle.hpp"
#include "ball_base.hpp"
#include "menu.hpp"
#include "pause_menu.hpp"

enum class GameState {
    Menu,
    Playing,
    Paused
};

class Game {
public:
    Game();
    ~Game();
    bool initialise();
    void loop();
    void close();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void CreateBall(int type);
    void UpdateBackground();
    
    SDL_Window* mWindow;
    SDL_Renderer* renderer;
    bool mIsRunning;
    Uint32 mTicksCount;
    
    Paddle* mPaddle1;
    Paddle* mPaddle2;
    BallBase* mBall;
    
    int mScore1;
    int mScore2;
    TTF_Font* police;
    Menu* mMenu;
    GameState mGameState;

    PauseMenu* mPauseMenu;
    
    Mix_Music* mBackgroundMusic;
    Mix_Chunk* mPaddleHitSound;
    Mix_Chunk* mWallHitSound;
    Mix_Chunk* mScoreSound;
    
    SDL_Color mBackgroundColor1;
    SDL_Color mBackgroundColor2;

    SDL_Rect mPauseButtonRect;
    bool DrawSaveButton();     
};

#endif