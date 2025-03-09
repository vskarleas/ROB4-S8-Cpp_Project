#include "inverse_power.hpp"

InversiblePower::InversiblePower(int screenWidth, int screenHeight)
    : Power(screenWidth, screenHeight)
{
    reset(screenWidth);
}

void InversiblePower::update(float deltaTime, Paddle *racket1, Paddle *racket2, float ballX, float ballY, float ballRadius, SDL_Renderer *renderer)
{
    if (is_active)
    {
        y += speed * deltaTime;

        // Check collision with ball
        if (collision_check(ballX, ballY, ballRadius))
        {
            if (ballX < x + width / 2)
            {
                duration_effect = 0.0f;  // Effect lasts 5 seconds
                effect_is_active = true; // Activate effect
                is_active = false;
                racket1->set_up(-1);
                racket1->render_object(renderer);
                play = true;
            }
            else
            {
                duration_effect = 0.0f;  // Effect lasts 5 seconds
                effect_is_active = true; // Activate effect
                is_active = false;
                racket2->set_up(-1);
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
            duration_effect += deltaTime;
            if (duration_effect >= 10.0)
            {
                // Deactivate effect after 10 seconds
                if (play)
                {
                    racket1->set_up(1);
                    effect_is_active = false;
                    racket1->render_object(renderer);
                    is_active = true;
                    reset(WINDOW_HEIGHT);
                }
                else if (!play)
                {
                    racket2->set_up(1);
                    effect_is_active = false;
                    racket2->render_object(renderer);
                    is_active = true;
                    reset(WINDOW_HEIGHT);
                }
            }
        }
    }
}

void InversiblePower::render(SDL_Renderer *renderer)
{
    if (!is_active)
        return;

    // Set arrow color to red to indicate negative effect
    SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, 255);

    // Define arrow points (triangle)
    SDL_Point arrow[4] = {
        {static_cast<int>(x) + width / 2, static_cast<int>(y)},      // Arrow top
        {static_cast<int>(x), static_cast<int>(y) + height},         // Bottom left
        {static_cast<int>(x) + width, static_cast<int>(y) + height}, // Bottom right
        {static_cast<int>(x) + width / 2, static_cast<int>(y)}       // Back to top
    };

    // Draw arrow outline
    SDL_RenderDrawLines(renderer, arrow, 4);

    // Fill arrow (rudimentary)
    for (int i = 0; i < height / 2; i++)
    {
        SDL_RenderDrawLine(
            renderer,
            arrow[0].x - i, arrow[0].y + i,
            arrow[0].x + i, arrow[0].y + i);
    }
}

void InversiblePower::reset(int screenWidth)
{
    // New random position
    x = 100 + rand() % (600);
    y = 0; // Start above screen

    // Red color for negative effect
    color = red;

    is_active = true;

    // Make reappearance time longer (>15 seconds)
    // This is handled by the timing in update() but we could also
    // adjust the activation probability here
}
