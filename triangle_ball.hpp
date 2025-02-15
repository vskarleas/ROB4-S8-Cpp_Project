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