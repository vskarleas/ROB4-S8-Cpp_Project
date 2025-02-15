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