// #############################################################################
// # File render.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "render.hpp"

namespace Utilities {
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