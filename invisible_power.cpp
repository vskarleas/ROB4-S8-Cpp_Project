// #############################################################################
// # File invisible_power.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "invisible_power.hpp"
#include "macros.hpp"

#include <SDL.h>

InvisiblePower::InvisiblePower(int screenWidth, int screenHeight)
{
    x = 150 + rand() % (550);
    y = 0;
    width = 30 + rand() % 20; // size between 30 and 50 pixels
    height = 30 + rand() % 20;
    speed = 80.0f;              
    isActive = true;            
}

void InvisiblePower::update(float deltaTime, BallBase *ball, SDL_Renderer *renderer)
{
    if (initialisation) //only once, otherwise the ball will be invisible all the time
    {
        initialisation = false;
        ball->set_color(white);
    }

    // Star mouvement
    if (isActive)
    {
        y += speed * deltaTime;

        if (check_collision(ball))
        {
            isActive = false;
            invisible_ball = true;
            ball->set_color(black);
            invisibility_duration = 0.0f; // reinitialisation
            repeat = 0.0f;
        }

        if (y + height >= 600 || y <= -40) //inverting the mouvement of the star
        {
            speed = -speed;
        }
    }
    else if (invisible_ball)
    {
        invisibility_duration += deltaTime;
        repeat += deltaTime;

        if (invisibility_duration >= 3.0)
        {
            // Return to original color after 3 seconds
            ball->set_color(white);
            invisibility_duration = 3.0f;
        }

        if (repeat >= 13.0)
        {
            // Star reappears after 13 seconds
            isActive = true;
            invisible_ball = false;
            y = 0; // Reset star position
        }
    }
}

/* Rendere for the star object */
void InvisiblePower::render(SDL_Renderer *renderer)
{
    if (!isActive)
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

bool InvisiblePower::check_collision(BallBase* ball_type) const
{
    if (!isActive) return false;

    SDL_Rect star = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height)
    };
    
    SDL_Rect ball = ball_type->boundaries();
    return SDL_HasIntersection(&star, &ball);
}
