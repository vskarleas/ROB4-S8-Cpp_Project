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


#include "notice_menu.hpp"

enum class GameState {
    Notice_Menu,
    Menu,
    Select_Ball_Menu,
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
    
    // The scores of the two players
    int mScore1;
    int mScore2;

    // The font used on the whole game
    TTF_Font* police;
    
    // Adding the different page sof the app
    NoticeMenu* mNoticeMenu;
    Menu* mMenu;
    PauseMenu* mPauseMenu;

    // This allows us to control on which state we are and make the appropriate UI and action decisons
    GameState mGameState;

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