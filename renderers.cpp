// #############################################################################
// # File renderers.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "renderers.hpp"
#include <iostream>

namespace Utilities {

    // Function to render the text on the SDL screen as a button
    void render_button(SDL_Renderer* renderer, TTF_Font* font, const char* text, 
                      const SDL_Rect& button, const SDL_Color& color) {
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, color);
        if (text_surface) {
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            if (text_texture) {
                SDL_Rect textRect = {
                    button.x + (button.w - text_surface->w) / 2,
                    button.y + (button.h - text_surface->h) / 2,
                    text_surface->w,
                    text_surface->h
                };
                SDL_RenderCopy(renderer, text_texture, nullptr, &textRect);
                SDL_DestroyTexture(text_texture);
            }
            SDL_FreeSurface(text_surface);
        }
    }
}

// Implementation of the circle_renderer class
void circle_renderer::DrawFilledCircle(SDL_Renderer* renderer, int32_t center_x, int32_t centerY, int32_t radius) const {
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        SDL_RenderDrawLine(renderer, center_x - x, centerY + y, center_x + x, centerY + y);
        SDL_RenderDrawLine(renderer, center_x - x, centerY - y, center_x + x, centerY - y);
        SDL_RenderDrawLine(renderer, center_x - y, centerY + x, center_x + y, centerY + x);
        SDL_RenderDrawLine(renderer, center_x - y, centerY - x, center_x + y, centerY - x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

/* We are using functors to encapsulate teh shapes rendering logic used to show the different ball types. It allows us to add more easily new shape types and also accelerated a lot the different tests because the functors allowed the different renderers to be tested individually */


// Implementation of the circle_renderer class
void circle_renderer::operator()(SDL_Renderer* renderer, float pos_x, float pos_y, float size) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    DrawFilledCircle(renderer, 
        static_cast<int32_t>(pos_x),
        static_cast<int32_t>(pos_y),
        static_cast<int32_t>(size / 2.0f));
}

// Implementation of the square_renderer class
void square_renderer::operator()(SDL_Renderer* renderer, float pos_x, float pos_y, float size) const {
    SDL_Rect ball = {
        static_cast<int>(pos_x - size / 2.0f),
        static_cast<int>(pos_y - size / 2.0f),
        static_cast<int>(size),
        static_cast<int>(size)
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball);
}

// Implementation of the triangle_renderer class
void triangle_renderer::operator()(SDL_Renderer* renderer, float pos_x, float pos_y, float size) const {
    SDL_Point points[3] = {
        {static_cast<int>(pos_x), static_cast<int>(pos_y - size / 2)},
        {static_cast<int>(pos_x - size / 2), static_cast<int>(pos_y + size / 2)},
        {static_cast<int>(pos_x + size / 2), static_cast<int>(pos_y + size / 2)}
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int min_y = points[0].y;
    int max_y = points[1].y;

    for (int y = min_y; y <= max_y; y++) {
        float alpha = static_cast<float>(y - min_y) / (max_y - min_y);
        int x1 = static_cast<int>(points[0].x + alpha * (points[1].x - points[0].x));
        int x2 = static_cast<int>(points[0].x + alpha * (points[2].x - points[0].x));
        SDL_RenderDrawLine(renderer, std::min(x1, x2), y, std::max(x1, x2), y);
    }
}