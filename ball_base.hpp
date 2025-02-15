#ifndef BALL_BASE_HPP
#define BALL_BASE_HPP
#include <SDL.h>

class BallBase
{
public:
    BallBase(float size = 15.0f);
    virtual ~BallBase() {};

    virtual void Update(float deltaTime, class Paddle *paddle1, class Paddle *paddle2, int &score1, int &score2);
    virtual void Draw(SDL_Renderer *renderer) = 0;
    virtual void Reset();

    void SetPosition(float x, float y) { mPosX = x; mPosY = y; }
    void SetVelocity(float velX, float velY) { mVelX = velX; mVelY = velY; }

    void RandomizeDirection();

    float GetVelX() const { return mVelX; }
    float GetVelY() const { return mVelY; }
    float GetPosX() const { return mPosX; }
    float GetPosY() const { return mPosY; }

protected:
    float mPosX;
    float mPosY;
    float mVelX;
    float mVelY;
    const float mBallSize;
};

#endif