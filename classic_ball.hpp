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