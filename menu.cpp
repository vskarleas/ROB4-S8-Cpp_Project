// #############################################################################
// # File menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include <string>

#include "menu.hpp"
#include "game_save.hpp"
#include "macros.hpp"
#include "renderers.hpp"

Menu::Menu(SDL_Renderer *_renderer, TTF_Font *font) : /* Follwoing the order in the class declaration*/
    start_new_game(false),
    exit_mode(false),
    continue_game(false),
    saved_file_exists(GameSave::save_exists()), // calls the save_exists() function to check if a game state file exists

    texture_menu(nullptr),
    renderer(_renderer),
    police(font)
{
    // Buttons positioning on the main menu page
    button_start = SDL_Rect{WINDOW_HEIGHT / 2, 100, 200, 50};
    button_continue = SDL_Rect{WINDOW_HEIGHT / 2, 180, 200, 50};
    button_exit = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 300, 200, 50}; // Keep space before exit
}

Menu::~Menu()
{
    // Deallocate menu texture
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

bool Menu::action_handler(const SDL_Event &event)
{
    // Reset the flags for new game, continue game and exit game, otherwise the logic is not triggered correctly
    start_new_game = false;
    continue_game = false;
    exit_mode = false;

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &button_start))
        {
            start_new_game = true;
            return true;
        }
        else if (saved_file_exists && SDL_PointInRect(&point, &button_continue))
        {
            continue_game = true;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_exit))
        {
            exit_mode = true;
            // SDL_Event quitEvent;
            // quitEvent.type = SDL_QUIT;
            // SDL_PushEvent(&quitEvent);
            return true;
        }
    }

    return false;
}

void Menu::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Color text_color = {0, 0, 0, 0};

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police, "Start New Game", button_start, text_color);

    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);

    if (saved_file_exists)
    {
        Utilities::render_button(renderer, police, "Continue Game", button_continue, text_color);
    }
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);

    Utilities::render_button(renderer, police, "Choose another mode", button_exit, text_color);

    SDL_RenderPresent(renderer);
}
