// #############################################################################
// # File power.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef POWER_HPP
#define POWER_HPP

#include <SDL.h>
#include <cstdlib>
#include <ctime>

#include "paddle.hpp"
#include "macros.hpp"

class Power
{
public:
    Power(int screen_width, int screenHeight); // Constructeur

    // Virtual method that updates the game's parameters based on the powers impact
    virtual void update(float time, Paddle *racket1, Paddle *racket2, float ball_pos_x, float ball_pos_y, float ball_radius, SDL_Renderer *renderer);
    virtual void render(SDL_Renderer *renderer);

    // Checks if the ball has hit one of the powers elements
    bool collision_check(float ball_pos_x, float ball_pos_y, float ball_radius) const;
    virtual void reset(int screen_width);

    bool is_active; // Used to determine game's reaction. It updates the effect_is_active boolean

protected:
    float x = 0;
    float y = 0;
    bool play;
    int width, height;
    float speed;
    float duration_effect = 0.0f; // Temps restant avant la fin de l'effet
    bool effect_is_active = false;   // Global variable that saves if the effect is active or not
    SDL_Color color;
};

#endif
