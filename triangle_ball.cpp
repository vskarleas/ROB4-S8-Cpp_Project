// #############################################################################
// # File triangle_ball.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "triangle_ball.hpp"
#include <algorithm>

void TriangleBall::render_object(SDL_Renderer *renderer)
{
    // Three corners definition
    SDL_Point points[3] = {
        {static_cast<int>(pos_x), static_cast<int>(pos_y - ball_size / 2)},                  // Top
        {static_cast<int>(pos_x - ball_size / 2), static_cast<int>(pos_y + ball_size / 2)}, // Bottom left
        {static_cast<int>(pos_x + ball_size / 2), static_cast<int>(pos_y + ball_size / 2)}  // Bottom right
    };

    // White color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Fill the triangle shape
    int minimum_y = points[0].y;  // Top point
    int maximum_y = points[1].y;  // Bottom points have same y

    for (int y = minimum_y; y <= maximum_y; y++)
    {
        // Calculate x coordinates where this horizontal line collides with the triangle lines
        float alpha = static_cast<float>(y - minimum_y) / (maximum_y - minimum_y);
        
        int x1 = static_cast<int>(points[0].x + alpha * (points[1].x - points[0].x));
        int x2 = static_cast<int>(points[0].x + alpha * (points[2].x - points[0].x));

        // Draw horizontal line
        SDL_RenderDrawLine(renderer, std::min(x1, x2), y, std::max(x1, x2), y);
    }
}