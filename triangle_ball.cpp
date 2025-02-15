// #############################################################################
// # File triangle_ball.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "triangle_ball.hpp"
#include <algorithm>

void TriangleBall::Draw(SDL_Renderer *renderer)
{
    // Define the three points of the triangle
    SDL_Point points[3] = {
        {static_cast<int>(mPosX), static_cast<int>(mPosY - mBallSize / 2)},                  // Top
        {static_cast<int>(mPosX - mBallSize / 2), static_cast<int>(mPosY + mBallSize / 2)}, // Bottom left
        {static_cast<int>(mPosX + mBallSize / 2), static_cast<int>(mPosY + mBallSize / 2)}  // Bottom right
    };

    // Set color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Fill the triangle by drawing horizontal lines
    int minY = points[0].y;  // Top point
    int maxY = points[1].y;  // Bottom points have same y

    for (int y = minY; y <= maxY; y++)
    {
        // Calculate x coordinates where this horizontal line intersects the triangle edges
        float alpha = static_cast<float>(y - minY) / (maxY - minY);
        
        int x1 = static_cast<int>(points[0].x + alpha * (points[1].x - points[0].x));
        int x2 = static_cast<int>(points[0].x + alpha * (points[2].x - points[0].x));

        // Draw horizontal line
        SDL_RenderDrawLine(renderer, std::min(x1, x2), y, std::max(x1, x2), y);
    }
}