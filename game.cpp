// #############################################################################
// # File game.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "game.hpp"
#include "classic_ball.hpp"
#include "square_ball.hpp"
#include "triangle_ball.hpp"
#include "game_save.hpp"
#include "menu.hpp"
#include "macros.hpp"

#include <string>

Game::Game()
    : mWindow(nullptr), renderer(nullptr), mIsRunning(true), mTicksCount(0), mPaddle1(nullptr), mPaddle2(nullptr), mBall(nullptr), mScore1(0), mScore2(0), police(nullptr), mMenu(nullptr), mGameState(GameState::Menu), mPauseMenu(nullptr) // Initialize pause menu pointer
{
    mBackgroundColor1.r = 0;
    mBackgroundColor1.g = 0;
    mBackgroundColor1.b = 0;
    mBackgroundColor1.a = 255;

    mBackgroundColor2.r = 0;
    mBackgroundColor2.g = 0;
    mBackgroundColor2.b = 0;
    mBackgroundColor2.a = 255;

    mSaveButtonRect = {700, 550, 100, 30}; // x, y, width, height
}

Game::~Game()
{
    // Delete menu first since it might use renderer
    if (mMenu)
    {
        delete mMenu;
        mMenu = nullptr;
    }

    if (mPauseMenu)
    {
        delete mPauseMenu;
        mPauseMenu = nullptr;
    }

    // Delete game objects
    if (mPaddle1)
    {
        delete mPaddle1;
        mPaddle1 = nullptr;
    }
    if (mPaddle2)
    {
        delete mPaddle2;
        mPaddle2 = nullptr;
    }
    if (mBall)
    {
        delete mBall;
        mBall = nullptr;
    }

    // Clean up audio resources
    if (mBackgroundMusic)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(mBackgroundMusic);
        mBackgroundMusic = nullptr;
    }
    if (mPaddleHitSound)
    {
        Mix_FreeChunk(mPaddleHitSound);
        mPaddleHitSound = nullptr;
    }
    if (mWallHitSound)
    {
        Mix_FreeChunk(mWallHitSound);
        mWallHitSound = nullptr;
    }
    if (mScoreSound)
    {
        Mix_FreeChunk(mScoreSound);
        mScoreSound = nullptr;
    }

    // Clean up font
    if (police)
    {
        TTF_CloseFont(police);
        police = nullptr;
    }

    // Clean up SDL resources
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (mWindow)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    // Quit SDL subsystems
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

bool Game::DrawSaveButton()
{
    // Draw save button with white text
    SDL_Color white = {255, 255, 255, 255};
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    TTF_SetFontSize(police, 24);

    SDL_Surface *saveText = TTF_RenderText_Solid(police, "Save", white);
    if (!saveText)
        return false;

    SDL_Texture *saveTexture = SDL_CreateTextureFromSurface(renderer, saveText);
    if (!saveTexture)
    {
        SDL_FreeSurface(saveText);
        return false;
    }

    SDL_Rect textRect = {
        mSaveButtonRect.x + (mSaveButtonRect.w - saveText->w) / 2,
        mSaveButtonRect.y + (mSaveButtonRect.h - saveText->h) / 2,
        saveText->w,
        saveText->h};

    SDL_RenderCopy(renderer, saveTexture, nullptr, &textRect);

    SDL_FreeSurface(saveText);
    SDL_DestroyTexture(saveTexture);
    return true;
}

bool Game::initialise()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        return false;
    }

    if (TTF_Init() != 0)
    {
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        return false;
    }

    mWindow = SDL_CreateWindow(
        GAME_NAME,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!mWindow)
    {
        return false;
    }

    renderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        return false;
    }

    police = TTF_OpenFont("assets/Helvetica.ttc", 24);
    if (!police)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }

    mMenu = new Menu(renderer, police);
    mPaddle1 = new Paddle(30, true);
    mPaddle2 = new Paddle(770, false);
    CreateBall(0); // Start with classic ball

    // Load audio files (make sure these files exist in your project directory)
    mBackgroundMusic = Mix_LoadMUS("assets/background.wav");
    mPaddleHitSound = Mix_LoadWAV("assets/paddle_hit.wav");
    mWallHitSound = Mix_LoadWAV("assets/wall_hit.wav");
    mScoreSound = Mix_LoadWAV("assets/score.wav");

    if (!mBackgroundMusic)
    {
        SDL_Log("Failed to load background music: %s", Mix_GetError());
    }
    if (!mPaddleHitSound)
    {
        SDL_Log("Failed to load paddle hit sound: %s", Mix_GetError());
    }

    // Start playing background music on loop
    if (mBackgroundMusic)
    {
        Mix_PlayMusic(mBackgroundMusic, -1); // -1 means loop indefinitely
    }

    mPauseMenu = new PauseMenu(renderer, police);

    return true;
}

void Game::loop()
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
        case SDL_QUIT:  // Handle window close (X button)
            mIsRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (mGameState == GameState::Menu)
            {
                if (mMenu->action_handler(event))
                {
                    if (mMenu->get_started())
                    {
                        if (mMenu->get_continue_game())
                        {
                            // Load saved game state
                            SaveState savedState;
                            if (GameSave::load_game(savedState, ""))
                            {
                                mScore1 = savedState.score1;
                                mScore2 = savedState.score2;
                                mPaddle1->set_pos_y(savedState.paddle1_y);
                                mPaddle2->set_pos_y(savedState.paddle2_y);
                                CreateBall(savedState.ball_type);
                                mBall->set_position(savedState.ball_x, savedState.ball_y);
                                mBall->set_velocity(savedState.ball_vel_x, savedState.ball_vel_y);
                                UpdateBackground();
                                // Delete save file after loading
                                GameSave::delete_save();
                                mGameState = GameState::Playing;
                            }
                        }
                        else
                        {
                            // New game - delete any existing save
                            GameSave::delete_save();
                            CreateBall(mMenu->get_selected_ball());
                            mScore1 = mScore2 = 0;
                            UpdateBackground();
                            mGameState = GameState::Playing;
                        }
                    }
                    else if (mMenu->get_exit_game())
                    {
                        mIsRunning = false;
                    }
                }
            }
            else if (mGameState == GameState::Playing)
            {
                SDL_Point clickPoint = {event.button.x, event.button.y};
                if (SDL_PointInRect(&clickPoint, &mSaveButtonRect))
                {
                    SaveState saveState;
                    saveState.score1 = mScore1;
                    saveState.score2 = mScore2;
                    saveState.paddle1_y = mPaddle1->get_pos_y();
                    saveState.paddle2_y = mPaddle2->get_pos_y();
                    saveState.ball_x = mBall->get_pos_x();
                    saveState.ball_y = mBall->get_pos_y();
                    saveState.ball_vel_x = mBall->get_vel_x();
                    saveState.ball_vel_y = mBall->get_vel_y();
                    saveState.ball_type = mMenu->get_selected_ball();
            
                    if (GameSave::save_game(saveState, ""))
                    {
                        SDL_Log("Game saved successfully");
                        mGameState = GameState::Menu;
                        mMenu->set_saved_file_exists(); // Add this method to Menu class
                    }
                }
            }
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        if (mGameState == GameState::Playing)
        {
            mGameState = GameState::Paused;
        }
        else if (mGameState == GameState::Paused)
        {
            mGameState = GameState::Playing;
        }
    }
}

void Game::UpdateGame()
{
    if (mGameState != GameState::Playing)
    {
        return;
    }

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    float travel_time = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (travel_time > 0.05f)
    {
        travel_time = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    mPaddle1->update(travel_time);
    mPaddle2->update(travel_time);
    mBall->update(travel_time, mPaddle1, mPaddle2, mScore1, mScore2);

    // Check for victory condition
    if (mScore1 >= 10 || mScore2 >= 10)
    {
        mGameState = GameState::Menu;
        return;
    }

    // Update background colors based on scores
    UpdateBackground();
}

void Game::UpdateBackground()
{
    // Player 1 background color
    if (mScore1 >= 7)
    {
        mBackgroundColor1.r = 0;
        mBackgroundColor1.g = 255;
        mBackgroundColor1.b = 0;
        mBackgroundColor1.a = 255;
    }
    else if (mScore1 >= 5)
    {
        mBackgroundColor1.r = 255;
        mBackgroundColor1.g = 0;
        mBackgroundColor1.b = 0;
        mBackgroundColor1.a = 255;
    }
    else if (mScore1 >= 3)
    {
        mBackgroundColor1.r = 0;
        mBackgroundColor1.g = 0;
        mBackgroundColor1.b = 255;
        mBackgroundColor1.a = 255;
    }
    else
    {
        mBackgroundColor1.r = 0;
        mBackgroundColor1.g = 0;
        mBackgroundColor1.b = 0;
        mBackgroundColor1.a = 255;
    }

    // Player 2 background color
    if (mScore2 >= 7)
    {
        mBackgroundColor2.r = 0;
        mBackgroundColor2.g = 255;
        mBackgroundColor2.b = 0;
        mBackgroundColor2.a = 255;
    }
    else if (mScore2 >= 5)
    {
        mBackgroundColor2.r = 255;
        mBackgroundColor2.g = 0;
        mBackgroundColor2.b = 0;
        mBackgroundColor2.a = 255;
    }
    else if (mScore2 >= 3)
    {
        mBackgroundColor2.r = 0;
        mBackgroundColor2.g = 0;
        mBackgroundColor2.b = 255;
        mBackgroundColor2.a = 255;
    }
    else
    {
        mBackgroundColor2.r = 0;
        mBackgroundColor2.g = 0;
        mBackgroundColor2.b = 0;
        mBackgroundColor2.a = 255;
    }
}

void Game::GenerateOutput()
{
    if (mGameState == GameState::Paused)
    {
        mPauseMenu->render_object();
        return;
    }

    if (mGameState == GameState::Menu)
    {
        mMenu->render_object();
        return;
    }

    // Draw split background
    SDL_Rect leftHalf = {0, 0, 400, 600};
    SDL_Rect rightHalf = {400, 0, 400, 600};

    SDL_SetRenderDrawColor(renderer,
                           mBackgroundColor1.r, mBackgroundColor1.g,
                           mBackgroundColor1.b, mBackgroundColor1.a);
    SDL_RenderFillRect(renderer, &leftHalf);

    SDL_SetRenderDrawColor(renderer,
                           mBackgroundColor2.r, mBackgroundColor2.g,
                           mBackgroundColor2.b, mBackgroundColor2.a);
    SDL_RenderFillRect(renderer, &rightHalf);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw middle line
    for (int y = 0; y < 600; y += 10)
    {
        SDL_Rect dash = {398, y, 4, 5};
        SDL_RenderFillRect(renderer, &dash);
    }

    mPaddle1->render_object(renderer);
    mPaddle2->render_object(renderer);
    mBall->render_object(renderer);

    // Print scores
    SDL_Color white = {255, 255, 255, 255};
    std::string score1Text = std::to_string(mScore1);
    std::string score2Text = std::to_string(mScore2);

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    TTF_SetFontSize(police, 48);

    SDL_Surface *surf1 = TTF_RenderText_Solid(police, score1Text.c_str(), white);
    SDL_Surface *surf2 = TTF_RenderText_Solid(police, score2Text.c_str(), white);

    SDL_Texture *tex1 = SDL_CreateTextureFromSurface(renderer, surf1);
    SDL_Texture *tex2 = SDL_CreateTextureFromSurface(renderer, surf2);

    SDL_Rect score1Rect = {200, 20, surf1->w, surf1->h};
    SDL_Rect score2Rect = {600, 20, surf2->w, surf2->h};

    SDL_RenderCopy(renderer, tex1, nullptr, &score1Rect);
    SDL_RenderCopy(renderer, tex2, nullptr, &score2Rect);

    SDL_FreeSurface(surf1);
    SDL_FreeSurface(surf2);
    SDL_DestroyTexture(tex1);
    SDL_DestroyTexture(tex2);

    // Draw save button at the bottom
    DrawSaveButton();

    SDL_RenderPresent(renderer);
}

void Game::CreateBall(int type)
{
    delete mBall;
    switch (type)
    {
    case 0:
        mBall = new ClassicBall();
        break;
    case 1:
        mBall = new SquareBall();
        break;
    case 2:
        mBall = new TriangleBall();
        break;
    default:
        mBall = new ClassicBall();
        break;
    }
}

void Game::close()
{
    if (police)
    {
        TTF_CloseFont(police);
        police = nullptr;
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (mWindow)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}