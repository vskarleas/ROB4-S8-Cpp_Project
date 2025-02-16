// #############################################################################
// # File ball_base.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef BALL_BASE_HPP
#define BALL_BASE_HPP

#include <SDL.h>

class BallBase
{
public:
    // Constructor
    BallBase(float size = 15.0f); // Default size is 15.0f
    virtual ~BallBase() {};

    
    /* We are using virtual methods in order to respect the heritage synatx */

    // Updates the ball's position
    virtual void update(float travel_time, class Paddle *paddle1, class Paddle *paddle2, int &score1, int &score2);
    virtual void render_object(SDL_Renderer *renderer) = 0;

    // Resets the ball's position
    virtual void reset();

    /* Randomize the direction_angle of the ball so that it doesn't start 
       towards the same direction_angle every single time */
    void random_direction_angle();

    // Setters for position and velocity of the generic ball
    void set_position(float x, float y) { pos_x = x; pos_y = y; }
    void set_velocity(float velX, float velY) { vel_x = velX; vel_y = velY; }


    // Getters
    float get_vel_x() const { return vel_x; }
    float get_vel_y() const { return vel_y; }
    float get_pos_x() const { return pos_x; }
    float get_pos_y() const { return pos_y; }

protected:
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    const float ball_size;
};

#endif