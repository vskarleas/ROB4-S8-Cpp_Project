// #############################################################################
// # File paddle.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "paddle.hpp"

/* Constructing the Racket object for the game */
Paddle::Paddle(int x, bool on_the_left_side): 
    // Paddle's position on the screen initially
    pos_y(300.0f), 
    pos_x(static_cast<float>(x)),

    // Paddle's caracteristics that compose the object height x width
    racket_height(100.0f), 
    racket_width(15.0f),

    // Paddle's speed for mouvement
    racket_speed(300.0f), 
    is_left(on_the_left_side) 
{
}

/* Updating the paddle's position on the screen */
void Paddle::Update(float travel_time)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (Paddle::get_is_left())
    {
        if (state[SDL_SCANCODE_W])
        {
            Paddle::set_pos_y(Paddle::get_pos_y() - Paddle::get_racket_speed() * travel_time);
        }
        if (state[SDL_SCANCODE_S])
        {
            Paddle::set_pos_y(Paddle::get_pos_y() + Paddle::get_racket_speed() * travel_time);
        }
    }
    else
    {
        if (state[SDL_SCANCODE_UP])
        {
            Paddle::set_pos_y(Paddle::get_pos_y() - Paddle::get_racket_speed() * travel_time);
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            Paddle::set_pos_y(Paddle::get_pos_y() + Paddle::get_racket_speed() * travel_time);
        }
    }

    if (Paddle::get_pos_y() < Paddle::get_racket_height() / 2.0f)
    {
        Paddle::set_pos_y(Paddle::get_racket_height() / 2.0f);
    }
    else if (Paddle::get_pos_y() > 600.0f - Paddle::get_racket_height() / 2.0f)
    {
        Paddle::set_pos_y(600.0f - Paddle::get_racket_height() / 2.0f);
    }
}

/* Drawing the paddle on the screen */
void Paddle::Draw(SDL_Renderer *renderer)
{
    SDL_Rect paddle = {
        static_cast<int>(Paddle::get_pos_x() - Paddle::get_racket_width() / 2.0f),
        static_cast<int>(Paddle::get_pos_y() - Paddle::get_racket_height() / 2.0f),
        static_cast<int>(Paddle::get_racket_width()),
        static_cast<int>(Paddle::get_racket_height())};
    SDL_RenderFillRect(renderer, &paddle);
}

/* Getting the paddle's position on the screen on SDL */
SDL_Rect Paddle::GetRect() const
{
    SDL_Rect rect = {
        static_cast<int>(Paddle::get_pos_x() - Paddle::get_racket_width() / 2.0f),
        static_cast<int>(Paddle::get_pos_y() - Paddle::get_racket_height() / 2.0f),
        static_cast<int>(Paddle::get_racket_width()),
        static_cast<int>(Paddle::get_racket_height())};
    return rect;
}