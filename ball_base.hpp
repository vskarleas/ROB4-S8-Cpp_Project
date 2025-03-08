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
    BallBase(float size = 15.0f); // Default size is 15.0f
    virtual ~BallBase() {};

    /* We are using virtual methods in order to respect the heritage synatx */

    // Updates the ball's position
    // Update the update method signature to use User pointers
    virtual void update(float travel_time, class Paddle *paddle1, class Paddle *paddle2, User *player1, User *player2);

    // Renders the ball
    virtual void render_object(SDL_Renderer *renderer) = 0;

    // Resets the ball's position
    virtual void reset();

    /* Randomize the direction_angle of the ball so that it doesn't start
       towards the same direction_angle every single time */
    void random_direction_angle();

    // Setters for position
    void set_position(float x, float y)
    {
        pos_x = x;
        pos_y = y;
    }

    // Setters for velocity of the generic ball
    void set_velocity(float velX, float velY)
    {
        vel_x = velX;
        vel_y = velY;
    }

    // Setters for color of the generic ball
    void set_color(const SDL_Color &new_color) { color = new_color; }

    // Returns the collision bounds of the ball - used for collision detection
    virtual SDL_Rect boundaries() const
    {
        return SDL_Rect{
            static_cast<int>(pos_x - ball_size / 2.0f),
            static_cast<int>(pos_y - ball_size / 2.0f),
            static_cast<int>(ball_size),
            static_cast<int>(ball_size)};
    }

    // Returns the velocity of the ball on the x-axis
    float get_vel_x() const { return vel_x; }

    // Returns the velocity of the ball on the y-axis
    float get_vel_y() const { return vel_y; }

    // Returns the x coordinate
    float get_pos_x() const { return pos_x; }

    // Retruns the y coordinate
    float get_pos_y() const { return pos_y; }

    // Returns the color of the ball as a SDL_Color structure
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