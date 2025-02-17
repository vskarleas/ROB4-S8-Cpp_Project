// #############################################################################
// # File render.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef RENDER_HPP
#define RENDER_HPP

#include <SDL.h>
#include <SDL_ttf.h>

/* Rendering an SDL rectangle which plays the role of a button */
namespace Utilities {
    void render_button(SDL_Renderer* renderer, TTF_Font* font, const char* text, 
                      const SDL_Rect& button, const SDL_Color& color);
}

#endif