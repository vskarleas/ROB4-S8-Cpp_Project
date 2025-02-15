// #############################################################################
// # File trangle_ball.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef TRIANGLE_BALL_HPP
#define TRIANGLE_BALL_HPP

#include "ball_base.hpp"

class TriangleBall : public BallBase
{
public:
    TriangleBall() : BallBase(25.0f) {}
    void Draw(SDL_Renderer *renderer) override;
};

#endif