#include "game.hpp"
#include <SDL_ttf.h>
#include <string>

Game::Game()
    : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mTicksCount(0), mScore1(0), mScore2(0), mFont(nullptr)
{
}

Game::~Game()
{
    delete mPaddle1;
    delete mPaddle2;
    delete mBall;
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return false;
    }

    if (TTF_Init() != 0)
    {
        return false;
    }

    mWindow = SDL_CreateWindow(
        "Multiplayer Pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0);

    if (!mWindow)
    {
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!mRenderer)
    {
        return false;
    }

    mFont = TTF_OpenFont("/System/Library/Fonts/Helvetica.ttc", 24);
    if (!mFont)
    {
        return false;
    }

    mPaddle1 = new Paddle(30, true);
    mPaddle2 = new Paddle(770, false);
    mBall = new Ball();

    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    mPaddle1->Update(deltaTime);
    mPaddle2->Update(deltaTime);
    mBall->Update(deltaTime, mPaddle1, mPaddle2, mScore1, mScore2);
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    // Draw middle line
    for (int y = 0; y < 600; y += 10)
    {
        SDL_Rect dash = {398, y, 4, 5};
        SDL_RenderFillRect(mRenderer, &dash);
    }

    mPaddle1->Draw(mRenderer);
    mPaddle2->Draw(mRenderer);
    mBall->Draw(mRenderer);

    // Draw scores
    SDL_Color white = {255, 255, 255, 255};
    std::string score1Text = std::to_string(mScore1);
    std::string score2Text = std::to_string(mScore2);

    SDL_Surface *surf1 = TTF_RenderText_Solid(mFont, score1Text.c_str(), white);
    SDL_Surface *surf2 = TTF_RenderText_Solid(mFont, score2Text.c_str(), white);

    SDL_Texture *tex1 = SDL_CreateTextureFromSurface(mRenderer, surf1);
    SDL_Texture *tex2 = SDL_CreateTextureFromSurface(mRenderer, surf2);

    SDL_Rect score1Rect = {200, 20, surf1->w, surf1->h};
    SDL_Rect score2Rect = {600, 20, surf2->w, surf2->h};

    SDL_RenderCopy(mRenderer, tex1, nullptr, &score1Rect);
    SDL_RenderCopy(mRenderer, tex2, nullptr, &score2Rect);

    SDL_FreeSurface(surf1);
    SDL_FreeSurface(surf2);
    SDL_DestroyTexture(tex1);
    SDL_DestroyTexture(tex2);

    SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
    TTF_CloseFont(mFont);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    TTF_Quit();
    SDL_Quit();
}