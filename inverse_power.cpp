#include "inverse_power.hpp"

InversiblePower::InversiblePower(int screen_width, int screen_height)
    : Power(screen_width, screen_height)
{
    is_active = true;
    reset(screen_width);
}

void InversiblePower::update(float time, Paddle *racket1, Paddle *racket2, SDL_Renderer *renderer, BallBase *ball)
{
    // if (is_active)
    // {
    //     y += speed * time;

    //     // Check collision with ball
    //     if (collision(ball))
    //     {
    //         if (ball->get_pos_x() < x + width / 2)
    //         {
    //             duration_effect = 0.0f;  // Effect lasts 5 seconds
    //             effect_is_active = true; // Activate effect
    //             is_active = false;
    //             racket1->render_object(renderer);
    //         }
    //         else
    //         {
    //             duration_effect = 0.0f;  // Effect lasts 5 seconds
    //             effect_is_active = true; // Activate effect
    //             is_active = false;
    //             racket2->set_up(-1);
    //             racket2->render_object(renderer);
    //             play = false;
    //         }
    //     }

    //     // If power goes off screen, reverse direction
    //     if (y + height >= WINDOW_HEIGHT || y <= 0)
    //     {
    //         is_active = true;
    //         speed = -speed;
    //     }
    // }
    // else
    // {
    //     if (effect_is_active)
    //     {
    //         duration_effect += time;
    //         if (duration_effect >= 10.0)
    //         {
    //             // Deactivate effect after 10 seconds
    //             if (play)
    //             {
    //                 racket1->set_up(1);
    //                 effect_is_active = false;
    //                 racket1->render_object(renderer);
    //                 is_active = true;
    //                 reset(WINDOW_HEIGHT);
    //             }
    //             else if (!play)
    //             {
    //                 racket2->set_up(1);
    //                 effect_is_active = false;
    //                 racket2->render_object(renderer);
    //                 is_active = true;
    //                 reset(WINDOW_HEIGHT);
    //             }
    //         }
    //     }
    // }

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

            // Deciding the change for the paddle's control
            if (ball->get_pos_x() < x + width / 2)
            {
                racket1->set_inverse_power_active(true);
            }
            else
            {
                racket2->set_inverse_power_active(true);
            }
        }

        if (y + height >= WINDOW_HEIGHT || y <= -40) // Reverse mouvement of the object
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
            // Return ball to original color after 3 seconds
            racket1->set_inverse_power_active(false);
            racket2->set_inverse_power_active(false);
            duration_effect = 6.5f;
        }

        if (repeat >= 9.0)
        {
            // Star reappears after 13 seconds
            is_active = true;
            effect_is_active = false;
            // y = 0; // Reset star position

            reset(WINDOW_HEIGHT);
        }
    }
}

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


    for (int i = 0; i < height / 2; i++)
    {
        SDL_RenderDrawLine(
            renderer,
            arrow[0].x - i, arrow[0].y + i,
            arrow[0].x + i, arrow[0].y + i);
    }
}

void InversiblePower::reset(int screen_width)
{
    int min_x = screen_width * 0.4;
    int max_x = screen_width * 0.9;

    x = min_x + rand() % (max_x - min_x);
    y = 0;

    color = {static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
    is_active = true;
}
