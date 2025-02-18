// #############################################################################
// # File page_3b_1t.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "page_3b_1t.hpp"
#include "macros.hpp"
#include "renderers.hpp"

#include <iostream>
#include <string>

MiddleMenu::MiddleMenu(SDL_Renderer *_renderer, TTF_Font *font) : selected_button(-1),
                                                                  mode_type(-1),
                                                                  texture_middle_menu(nullptr),
                                                                  renderer(_renderer),
                                                                  police(font)
{
    button_1 = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 500, 200, 40}; // The tree following buttons willbe closer to each other
    button_2 = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 450, 200, 40};
    button_3 = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 400, 200, 40};
}

MiddleMenu::~MiddleMenu()
{
    // Deallocate menu texture
    if (texture_middle_menu)
    {
        SDL_DestroyTexture(texture_middle_menu);
        texture_middle_menu = nullptr;
    }
}

bool MiddleMenu::action_handler(const SDL_Event &event)
{
    // Reinitialisations
    selected_button = -1;
    // mode_type = -1;

    if (event.type == SDL_MOUSEMOTION)
    {
        SDL_Point point = {event.motion.x, event.motion.y};

        // Ball selection menu hover handling
        if (SDL_PointInRect(&point, &button_1))
            selected_button = 0;
        else if (SDL_PointInRect(&point, &button_2))
            selected_button = 1;
        else if (SDL_PointInRect(&point, &button_3))
            selected_button = 2;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        // Ball selection menu clicks
        if (SDL_PointInRect(&point, &button_1))
        {
            selected_button = 0;
            // GameSave::delete_save();
            return true;
        }
        else if (SDL_PointInRect(&point, &button_2))
        {
            selected_button = 1;
            // GameSave::delete_save();
            return true;
        }
        else if (SDL_PointInRect(&point, &button_3))
        {
            selected_button = 2;
            // GameSave::delete_save();
            return true;
        }
    }
    return false;
}

void MiddleMenu::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Color text_color = {0, 0, 0, 0};

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    if (mode_type == TWO_PLAYERS_MODE)
    {
        Utilities::render_button(renderer, police, "Select Ball Type", SDL_Rect{WINDOW_HEIGHT / 2, 50, 200, 50},
                                 text_color);

        TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
        Utilities::render_button(renderer, police, "Classic Ball", button_1, text_color);
        Utilities::render_button(renderer, police, "Square Ball", button_2, text_color);
        Utilities::render_button(renderer, police, "Triangle Ball", button_3, text_color);
    }
    else if (mode_type == AI_MODE)
    {
        Utilities::render_button(renderer, police, "Select difficulty level", SDL_Rect{WINDOW_HEIGHT / 2, 50, 200, 50},
                                 text_color);

        TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
        Utilities::render_button(renderer, police, "Easy", button_1, text_color);
        Utilities::render_button(renderer, police, "Normal", button_2, text_color);
        Utilities::render_button(renderer, police, "Hard", button_3, text_color);
    }

    SDL_RenderPresent(renderer);
}
