// #############################################################################
// # File ball_base.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef BALL_BASE_HPP
#define BALL_BASE_HPP

#include <SDL.h>
#include "user.hpp"

class BallBase
{
public:
    // Constructor
    BallBase(float size = 15.0f); // Default size is 15.0f
    virtual ~BallBase() {};

    /* We are using virtual methods in order to respect the heritage synatx */

    // Updates the ball's position
    // Update the update method signature to use User pointers
    virtual void update(float travel_time, class Paddle *paddle1, class Paddle *paddle2, User *player1, User *player2);
    virtual void render_object(SDL_Renderer *renderer) = 0;

    // Resets the ball's position
    virtual void reset();

    /* Randomize the direction_angle of the ball so that it doesn't start
       towards the same direction_angle every single time */
    void random_direction_angle();

    // Setters for position and velocity of the generic ball
    void set_position(float x, float y)
    {
        pos_x = x;
        pos_y = y;
    }
    void set_velocity(float velX, float velY)
    {
        vel_x = velX;
        vel_y = velY;
    }
    void set_color(const SDL_Color &new_color) { color = new_color; }

    // Returns the collision bounds of the ball
    virtual SDL_Rect boundaries() const
    {
        return SDL_Rect{
            static_cast<int>(pos_x - ball_size / 2.0f),
            static_cast<int>(pos_y - ball_size / 2.0f),
            static_cast<int>(ball_size),
            static_cast<int>(ball_size)};
    }

    // Getters
    float get_vel_x() const { return vel_x; }
    float get_vel_y() const { return vel_y; }
    float get_pos_x() const { return pos_x; }
    float get_pos_y() const { return pos_y; }
    SDL_Color get_color() const { return color; }

protected:
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    const float ball_size;
    SDL_Color color;
};

#endif