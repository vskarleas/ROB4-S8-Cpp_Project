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
#include "gui.hpp"
#include "sound_effects.hpp"

#include <string>

Mix_Chunk *Game::mPaddleHitSound = nullptr;
Mix_Chunk *Game::mWallHitSound = nullptr;
Mix_Chunk *Game::mScoreSound = nullptr;
Mix_Music *Game::mPauseMusic = nullptr;
Mix_Music *Game::mOnHoldMusic = nullptr;

Game::Game()
    : mWindow(nullptr),
      renderer(nullptr),

      mIsRunning(true),
      mTicksCount(0),

      mPaddle1(nullptr),
      mPaddle2(nullptr),
      mBall(nullptr),

      mAI(nullptr),

      //   mScore1(0),
      //   mScore2(0),

      police(nullptr),

      mNoticeMenu(nullptr),
      mMenu(nullptr),
      mPauseMenu(nullptr),
      mMiddleMenu(nullptr),
      mModeMenu(nullptr),
      mGameOver(nullptr),

      mGameState(game_state::Notice_Menu), // by default we get into the Notice Menu with option -1

      player1(new User("Player 1")),
      player2(new User("Player 2")),
      winner(""),
      last_highscore(0),
      last_highscore_name(""),

      mletter(nullptr)

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
    delete player1;
    delete player2;

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

    if (mletter)
    {
        delete mletter;
        mletter = nullptr;
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

    if (mOnHoldMusic)
    {
        Mix_FreeMusic(mOnHoldMusic);
        mOnHoldMusic = nullptr;
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

    if (mSetup)
    {
        delete mSetup;
        mSetup = nullptr;
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

    if (mPauseMusic)
    {
        Mix_FreeMusic(mPauseMusic);
        mPauseMusic = nullptr;
    }

    if (mAI)
    {
        delete mAI;
        mAI = nullptr;
    }

    // Quit SDL systems
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

bool Game::pause_button()
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
    mMenu = new page_3b_0t(renderer, police);
    mNoticeMenu = new page_2b_1t(renderer, police);
    mMiddleMenu = new page_3b_1t(renderer, police);
    mModeMenu = new page_4b_1t(renderer, police);
    mPauseMenu = new page_3b(renderer, police);
    mGameOver = new game_over(renderer, police);
    mSetup = new Setup(renderer, police);
    mletter = new Letter(400, 0, 30, renderer, police);

    // Creating the different objects of the game
    mPaddle1 = new Paddle(30, true);
    mPaddle2 = new Paddle(770, false);
    ball_creation(0); // Start with classic ball then it is updated over the choices at MiddleMenu

    // Load audio files (make sure these files exist in your project directory)
    mBackgroundMusic = Mix_LoadMUS("assets/background.wav");
    mPaddleHitSound = Mix_LoadWAV("assets/paddle_hit.wav");
    mWallHitSound = Mix_LoadWAV("assets/wall_hit.wav");
    mScoreSound = Mix_LoadWAV("assets/score.wav");
    mPauseMusic = Mix_LoadMUS("assets/pause.wav");

    mOnHoldMusic = Mix_LoadMUS("assets/onhold.wav");

    if (!mBackgroundMusic)
    {
        SDL_Log("Failed to load background music: %s", Mix_GetError());
    }

    if (!mPaddleHitSound)
    {
        SDL_Log("Failed to load paddle hit sound: %s", Mix_GetError());
    }

    if (!mOnHoldMusic)
    {
        SDL_Log("Failed to load onhold music: %s", Mix_GetError());
    }

    if (!mPauseMusic)
    {
        SDL_Log("Failed to load pause music: %s", Mix_GetError());
    }

    if (!mWallHitSound)
    {
        SDL_Log("Failed to load wall hit sound: %s", Mix_GetError());
    }

    if (!mScoreSound)
    {
        SDL_Log("Failed to load score sound: %s", Mix_GetError());
    }

    // Start playing background music on loop
    if (mBackgroundMusic)
    {
        Mix_PlayMusic(mBackgroundMusic, -1); // -1 means loop indefinitely
        Mix_VolumeMusic(MIX_MAX_VOLUME / 3); // 25% of the max volume for the background music
    }

    if (mOnHoldMusic)
    {
        Mix_PlayMusic(mOnHoldMusic, -1);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
    }

    if (mPaddleHitSound)
        Mix_VolumeChunk(mPaddleHitSound, MIX_MAX_VOLUME / 2);
    if (mWallHitSound)
        Mix_VolumeChunk(mWallHitSound, MIX_MAX_VOLUME / 4);
    if (mScoreSound)
        Mix_VolumeChunk(mScoreSound, MIX_MAX_VOLUME / 2);

    // Adding the AI functionality on the PAddle No 2
    mAI = new AI(mPaddle2);

    // Reading the High Score from the file
    if (Saving::highscore_exists())
    {
        HighScore local;
        if (Saving::load_highscore(local))
        {
            last_highscore = local.score;
            strncpy(last_highscore_name, local.name, 19);
            last_highscore_name[19] = '\0';
            SDL_Log("Initialized high score - Name: %s, Score: %d",
                    last_highscore_name, last_highscore);
        }
        else
        {
            SDL_Log("Failed to load high score from file during initialisation");
            // Initialize with defaults if load fails
            last_highscore = 0;
            strncpy(last_highscore_name, "None", 19);
            last_highscore_name[19] = '\0';
        }
    }

    return true;
}

void Game::loop()
{
    while (mIsRunning) // set to false when we either tap on the X to close the SDL window or when we tap on the Exit game button
    {
        game_logic();
        game();
        output();
    }
}

void Game::game_logic()
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
                player1->reset_score();
                player2->reset_score();

                if (mNoticeMenu->action_handler(event)) // we check which of two button was clicked
                {
                    if (mNoticeMenu->get_next_view()) // if we want to move on with this choice
                    {
                        std::string user_name;

                        switch (mNoticeMenu->get_notice_id())
                        {
                        case AI_MODE:
                            mMiddleMenu->set_mode_type(AI_MODE_SELECTION);
                            player2->set_user_name("DrixAI");

                            printf("What is the name of Player 1 ?\n");

                            // Receive the name on the termina
                            // printf("Enter your name: ");
                            // scanf("%s", name);
                            // player1->set_user_name(name);

                            user_name = GUI::player_name_input(renderer, police, 1);
                            player1->set_user_name(user_name);

                            mGameState = game_state::Middle_menu;
                            break;

                        case TWO_PLAYERS_MODE:
                            mGameState = game_state::Menu; // entering the internal menu of the game
                            break;

                        case STORYTIME_MODE:
                            user_name = GUI::player_name_input(renderer, police, 1);
                            player1->set_user_name(user_name);

                            user_name = GUI::player_name_input(renderer, police, 2);
                            player2->set_user_name(user_name);

                            mMiddleMenu->set_mode_type(BALL_TYPE_SELECTION);
                            mGameState = game_state::Middle_menu;
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
                            break;
                        case TWO_PLAYERS_MODE:
                            mNoticeMenu->set_notice_id(TWO_PLAYERS_MODE);
                            break;
                        case STORYTIME_MODE:
                            mNoticeMenu->set_notice_id(STORYTIME_MODE);
                            break;
                        case FUN_MODE:
                            mNoticeMenu->set_notice_id(FUN_MODE);
                            break;
                        default:
                            SDL_Log("Invalid mode id");
                            break;
                        }
                        mGameState = game_state::Notice_Menu;
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
                    std::string user_name;

                    if (mMenu->get_started())
                    {
                        // Demander les prénoms des joueurs
                        user_name = GUI::player_name_input(renderer, police, 1); // Utiliser la méthode de User pour demander le nom du joueur 1
                        player1->set_user_name(user_name);

                        user_name = GUI::player_name_input(renderer, police, 2);

                        // Mettre à jour l'objet user2 avec le prénom saisi
                        player2->set_user_name(user_name);

                        // printf("What is the name of Player 1 ?\n");
                        // printf("Enter your name: ");
                        // scanf("%s", name);
                        // player1->set_user_name(name);

                        // printf("\n\nWhat is the name of Player 2 ?\n");
                        // printf("Enter your name: ");
                        // scanf("%s", name);
                        // player2->set_user_name(name);

                        mMiddleMenu->set_mode_type(BALL_TYPE_SELECTION);
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
                        if (Saving::load_game(savedState))
                        {
                            player1->set_user_score(savedState.score1);
                            player2->set_user_score(savedState.score2);

                            player1->set_user_name(savedState.player1_name);
                            player2->set_user_name(savedState.player2_name);

                            mPaddle1->set_pos_y(savedState.paddle1_y);
                            mPaddle2->set_pos_y(savedState.paddle2_y);
                            ball_creation(savedState.ball_type);
                            mBall->set_position(savedState.ball_x, savedState.ball_y);
                            mBall->set_velocity(savedState.ball_vel_x, savedState.ball_vel_y);
                            update_background_color();

                            Saving::delete_save(); // Delete the saved game file once we have loaded the game state

                            mGameState = game_state::Playing;

                            SoundEffects::change_music_track(mBackgroundMusic);
                        }
                    }
                }
                else
                {
                    SDL_Log("Invalid action on Main menu");
                }
            }
            else if (mGameState == game_state::Playing || mGameState == game_state::AI_playing || mGameState == game_state::Storytime_playing)
            {
                SDL_Point clickPoint = {event.button.x, event.button.y};
                if (SDL_PointInRect(&clickPoint, &mPauseButtonRect)) // We go to pause menu if the pause button is clicked
                {
                    SoundEffects::change_music_track(mPauseMusic);

                    switch (mGameState)
                    {
                    case game_state::Playing:
                        mPauseMenu->set_mode_type(TWO_PLAYERS_MODE); // essential otherwise we show option sthat we shouldn;t on certain modes of the game
                        break;
                    case game_state::AI_playing:
                        mPauseMenu->set_mode_type(AI_MODE);
                        break;
                    case game_state::Storytime_playing:
                        mPauseMenu->set_mode_type(STORYTIME_MODE);
                        break;
                    default:
                        printf("ERROR: Unhandled pause menu option\n");
                    }

                    mGameState = game_state::Paused;
                }
                else
                {
                    SoundEffects::change_music_track(mBackgroundMusic);
                }
            }
            else if (mGameState == game_state::Paused)
            {
                if (mPauseMenu->action_handler(event))
                {
                    if (mPauseMenu->ShouldResume())
                    {
                        // mPauseMenu->set_mode_type(mNoticeMenu->get_notice_id()); // We go back to the mode we came from (either two players or AI) to make sure the correct redering
                        switch (mPauseMenu->get_mode_type())
                        {
                        case AI_MODE:
                            mGameState = game_state::AI_playing;
                            break;
                        case TWO_PLAYERS_MODE:
                            mGameState = game_state::Playing;
                            break;
                        case STORYTIME_MODE:
                            mGameState = game_state::Storytime_playing;
                            break;
                        default:
                            printf("ERROR: Unhandled pause menu option\n");
                        }

                        SoundEffects::change_music_track(mBackgroundMusic);
                    }
                    else if (mPauseMenu->ShouldSave() && mNoticeMenu->get_notice_id() == TWO_PLAYERS_MODE) // it only apears on the TWO PLAYERS MODE - the only supported version
                    {
                        SaveState saveState;
                        saveState.score1 = player1->get_user_score();
                        saveState.score2 = player2->get_user_score();
                        saveState.paddle1_y = mPaddle1->get_pos_y();
                        saveState.paddle2_y = mPaddle2->get_pos_y();
                        saveState.ball_x = mBall->get_pos_x();
                        saveState.ball_y = mBall->get_pos_y();
                        saveState.ball_vel_x = mBall->get_vel_x();
                        saveState.ball_vel_y = mBall->get_vel_y();
                        saveState.ball_type = mMiddleMenu->get_selected_option();

                        strncpy(saveState.player1_name, player1->get_user_name().c_str(), 19);
                        saveState.player1_name[19] = '\0'; // Ensuring that the name ends to \0 that is standar for string types
                        strncpy(saveState.player2_name, player2->get_user_name().c_str(), 19);
                        saveState.player2_name[19] = '\0';

                        if (Saving::save_game(saveState))
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

                        SoundEffects::change_music_track(mOnHoldMusic);
                    }
                    else if (mPauseMenu->get_exit_mode())
                    {
                        SoundEffects::change_music_track(mOnHoldMusic);

                        // We update the existens of the save file
                        mMenu->set_saved_file_exists();

                        if (mNoticeMenu->get_notice_id() == TWO_PLAYERS_MODE) // it only appears on the TWO PLAYERS MODE
                        {
                            mGameState = game_state::Game_Over;
                        }
                        else
                        {
                            mGameState = game_state::Choose_Mode;
                        }
                    }
                    else
                    {
                        printf("ERROR: Unhandled pause menu option\n");
                    }
                }
            }
            else if (mGameState == game_state::Game_Over)
            {
                mMenu->set_saved_file_exists();
                if (mGameOver->action_handler(event))
                {
                    switch (mNoticeMenu->get_notice_id())
                    {
                    case TWO_PLAYERS_MODE:
                        mGameState = game_state::Menu;

                        // Saving the High Score
                        HighScore new_highscore;

                        new_highscore.score = last_highscore;

                        strncpy(new_highscore.name, last_highscore_name, 19);
                        new_highscore.name[19] = '\0';

                        Saving::delete_highscore(); // In order to have a new fresh file that do not increase in size
                        Saving::save_highscore(new_highscore);

                        break;

                    case AI_MODE:
                        mGameState = game_state::Choose_Mode;
                        break;

                    case STORYTIME_MODE:
                        mGameState = game_state::Choose_Mode;
                        break;

                    default:
                        printf("ERROR: Unhandled game over menu option\n");
                        break;
                    }

                    SoundEffects::change_music_track(mOnHoldMusic);
                }
            }
            else if (mGameState == game_state::Middle_menu)
            {
                if (mMiddleMenu->action_handler(event))
                {
                    if (mMiddleMenu->get_mode_type() == BALL_TYPE_SELECTION)
                    {
                        if (mNoticeMenu->get_notice_id() == TWO_PLAYERS_MODE)
                        {
                            Saving::delete_save(); // delete only in the case that we start a new game

                            ball_creation(mMiddleMenu->get_selected_option());

                            // Reset game state
                            player1->reset_score();
                            player2->reset_score();

                            // Reset paddle positions
                            mPaddle1->set_pos_y(WINDOW_HEIGHT / 2.0f);
                            mPaddle2->set_pos_y(WINDOW_HEIGHT / 2.0f);

                            // Reset ball position and give it initial velocity
                            mBall->set_position(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
                            mBall->set_velocity(200.0f, 235.0f); // Initial ball speed

                            // Reset background colors
                            update_background_color();

                            mGameState = game_state::Playing;
                            SDL_Log("New default game started with selected ball type (%d)", mMiddleMenu->get_selected_option());
                        }
                        else if (mNoticeMenu->get_notice_id() == STORYTIME_MODE)
                        {
                            ball_creation(mMiddleMenu->get_selected_option());

                            // Reset game state
                            player1->reset_score();
                            player2->reset_score();

                            // Reset paddle positions
                            mPaddle1->set_pos_y(WINDOW_HEIGHT / 2.0f);
                            mPaddle2->set_pos_y(WINDOW_HEIGHT / 2.0f);

                            // Reset ball position and give it initial velocity
                            mBall->set_position(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
                            mBall->set_velocity(200.0f, 235.0f); // Initial ball speed

                            // Reset background colors
                            update_background_color();

                            mGameState = game_state::Storytime_playing;
                            SDL_Log("New Storytime game started with selected ball type (%d)", mMiddleMenu->get_selected_option());
                        }
                        else if (mNoticeMenu->get_notice_id() == AI_MODE)
                        {
                            player1->reset_score();
                            player2->reset_score();

                            mPaddle1->set_pos_y(WINDOW_HEIGHT / 2.0f);
                            mPaddle2->set_pos_y(WINDOW_HEIGHT / 2.0f);

                            ball_creation(mMiddleMenu->get_selected_option());

                            mBall->set_position(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
                            mBall->set_velocity(200.0f, 235.0f);
                            update_background_color();
                            mGameState = game_state::AI_playing;
                        }
                        else
                        {
                            printf("ERROR: Unhandled middle menu option under the BALL_TYPE_SELECTION\n");
                        }

                        // Starting the arcade background music
                        SoundEffects::change_music_track(mBackgroundMusic);
                    }
                    else if (mMiddleMenu->get_mode_type() == AI_MODE_SELECTION)
                    {
                        switch (mMiddleMenu->get_selected_option())
                        {
                        case AI_MODE_EASY:

                            mAI->setDifficulty(AI_MODE_EASY);
                            break;

                        case AI_MODE_NORMAL:
                            mAI->setDifficulty(AI_MODE_NORMAL);
                            break;

                        case AI_MODE_HARD:
                            mAI->setDifficulty(AI_MODE_HARD);
                            break;

                        default:
                            SDL_Log("Invalid ball type selected");
                            break;
                        }

                        // No change on the state of the game. It will update the output to show the ball menu since we changed the input mode
                        mMiddleMenu->set_mode_type(BALL_TYPE_SELECTION);
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

void Game::game()
{
    if (mGameState != game_state::Playing && mGameState != game_state::AI_playing && mGameState != game_state::Storytime_playing) // There is nothing to update if the game is not in playing state
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
    
    switch(mGameState)
    {
        case game_state::Playing:
            mPaddle2->update(travel_time);
            break;

        case game_state::AI_playing:
            if (mAI)
            {
                mAI->updateAI(mBall, travel_time);
            }
            else
            {
                SDL_Log("AI object is not initialized and it is returning a NILL");
            }
            break;

        case game_state::Storytime_playing:
            mPaddle2->update(travel_time);
            break;

        default:
            break;
    }


    mBall->update(travel_time, mPaddle1, mPaddle2, player1, player2);

    // Check for victory condition
    switch (mNoticeMenu->get_notice_id())
    {
    case TWO_PLAYERS_MODE:
        // Updating winner for the Game Over renderer page requirements
        if (player1->get_user_score() != player2->get_user_score())
        {
            winner = (player1->get_user_score() > player2->get_user_score()) ? player1->get_user_name() : player2->get_user_name();
        }
        else
        {
            winner = "It's a tie!";
        }
        mGameOver->set_winner(winner); // transfering the winner name on the game over page

        // High score logic
        if (player1->get_user_score() >= last_highscore || player2->get_user_score() >= last_highscore)
        {
            last_highscore = (player1->get_user_score() >= player2->get_user_score()) ? player1->get_user_score() : player2->get_user_score();

            strncpy(last_highscore_name, ((player1->get_user_score() >= player2->get_user_score()) ? player1->get_user_name() : player2->get_user_name()).c_str(), 19);
            last_highscore_name[19] = '\0';
        }

        break;

    case AI_MODE:
        if (player1->get_user_score() >= 10 || player2->get_user_score() >= 10)
        {
            // Decide who wins
            winner = (player1->get_user_score() >= 10) ? player1->get_user_name() : player2->get_user_name();
            mGameOver->set_winner(winner);
            mGameState = game_state::Game_Over;
        }
        else
        {
            return; // Nothing to do in that case
        }
        break;

    case STORYTIME_MODE:
        // Adding letters logic
        mletter->update_letter(travel_time, WINDOW_HEIGHT,player1, player2, mBall->get_pos_x(), mBall->get_pos_y(),15);

        // Same logic with AI_MODE
        if (player1->get_user_score() >= 15 || player2->get_user_score() >= 15)
        {
            winner = (player1->get_user_score() >= 10) ? player1->get_user_name() : player2->get_user_name();
            mGameOver->set_winner(winner);
            mGameState = game_state::Game_Over;
        }
        else
        {
            return; // Nothing to do in that case
        }
        break;

    default:
        SDL_Log("Invalid notice menu ID when we are at Game Over (before going back to inner menu or Choose mode menu)");
        break;
    }

    // Update background colors based on scores
    update_background_color();
}

void Game::update_background_color()
{
    // Player 1 background color
    if (player1->get_user_score() >= 7)
    {
        mBackgroundColor1.r = 0;
        mBackgroundColor1.g = 255;
        mBackgroundColor1.b = 0;
        mBackgroundColor1.a = 255;
    }
    else if (player1->get_user_score() >= 5)
    {
        mBackgroundColor1.r = 255;
        mBackgroundColor1.g = 0;
        mBackgroundColor1.b = 0;
        mBackgroundColor1.a = 255;
    }
    else if (player1->get_user_score() >= 3)
    {
        mBackgroundColor1.r = 0;
        mBackgroundColor1.g = 0;
        mBackgroundColor1.b = 255;
        mBackgroundColor1.a = 255;
    }
    else if (player1->get_user_score() >= 10)
    {
        mBackgroundColor1.r = 0;
        mBackgroundColor1.g = 0;
        mBackgroundColor1.b = 0;
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
    if (player2->get_user_score() >= 7)
    {
        mBackgroundColor2.r = 0;
        mBackgroundColor2.g = 255;
        mBackgroundColor2.b = 0;
        mBackgroundColor2.a = 255;
    }
    else if (player2->get_user_score() >= 5)
    {
        mBackgroundColor2.r = 255;
        mBackgroundColor2.g = 0;
        mBackgroundColor2.b = 0;
        mBackgroundColor2.a = 255;
    }
    else if (player2->get_user_score() >= 3)
    {
        mBackgroundColor2.r = 0;
        mBackgroundColor2.g = 0;
        mBackgroundColor2.b = 255;
        mBackgroundColor2.a = 255;
    }
    else if (player2->get_user_score() >= 10)
    {
        mBackgroundColor1.r = 0;
        mBackgroundColor1.g = 0;
        mBackgroundColor1.b = 0;
        mBackgroundColor1.a = 255;
    }
    else
    {
        mBackgroundColor2.r = 0;
        mBackgroundColor2.g = 0;
        mBackgroundColor2.b = 0;
        mBackgroundColor2.a = 255;
    }
}

void Game::output()
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
        mMenu->render_object(mNoticeMenu->get_notice_id(), last_highscore_name, last_highscore);
        return;
    }

    if (mGameState == game_state::Middle_menu)
    {
        mMiddleMenu->render_object();
        return;
    }

    if (mGameState == game_state::Game_Over)
    {
        mGameOver->render_object();
        return;
    }

    if (mGameState == game_state::Set_up)
    {
        mSetup->render_object();
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

    if (mNoticeMenu->get_notice_id() == STORYTIME_MODE)
    {
        mletter->render(renderer);
    }

    // Print scores
    SDL_Color white = {255, 255, 255, 255};

    std::string score1Text = std::to_string(player1->get_user_score()) + " [" + player1->get_user_name() + "]";
    std::string score2Text = std::to_string(player2->get_user_score()) + " [" + player2->get_user_name() + "]";

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    TTF_SetFontSize(police, 36);

    SDL_Surface *surf1 = TTF_RenderText_Solid(police, score1Text.c_str(), white);
    SDL_Surface *surf2 = TTF_RenderText_Solid(police, score2Text.c_str(), white);

    SDL_Texture *tex1 = SDL_CreateTextureFromSurface(renderer, surf1);
    SDL_Texture *tex2 = SDL_CreateTextureFromSurface(renderer, surf2);

    SDL_Rect score1Rect = {100, 20, surf1->w, surf1->h};
    SDL_Rect score2Rect = {500, 20, surf2->w, surf2->h};

    SDL_RenderCopy(renderer, tex1, nullptr, &score1Rect);
    SDL_RenderCopy(renderer, tex2, nullptr, &score2Rect);

    SDL_FreeSurface(surf1);
    SDL_FreeSurface(surf2);
    SDL_DestroyTexture(tex1);
    SDL_DestroyTexture(tex2);

    // Pause menu only on the default Pong game, AI mode or Storytime mode
    if (mNoticeMenu->get_notice_id() == AI_MODE || mNoticeMenu->get_notice_id() == TWO_PLAYERS_MODE || mNoticeMenu->get_notice_id() == STORYTIME_MODE) // We are rendering the Pause button only in the default Pong game
    {
        pause_button();
    }

    SDL_RenderPresent(renderer);
}

void Game::ball_creation(int type)
{
    delete mBall; // in order to prevent memory leak
    
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