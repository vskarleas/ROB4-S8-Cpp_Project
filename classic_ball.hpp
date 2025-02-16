// #############################################################################
// # File classic_base.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef CLASSIC_BALL_HPP
#define CLASSIC_BALL_HPP

#include "ball_base.hpp"


class ClassicBall : public BallBase
{
public:
    // Constructor with default size of 15.0f for a circle object (specified)
    ClassicBall() : BallBase(15.0f) {}

    // Rendering the square ball
    void render_object(SDL_Renderer *renderer) override;
};

#endif