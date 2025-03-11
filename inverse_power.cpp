/**
 * @file inverse_power.hpp
 * @brief Implementation of the InversiblePower class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "inverse_power.hpp"

/**
 * @brief Constructs an InversiblePower object
 * @param screen_width Width of the game screen
 * @param screen_height Height of the game screen
 * 
 * Initializes the power-up and sets it to active state.
 */
InversiblePower::InversiblePower(int screen_width, int screen_height)
    : Power(screen_width, screen_height)
{
    is_active = true;
    reset(screen_width);
}

/**
 * @brief Updates the power-up's state based on game events
 * 
 * Handles the power-up movement, collision detection with the ball,
 * activation of control inversion effect, and timing for effect duration.
 * When the ball collides with this power-up, the controls for the player
 * who last hit the ball are inverted for 3 seconds.
 * 
 * @param time Delta time since last frame
 * @param racket1 First player's paddle
 * @param racket2 Second player's paddle
 * @param renderer SDL renderer (unused in this method)
 * @param ball The game ball for collision detection
 */
void InversiblePower::update(float time, Paddle *racket1, Paddle *racket2, SDL_Renderer *renderer, BallBase *ball)
{
    if (is_active)
    {
        y += speed * time;

        if (collision(ball))
        {
            is_active = false;
            effect_is_active = true;

            // Reseting time variables
            duration_effect = 0.0f;
            repeat = 0.0f;

            // Deciding which paddle's controls to invert based on ball position
            if (ball->get_pos_x() < x + width / 2)
            {
                racket2->set_inverse_power_active(true);
            }
            else
            {
                racket1->set_inverse_power_active(true);
            }
        }

        if (y + height >= WINDOW_HEIGHT || y <= -40) // Reverse movement of the object
        {
            speed = -speed;
        }
    }
    else if (effect_is_active)
    {
        duration_effect += time;
        repeat += time;

        if (duration_effect >= 3.0)
        {
            // Return paddles to normal controls after 3 seconds
            racket1->set_inverse_power_active(false);
            racket2->set_inverse_power_active(false);
            duration_effect = 9.5f;
        }

        if (repeat >= 9.0)
        {
            // Power-up reappears after 9 seconds
            is_active = true;
            effect_is_active = false;
            
            reset(WINDOW_HEIGHT);
        }
    }
}

/**
 * @brief Renders the power-up on screen as an arrow
 * 
 * Draws the power-up as a red arrow pointing downward when active.
 * The arrow indicates that this power-up has a negative effect.
 * 
 * @param renderer SDL renderer to draw the power-up
 */
void InversiblePower::render(SDL_Renderer *renderer)
{
    if (!is_active)
        return;

    // Set arrow color to red to indicate negative effect
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Point arrow[4] = {
        {static_cast<int>(x) + width / 2, static_cast<int>(y)},
        {static_cast<int>(x), static_cast<int>(y) + height},
        {static_cast<int>(x) + width, static_cast<int>(y) + height},
        {static_cast<int>(x) + width / 2, static_cast<int>(y)}
    };

    // Draw arrow outline
    SDL_RenderDrawLines(renderer, arrow, 4);

    // Fill in the arrow
    for (int i = 0; i < height / 2; i++)
    {
        SDL_RenderDrawLine(
            renderer,
            arrow[0].x - i, arrow[0].y + i,
            arrow[0].x + i, arrow[0].y + i);
    }
}

/**
 * @brief Resets the power-up to a new random position
 * 
 * Places the power-up at a random horizontal position at the top of the screen
 * and assigns it a random color.
 * 
 * @param screen_width Width of the game screen for positioning
 */
void InversiblePower::reset(int screen_width)
{
    int min_x = screen_width * 0.4;
    int max_x = screen_width * 0.9;

    x = min_x + rand() % (max_x - min_x);
    y = 0;

    color = {static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
    is_active = true;
}
