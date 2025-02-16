// #############################################################################
// # File square_ball.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef SQUARE_BALL_HPP
#define SQUARE_BALL_HPP

#include "ball_base.hpp"

class SquareBall : public BallBase
{
public:
    // Constructor with default size of 20.0f for a square object this time (check render_object method in square_ball.cpp)
    SquareBall() : BallBase(20.0f) {}
    void render_object(SDL_Renderer *renderer) override;
};

#endif