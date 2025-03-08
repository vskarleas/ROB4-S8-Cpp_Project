// #############################################################################
// # File page_3b_0t.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include <string>

#include "page_3b_0t.hpp"
#include "game_save.hpp"
#include "macros.hpp"
#include "renderers.hpp"
#include "game.hpp"

page_3b_0t::page_3b_0t(SDL_Renderer *_renderer, TTF_Font *font) : /* Follwoing the order in the class declaration*/
                                                                  start_new_game(false),
                                                                  exit_mode(false),
                                                                  continue_game(false),
                                                                  saved_file_exists(Saving::save_exists()), // calls the save_exists() function to check if a game state file exists

                                                                  texture_menu(nullptr),
                                                                  renderer(_renderer),
                                                                  police(font)
{
    // Buttons positioning on the main menu page
    button_start = SDL_Rect{WINDOW_HEIGHT / 2, 100, 200, 50};
    button_continue = SDL_Rect{WINDOW_HEIGHT / 2, 180, 200, 50};
    button_exit = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 300, 200, 50}; // Keep space before exit
}

page_3b_0t::~page_3b_0t()
{
    // Deallocate menu texture
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

bool page_3b_0t::action_handler(const SDL_Event &event)
{
    // Reset the flags for new game, continue game and exit game, otherwise the logic is not triggered correctly
    start_new_game = false;
    continue_game = false;
    exit_mode = false;

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        SDL_Rect adjusted_start = button_start;
        SDL_Rect adjusted_continue = button_continue;
        adjusted_start.y += 50;
        adjusted_continue.y += 50;

        if (SDL_PointInRect(&point, &adjusted_start))
        {
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            start_new_game = true;
            return true;
        }
        else if (saved_file_exists && SDL_PointInRect(&point, &adjusted_continue))
        {
            continue_game = true;
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            return true;
        }
        else if (SDL_PointInRect(&point, &button_exit))
        {
            exit_mode = true;
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            // SDL_Event quitEvent;
            // quitEvent.type = SDL_QUIT;
            // SDL_PushEvent(&quitEvent);
            return true;
        }
    }

    return false;
}

void page_3b_0t::render_object(int mode, const std::string &highscore_name, int highscore)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Color highlight_color = {255, 0, 0, 255};

    // Show high score at the top if it exists
    if (mode == TWO_PLAYERS_MODE && !highscore_name.empty())
    {
        TTF_SetFontStyle(police, TTF_STYLE_BOLD);
        std::string highScoreText = "High Score: " + std::to_string(highscore) + " by " + highscore_name;
        SDL_Rect highScoreRect = {WINDOW_HEIGHT / 2 - 100, 20, 400, 50}; // Moved to top
        Utilities::render_button(renderer, police, highScoreText.c_str(), highScoreRect, highlight_color);

        // results on the terminal
        // SDL_Log("Current High Score - Player: %s, Score: %d", highscore_name.c_str(), highscore);
    }

    // Rest of the menu items moved down slightly to accommodate high score
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);

    SDL_Rect adjusted_start = button_start;
    SDL_Rect adjusted_continue = button_continue;
    adjusted_start.y += 50;
    adjusted_continue.y += 50;

    Utilities::render_button(renderer, police, "Start New Game", adjusted_start, black);

    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    if (saved_file_exists)
    {
        Utilities::render_button(renderer, police, "Continue Game", adjusted_continue, black);
    }

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police, "Choose another mode", button_exit, black);

    SDL_RenderPresent(renderer);
}
