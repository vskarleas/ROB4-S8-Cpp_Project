// #############################################################################
// # File mode_menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "mode_menu.hpp"
#include "macros.hpp"

#include <iostream>
#include <string>

ModeMenu::ModeMenu(SDL_Renderer *_renderer, TTF_Font *font) :
    ai_mode(false),
    two_players_mode(false),
    storytime_mode(false),
    fun_mode(false),

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