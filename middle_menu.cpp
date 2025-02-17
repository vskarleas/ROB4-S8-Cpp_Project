// #############################################################################
// # File middle_menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "middle_menu.hpp"
#include "macros.hpp"
#include "renderers.hpp"

#include <iostream>
#include <string>

MiddleMenu::MiddleMenu(SDL_Renderer *_renderer, TTF_Font *font) : 
    selected_ball(-1),
    selected_button(-1),
    texture_middle_menu(nullptr),
    renderer(_renderer),
    police(font)
{
    button_circle_ball = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 500, 200, 40}; // The tree following buttons willbe closer to each other
    button_square_ball = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 450, 200, 40};
    button_triangle_ball = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 400, 200, 40};
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
    if (event.type == SDL_MOUSEMOTION)
    {
        SDL_Point point = {event.motion.x, event.motion.y};
        selected_button = -1;

        // Ball selection menu hover handling
        if (SDL_PointInRect(&point, &button_circle_ball))
            selected_button = 3;
        else if (SDL_PointInRect(&point, &button_square_ball))
            selected_button = 4;
        else if (SDL_PointInRect(&point, &button_triangle_ball))
            selected_button = 5;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        // Ball selection menu clicks
        if (SDL_PointInRect(&point, &button_circle_ball))
        {
            selected_ball = 0;
            // GameSave::delete_save();
            return true;
        }
        else if (SDL_PointInRect(&point, &button_square_ball))
        {
            selected_ball = 1;
            // GameSave::delete_save();
            return true;
        }
        else if (SDL_PointInRect(&point, &button_triangle_ball))
        {
            selected_ball = 2;
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
    SDL_Color text_color_selected = {100, 180, 190, 220};

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police,"Select Ball Type", SDL_Rect{WINDOW_HEIGHT/2, 50, 200, 50},
                 text_color);

    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    Utilities::render_button(renderer, police, "Classic Ball", button_circle_ball,
                 selected_button == 3 ? text_color_selected : text_color);
    Utilities::render_button(renderer, police,"Square Ball", button_square_ball,
                 selected_button == 4 ? text_color_selected : text_color);
    Utilities::render_button(renderer, police,"Triangle Ball", button_triangle_ball,
                 selected_button == 5 ? text_color_selected : text_color);

    SDL_RenderPresent(renderer);
}
