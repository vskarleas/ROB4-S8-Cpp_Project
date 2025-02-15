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
    Paused,
    GameOver
};

class Game {
public:
    Game();
    ~Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void CreateBall(int type);
    void UpdateBackground();
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;
    Uint32 mTicksCount;
    
    Paddle* mPaddle1;
    Paddle* mPaddle2;
    BallBase* mBall;
    
    int mScore1;
    int mScore2;
    TTF_Font* mFont;
    Menu* mMenu;
    GameState mGameState;

    PauseMenu* mPauseMenu;
    
    Mix_Music* mBackgroundMusic;
    Mix_Chunk* mPaddleHitSound;
    Mix_Chunk* mWallHitSound;
    Mix_Chunk* mScoreSound;
    
    SDL_Color mBackgroundColor1;
    SDL_Color mBackgroundColor2;

    SDL_Rect mSaveButtonRect;
    bool DrawSaveButton();     
};

#endif