#ifndef BALL_HPP
#define BALL_HPP
#include <SDL.h>

class Ball
{
public:
    Ball();
    void Update(float deltaTime, class Paddle *paddle1, class Paddle *paddle2, int &score1, int &score2);
    void Draw(SDL_Renderer *renderer);
    void Reset();

private:
    float mPosX;
    float mPosY;
    float mVelX;
    float mVelY;
    const float mBallSize; // Remove initialization here
};
#endif