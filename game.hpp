#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "paddle.hpp"
#include "ball.hpp"

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

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;
    Uint32 mTicksCount;
    
    Paddle* mPaddle1;
    Paddle* mPaddle2;
    Ball* mBall;
    
    int mScore1;
    int mScore2;
    TTF_Font* mFont;
};

#endif