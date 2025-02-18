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
#include "page_3b.hpp"
#include "macros.hpp"

#include <string>

Game::Game()
    : mWindow(nullptr),
      renderer(nullptr),

      mIsRunning(true),
      mTicksCount(0),

      mPaddle1(nullptr),
      mPaddle2(nullptr),
      mBall(nullptr),

      mScore1(0),
      mScore2(0),

      police(nullptr),

      mNoticeMenu(nullptr),
      mMenu(nullptr),
      mPauseMenu(nullptr),
      mMiddleMenu(nullptr),
      mModeMenu(nullptr),

      mGameState(game_state::Notice_Menu) // by default we get into the Notice Menu

{
    mBackgroundColor1.r = 0;
    mBackgroundColor1.g = 0;
    mBackgroundColor1.b = 0;
    mBackgroundColor1.a = 255;

    mBackgroundColor2.r = 0;
    mBackgroundColor2.g = 0;
    mBackgroundColor2.b = 0;
    mBackgroundColor2.a = 255;

    mPauseButtonRect = {700, 550, 100, 30}; // x, y, width, height
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

    if (mNoticeMenu)
    {
        delete mNoticeMenu;
        mNoticeMenu = nullptr;
    }

    if (mMiddleMenu)
    {
        delete mMiddleMenu;
        mMiddleMenu = nullptr;
    }

    if (mModeMenu)
    {
        delete mModeMenu;
        mModeMenu = nullptr;
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
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    TTF_SetFontSize(police, 24);

    SDL_Surface *saveText = TTF_RenderText_Solid(police, "Pause", white);
    if (!saveText)
        return false;

    SDL_Texture *saveTexture = SDL_CreateTextureFromSurface(renderer, saveText);
    if (!saveTexture)
    {
        SDL_FreeSurface(saveText);
        return false;
    }

    SDL_Rect textRect = {
        mPauseButtonRect.x + (mPauseButtonRect.w - saveText->w) / 2,
        mPauseButtonRect.y + (mPauseButtonRect.h - saveText->h) / 2,
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

    // Rendering the different views of the game
    mMenu = new Menu(renderer, police);
    mNoticeMenu = new NoticeMenu(renderer, police);
    mMiddleMenu = new MiddleMenu(renderer, police);
    mModeMenu = new ModeMenu(renderer, police);
    mPauseMenu = new PauseMenu(renderer, police);

    // Creating the different objects of the game
    mPaddle1 = new Paddle(30, true);
    mPaddle2 = new Paddle(770, false);
    CreateBall(0); // Start with classic ball then it is updated over the choices at MiddleMenu

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

    return true;
}

void Game::loop()
{
    while (mIsRunning) // set to false when we either tap on the X to close the SDL window or when we tap on the Exit game button
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
        case SDL_QUIT: // Handle window close (X button)
            mIsRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (mGameState == game_state::Notice_Menu && mNoticeMenu->get_notice_id() == -1)
            {
                if (mNoticeMenu->action_handler(event))
                {
                    if (mNoticeMenu->get_next_view()) // The let's go button has been clicked
                    {
                        mGameState = game_state::Choose_Mode;
                    }
                    else // Waiting for user to enter the game
                    {
                        return;
                    }
                }
                else
                {
                    SDL_Log("Invalid action on Notice menu with id -1");
                }
            }
            else if (mGameState == game_state::Notice_Menu && mNoticeMenu->get_notice_id() != -1)
            {
                if (mNoticeMenu->action_handler(event)) // we check which of two button was clicked
                {
                    if (mNoticeMenu->get_next_view()) // if we want to move on with this choice
                    {
                        switch (mNoticeMenu->get_notice_id())
                        {
                        case AI_MODE:
                            mMiddleMenu->set_mode_type(AI_MODE);
                            mGameState = game_state::Middle_menu;
                            break;
                        case TWO_PLAYERS_MODE:
                            mGameState = game_state::Menu; // entering the internal menu of the game
                            break;
                        case STORYTIME_MODE:
                            mGameState = game_state::Storytime_playing;
                            break;
                        case FUN_MODE:
                            mGameState = game_state::Fun_playing;
                            break;
                        case GAME_SAVED:
                            mGameState = game_state::Choose_Mode;
                            break;
                        default:
                        {
                            SDL_Log("Invalid notice id");
                            break;
                        }
                        }
                    }
                    else if (mNoticeMenu->get_go_back()) // we want to go back to the Mode menu
                    {
                        mGameState = game_state::Choose_Mode;
                    }
                    else
                    {
                        SDL_Log("Invalid action on Notice menu");
                    }
                }
                else
                {
                    SDL_Log("Invalid action on Notice menu");
                }
            }
            else if (mGameState == game_state::Choose_Mode)
            {
                if (mModeMenu->action_handler(event))
                {
                    if (mModeMenu->get_exit_game())
                    {
                        mIsRunning = false;
                    }
                    else
                    {
                        switch (mModeMenu->get_mode_id())
                        {
                        case AI_MODE:
                            mNoticeMenu->set_notice_id(AI_MODE);
                            mGameState = game_state::Notice_Menu;
                            break;
                        case TWO_PLAYERS_MODE:
                            mNoticeMenu->set_notice_id(TWO_PLAYERS_MODE);
                            mGameState = game_state::Notice_Menu;
                            break;
                        case STORYTIME_MODE:
                            mNoticeMenu->set_notice_id(STORYTIME_MODE);
                            mGameState = game_state::Notice_Menu;
                            break;
                        case FUN_MODE:
                            mNoticeMenu->set_notice_id(FUN_MODE);
                            mGameState = game_state::Notice_Menu;
                            break;
                        default:
                            SDL_Log("Invalid mode id");
                            break;
                        }
                    }
                }
                else
                {
                    SDL_Log("Invalid action on Mode menu");
                }
            }
            else if (mGameState == game_state::Menu)
            {
                if (mMenu->action_handler(event))
                {
                    if (mMenu->get_started())
                    {
                        mMiddleMenu->set_mode_type(TWO_PLAYERS_MODE);
                        mGameState = game_state::Middle_menu; // We need to select the ball type before starting a new game
                    }
                    else if (mMenu->get_exit_mode())
                    {
                        mGameState = game_state::Choose_Mode; // Go back to the Mode menu
                        // mIsRunning = false; // No need to delete the saved game file before exiting if it exists. The idea is that we find itback when we reneter the game
                    }
                    else if (mMenu->get_continue_game())
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

                            GameSave::delete_save(); // Delete the saved game file once we have loaded the game state

                            mGameState = game_state::Playing;
                        }
                    }
                }
                else
                {
                    SDL_Log("Invalid action on Main menu");
                }
            }
            else if (mGameState == game_state::Playing)
            {
                SDL_Point clickPoint = {event.button.x, event.button.y};
                if (SDL_PointInRect(&clickPoint, &mPauseButtonRect)) // We go to pause menu if the pause button is clicked
                {
                    mPauseMenu->set_mode_type(TWO_PLAYERS_MODE); // essential otherwise we do not know where are right now
                    mGameState = game_state::Paused;
                }
            }
            else if (mGameState == game_state::AI_playing)
            {
                SDL_Point clickPoint = {event.button.x, event.button.y};
                if (SDL_PointInRect(&clickPoint, &mPauseButtonRect)) // We go to pause menu if the pause button is clicked
                {
                    mPauseMenu->set_mode_type(AI_MODE);
                    mGameState = game_state::Paused;
                }
            }
            else if (mGameState == game_state::Paused)
            {
                if (mPauseMenu->action_handler(event))
                {
                    if (mPauseMenu->ShouldResume())
                    {
                        // mPauseMenu->set_mode_type(mNoticeMenu->get_notice_id()); // We go back to the mode we came from (either two players or AI) to make sure the correct redering
                        if (mPauseMenu->get_mode_type() == TWO_PLAYERS_MODE)
                        {
                            mGameState = game_state::Playing;
                        }
                        else if (mPauseMenu->get_mode_type() == AI_MODE)
                        {
                            mGameState = game_state::AI_playing;
                        }
                        else
                        {
                            printf("ERROR: Unhandled pause menu option\n");
                        }
                    }
                    else if (mPauseMenu->ShouldSave())
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
                        saveState.ball_type = mMiddleMenu->get_selected_option();

                        if (GameSave::save_game(saveState, ""))
                        {
                            SDL_Log("Game saved successfully");
                            mMenu->set_saved_file_exists();
                            mNoticeMenu->set_notice_id(GAME_SAVED);
                            mGameState = game_state::Notice_Menu; // We go back to the main menu
                        }
                        else
                        {
                            SDL_Log("Failed to save game");
                            mIsRunning = false;
                        }
                    }
                    else if (mPauseMenu->get_exit_mode())
                    {
                        // We update the existens of the save file
                        mMenu->set_saved_file_exists();
                        mGameState = game_state::Choose_Mode; // We go back to the main menu without saving the progress
                    }
                    else
                    {
                        printf("ERROR: Unhandled pause menu option\n");
                    }
                }
            }
            else if (mGameState == game_state::Middle_menu)
            {
                if (mMiddleMenu->action_handler(event))
                {
                    if (mMiddleMenu->get_mode_type() == TWO_PLAYERS_MODE)
                    {
                        GameSave::delete_save(); // delete only in the case that we start a new game

                        CreateBall(mMiddleMenu->get_selected_option());

                        // Reset game state
                        mScore1 = 0;
                        mScore2 = 0;

                        // Reset paddle positions
                        mPaddle1->set_pos_y(WINDOW_HEIGHT / 2.0f);
                        mPaddle2->set_pos_y(WINDOW_HEIGHT / 2.0f);

                        // Reset ball position and give it initial velocity
                        mBall->set_position(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
                        mBall->set_velocity(200.0f, 235.0f); // Initial ball speed

                        // Reset background colors
                        UpdateBackground();

                        mGameState = game_state::Playing;
                        SDL_Log("New game started with selected ball type (%d)", mMiddleMenu->get_selected_option());
                    }
                    else if (mMiddleMenu->get_mode_type() == AI_MODE)
                    {
                        switch(mMiddleMenu->get_selected_option()) // TO BE COMPLETED WITH THE DEEP LEARNING MODEL
                        {
                            default:
                                SDL_Log("Invalid ball type selected");
                                break;
                        }
                    }
                    else
                    {
                        SDL_Log("Invalid mode type selected");
                    }
                }
                else
                {
                    SDL_Log("We couldn't try to select a ball type on the middle menu");
                }
            }
            break;

        default:
            break;
        }
    }
}

void Game::UpdateGame()
{
    if (mGameState != game_state::Playing) // There is nothing to update if the game is not in playing state
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
        mGameState = game_state::Menu;
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
    if (mGameState == game_state::Notice_Menu)
    {
        mNoticeMenu->render_object();
        return;
    }

    if (mGameState == game_state::Choose_Mode)
    {
        mModeMenu->render_object();
        return;
    }

    if (mGameState == game_state::Paused)
    {
        mPauseMenu->render_object();
        return;
    }

    if (mGameState == game_state::Menu)
    {
        mMenu->render_object();
        return;
    }

    if (mGameState == game_state::Middle_menu)
    {
        mMiddleMenu->render_object();
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

    // Pause menu only on the default Pong game or AI mode
    if (mNoticeMenu->get_notice_id() == AI_MODE || mNoticeMenu->get_notice_id() == TWO_PLAYERS_MODE) // We are rendering the Pause button only in the default Pong game
    {
        DrawSaveButton();
    }

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
