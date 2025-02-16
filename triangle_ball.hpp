// #############################################################################
// # File trangle_ball.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef TRIANGLE_BALL_HPP
#define TRIANGLE_BALL_HPP

#include "ball_base.hpp"

class TriangleBall : public BallBase
{
public:
    // Constructor with default size of 20.0f for a triangle object this time (check render_object method in triangle_ball.cpp)
    TriangleBall() : BallBase(20.0f) {}
    void render_object(SDL_Renderer *renderer) override; // overriding the render_object method from BallBase
};

#endif