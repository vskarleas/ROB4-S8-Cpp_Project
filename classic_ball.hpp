// #############################################################################
// # File classic_base.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef CLASSIC_BALL_HPP
#define CLASSIC_BALL_HPP

#include "ball_base.hpp"

class ClassicBall : public BallBase
{
public:
    ClassicBall() : BallBase(15.0f) {}
    void Draw(SDL_Renderer *renderer) override;
};

#endif