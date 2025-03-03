// #############################################################################
// # File renderers.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef RENDER_HPP
#define RENDER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <algorithm>

/* Rendering an SDL rectangle which plays the role of a button */
namespace Utilities
{
    void render_button(SDL_Renderer *renderer, TTF_Font *font, const char *text,
                       const SDL_Rect &button, const SDL_Color &color);
}

struct circle_renderer
{
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;

private:
    void DrawFilledCircle(SDL_Renderer *renderer, int32_t center_x, int32_t centerY, int32_t radius) const;
};

struct square_renderer
{
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;
};

struct triangle_renderer
{
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;
};

#endif