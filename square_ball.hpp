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
    SquareBall() : BallBase(20.0f) {}
    void Draw(SDL_Renderer *renderer) override;
};

#endif