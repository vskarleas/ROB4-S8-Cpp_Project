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

#include "page_3b.hpp"
#include "page_3b_0t.hpp"
#include "page_3b_1t.hpp"
#include "page_4b_1t.hpp"
#include "page_2b_1t.hpp"

#include "ai.hpp"

enum class game_state {
    Notice_Menu,
    Menu, // th is the after menu after the Two players notice
    Middle_menu,
    Choose_Mode, // this is used as our main menu where players can choose what they want to do
    AI_playing,
    Fun_playing,
    Storytime_playing,
    Playing, // playing classic with two players (first implementation)
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
    
    // SDL objects for the game window and renderer
    SDL_Window* mWindow;
    SDL_Renderer* renderer;

    // Game loop variable allowing to control either if we stay on the modes loop or not
    bool mIsRunning;

    // This is used to track the time since the last frame was drawn
    /* We need that to calculate velocities and position */
    Uint32 mTicksCount;
    
    // Every game needs two paddles and one ball as expected
    Paddle* mPaddle1;
    Paddle* mPaddle2;
    BallBase* mBall;

    AI* mAI; // the AI player
    
    // The scores of the two players
    int mScore1;
    int mScore2;

    // The font used on the whole game
    TTF_Font* police;
    
    // Adding the different page structures on the app
    page_2b_1t* mNoticeMenu;
    page_3b_0t* mMenu;
    page_3b* mPauseMenu;
    page_3b_1t* mMiddleMenu;
    page_4b_1t* mModeMenu;


    // This allows us to control on which state we are and make the appropriate UI and action decisons
    game_state mGameState;

    // Audio variables
    Mix_Music* mBackgroundMusic;
    Mix_Chunk* mPaddleHitSound;
    Mix_Chunk* mWallHitSound;
    Mix_Chunk* mScoreSound;
    
    // Background color for the two sides
    SDL_Color mBackgroundColor1;
    SDL_Color mBackgroundColor2;

    // The pause button object declared here
    SDL_Rect mPauseButtonRect;
    bool DrawSaveButton();     
};

#endif