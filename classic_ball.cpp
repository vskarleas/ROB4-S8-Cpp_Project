// #############################################################################
// # File classic_base.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "classic_ball.hpp"

// Helper function to draw filled circle
void DrawFilledCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius)
{
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Draw horizontal lines to fill the circle
        SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
        SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
        SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
        SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void ClassicBall::render_object(SDL_Renderer* renderer)
{
    // Set color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // Draw filled circle
    DrawFilledCircle(renderer, 
        static_cast<int32_t>(pos_x),
        static_cast<int32_t>(pos_y),
        static_cast<int32_t>(ball_size / 2.0f));
}