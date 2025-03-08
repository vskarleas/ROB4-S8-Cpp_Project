/**
 * @file classic_ball.cpp
 * @brief Implementation of the classic circular ball class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "classic_ball.hpp"
#include "renderers.hpp"

/**
 * @brief Helper function to draw a filled circle
 * 
 * Uses the midpoint circle algorithm to efficiently render a filled circle
 * 
 * @param renderer The SDL renderer to use for drawing
 * @param center_x The x coordinate of the circle's center
 * @param centerY The y coordinate of the circle's center
 * @param radius The radius of the circle
 */
void DrawFilledCircle(SDL_Renderer *renderer, int32_t center_x, int32_t centerY, int32_t radius)
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
        SDL_RenderDrawLine(renderer, center_x - x, centerY + y, center_x + x, centerY + y);
        SDL_RenderDrawLine(renderer, center_x - x, centerY - y, center_x + x, centerY - y);
        SDL_RenderDrawLine(renderer, center_x - y, centerY + x, center_x + y, centerY + x);
        SDL_RenderDrawLine(renderer, center_x - y, centerY - x, center_x + y, centerY - x);

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

/**
 * @brief Renders the classic ball on screen
 * 
 * Uses the circle_renderer function to draw a circular shape
 * at the ball's current position with the specified size and color
 * 
 * @param renderer The SDL renderer used for drawing
 */
void ClassicBall::render_object(SDL_Renderer *renderer)
{
    circle_renderer()(renderer, pos_x, pos_y, ball_size, color);
}