/**
 * @file power.cpp
 * @brief Implementation of the Power class for special game effects
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "power.hpp"

#include <iostream>

/**
 * @brief Constructor for the Power class
 * 
 * Initializes the power with random size and position
 * 
 * @param screen_width The width of the game screen
 * @param screenHeight The height of the game screen
 */
Power::Power(int screen_width, int screenHeight)
{
    width = 30 + rand() % 20; // Size between 30 and 50 pixels
    height = 30 + rand() % 20;
    speed = 50.0f;            // Movement speed of 50 pixels/sec
    srand(time(nullptr));     // Initialize random colors
    reset(screen_width);
}

/**
 * @brief Updates the power's position and checks for collision with the ball
 * 
 * Handles power movement, collision detection, and effect application/duration
 * 
 * @param time Time delta since last update
 * @param racket1 Pointer to first paddle
 * @param racket2 Pointer to second paddle
 * @param ball_pos_x Ball's X position
 * @param ball_pos_y Ball's Y position
 * @param ball_radius Ball's radius
 * @param renderer SDL renderer for drawing
 */
void Power::update(float time, Paddle *racket1, Paddle *racket2, float ball_pos_x, float ball_pos_y, float ball_radius, SDL_Renderer *renderer)
{
    if (is_active)
    {
        y += speed * time;
        // Check for collision with ball
        if (collision_check(ball_pos_x, ball_pos_y, ball_radius))
        {
            if (ball_pos_x < x + width / 2)
            {
                racket1->set_racket_height(racket1->get_racket_height() * 2); // Increase paddle size
                duration_effect = 0.0f;                                       
                effect_is_active = true;                                      
                is_active = false;
                racket1->render_object(renderer);
                play = true;
            }
            else
            {
                racket2->set_racket_height(racket2->get_racket_height() * 2); // Increase paddle size
                duration_effect = 0.0f;                                       
                effect_is_active = true;                                     
                is_active = false;
                racket2->render_object(renderer);
                play = false;
            }
        }

        // If power goes off screen, reverse direction
        if (y + height >= WINDOW_HEIGHT || y <= 0)
        {
            is_active = true;
            speed = -speed;
        }
    }
    else
    {
        if (effect_is_active)
        {
            duration_effect += time;
            if (duration_effect >= 10.0)
            {
                // Deactivate effect after 10 seconds
                if (play)
                {
                    racket1->set_racket_height(racket1->get_racket_height() / 2); // Return to normal size
                    effect_is_active = false;
                    racket1->render_object(renderer);
                    is_active = true;
                    reset(WINDOW_HEIGHT);
                }
                else if (!play)
                {
                    racket2->set_racket_height(racket2->get_racket_height() / 2); // Return to normal size
                    effect_is_active = false;
                    racket2->render_object(renderer);
                    is_active = true;
                    reset(WINDOW_HEIGHT);
                }
            }
        }
    }
}

/**
 * @brief Renders the power on screen
 * 
 * Draws a colored rectangle representing the power if it's active
 * 
 * @param renderer SDL renderer for drawing
 */
void Power::render(SDL_Renderer *renderer)
{
    if (!is_active)
        return;

    SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), width, height};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    SDL_RenderFillRect(renderer, &rect);
}

/**
 * @brief Checks if the ball has hit this power-up
 * 
 * Uses circle-rectangle collision detection
 * 
 * @param ball_pos_x Ball's X position
 * @param ball_pos_y Ball's Y position
 * @param ball_radius Ball's radius
 * @return true if collision detected, false otherwise
 */
bool Power::collision_check(float ball_pos_x, float ball_pos_y, float ball_radius) const
{
    if (!is_active)
        return false;

    // Circle-rectangle collision detection
    float closestX = (ball_pos_x < x) ? x : (ball_pos_x > x + width) ? x + width
                                                                     : ball_pos_x;
    float closestY = (ball_pos_y < y) ? y : (ball_pos_y > y + height) ? y + height
                                                                      : ball_pos_y;

    float distanceX = ball_pos_x - closestX;
    float distanceY = ball_pos_y - closestY;

    return (distanceX * distanceX + distanceY * distanceY) < (ball_radius * ball_radius);
}

/**
 * @brief Resets the power to a new random position
 * 
 * @param screen_width The width of the game screen
 */
void Power::reset(int screen_width)
{
    // New random position
    x = 100 + rand() % (600);
    y = 1; // Start above the screen
    // Random color
    color = {static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
    is_active = true; // Activate the power
}
