// #############################################################################
// # File square_ball.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "square_ball.hpp"

#include "square_ball.hpp"

// Rendering the white square ball
void SquareBall::render_object(SDL_Renderer *renderer)
{
    SDL_Rect ball = {
        static_cast<int>(pos_x - ball_size / 2.0f), // setting the size
        static_cast<int>(pos_y - ball_size / 2.0f),
        static_cast<int>(ball_size),
        static_cast<int>(ball_size)
    };

    // Set color to white (R=255, G=255, B=255, A=255)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Filling the rectangle
    SDL_RenderFillRect(renderer, &ball);
}