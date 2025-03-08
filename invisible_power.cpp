/**
 * @file invisible_power.cpp
 * @brief Implementation of the InvisiblePower class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "invisible_power.hpp"
#include "macros.hpp"

#include <SDL.h>

/**
 * @brief Constructor for the InvisiblePower class
 * 
 * Initializes the star-shaped power at a random position
 * 
 * @param screen_width The width of the game screen
 * @param screenHeight The height of the game screen
 */
InvisiblePower::InvisiblePower(int screen_width, int screenHeight)
{
    x = 150 + rand() % (550);
    y = 0;
    width = 30 + rand() % 20; // Size between 30 and 50 pixels
    height = 30 + rand() % 20;
    speed = 80.0f;
    is_active = true;
}

/**
 * @brief Updates the power's position and handles ball visibility effects
 * 
 * Manages the star's movement, collision detection, and ball invisibility timing
 * 
 * @param time Time delta since last update
 * @param ball Pointer to the ball object
 * @param renderer SDL renderer for drawing
 */
void InvisiblePower::update(float time, BallBase *ball, SDL_Renderer *renderer)
{
    if (initialisation) // Only once, otherwise the ball will be invisible all the time
    {
        initialisation = false;
        ball->set_color(white);
    }

    // Star movement
    if (is_active)
    {
        y += speed * time;

        if (check_collision(ball))
        {
            is_active = false;
            invisible_ball = true;
            ball->set_color(black); // Make ball blend with background
            invisibility_duration = 0.0f; // Reset timer
            repeat = 0.0f;
        }

        if (y + height >= 600 || y <= -40) // Reverse star movement at screen edges
        {
            speed = -speed;
        }
    }
    else if (invisible_ball)
    {
        invisibility_duration += time;
        repeat += time;

        if (invisibility_duration >= 3.0)
        {
            // Return ball to original color after 3 seconds
            ball->set_color(white);
            invisibility_duration = 3.0f;
        }

        if (repeat >= 13.0)
        {
            // Star reappears after 13 seconds
            is_active = true;
            invisible_ball = false;
            y = 0; // Reset star position
        }
    }
}

/**
 * @brief Renders the star-shaped power on screen
 * 
 * Draws a star shape using SDL rendering functions
 * 
 * @param renderer SDL renderer for drawing
 */
void InvisiblePower::render(SDL_Renderer *renderer)
{
    if (!is_active)
        return;

    // Use yellow color from macros.hpp
    SDL_SetRenderDrawColor(renderer, yellow.r, yellow.g, yellow.b, yellow.a);

    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;
    float outerRadius = width / 2.0f;
    float innerRadius = outerRadius * 0.4f; // Inner radius for star points

    // Create a 5-pointed star (10 points total - alternating outer and inner)
    SDL_Point points[10];
    for (int i = 0; i < 10; i++)
    {
        // Rotate 36 degrees (2π/10) for each point
        float angle = i * 36 * M_PI / 180;
        // Use outer radius for main points, inner radius for inner points
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;

        points[i].x = static_cast<int>(centerX + radius * sin(angle));
        points[i].y = static_cast<int>(centerY - radius * cos(angle));
    }

    // Draw the star by connecting points
    for (int i = 0; i < 10; i++)
    {
        SDL_RenderDrawLine(renderer,
                           points[i].x, points[i].y,
                           points[(i + 1) % 10].x, points[(i + 1) % 10].y);
    }

    // Fill the star (optional - makes it more visible)
    for (int i = 0; i < 10; i += 2)
    {
        SDL_RenderDrawLine(renderer,
                           centerX, centerY,
                           points[i].x, points[i].y);
    }
}

/**
 * @brief Checks for collision between the power and the ball
 * 
 * @param ball_type Pointer to the ball object
 * @return true if collision detected, false otherwise
 */
bool InvisiblePower::check_collision(BallBase *ball_type) const
{
    if (!is_active)
        return false;

    SDL_Rect star = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height)};

    SDL_Rect ball = ball_type->boundaries();
    return SDL_HasIntersection(&star, &ball);
}
