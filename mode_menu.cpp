// #############################################################################
// # File mode_menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "mode_menu.hpp"
#include "macros.hpp"
#include "renderers.hpp"

#include <iostream>
#include <string>

ModeMenu::ModeMenu(SDL_Renderer *_renderer, TTF_Font *font) :
    mode_id(-1),

    texture_menu(nullptr),
    renderer(_renderer),
    police(font)
{
    button_ai_mode = SDL_Rect{WINDOW_HEIGHT / 2 - 100, 150, 200, 50};
    button_two_players_mode = SDL_Rect{WINDOW_HEIGHT / 2, 150, 200, 50};
    button_storytime_mode = SDL_Rect{WINDOW_HEIGHT / 2 + 100, 150, 200, 50};
    button_fun_mode = SDL_Rect{WINDOW_HEIGHT / 2, 250, 200, 50};
}


ModeMenu::~ModeMenu()
{
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

bool ModeMenu::action_handler(const SDL_Event &event)
{
    // Reinitialising everything sinc ethis is a repeated menu
    mode_id = -1;

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        // Ball selection menu clicks
        if (SDL_PointInRect(&point, &button_ai_mode))
        {
            mode_id = 0;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_two_players_mode))
        {
            mode_id = 1;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_storytime_mode))
        {
            mode_id = 2;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_fun_mode))
        {
            mode_id = 3;
            return true;
        }
    }
    return false;
}

void ModeMenu::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Color text_color = {0, 0, 0, 0};

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police,"Select Ball Type", SDL_Rect{WINDOW_HEIGHT/2, 50, 200, 50},
                 text_color);

    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    Utilities::render_button(renderer, police, "AI mode", button_ai_mode, text_color);
    Utilities::render_button(renderer, police,"Classic Pong", button_two_players_mode, text_color);
    Utilities::render_button(renderer, police,"Storytime mode", button_storytime_mode, text_color);
    Utilities::render_button(renderer, police,"Fun mode", button_fun_mode, text_color);

    SDL_RenderPresent(renderer);
}