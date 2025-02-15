// #############################################################################
// # File ball_base.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "paddle.hpp"
#include "ball_base.hpp"

BallBase::BallBase(float size)
    : mPosX(400.0f), mPosY(300.0f), mVelX(0.0f), mVelY(0.0f), mBallSize(size)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    RandomizeDirection();
}

void BallBase::RandomizeDirection()
{
    // Generate random angle between -45 and 45 degrees
    float angle = (std::rand() % 90 - 45) * 3.14159f / 180.0f;
    float speed = 300.0f;

    // Randomly choose left or right direction
    float baseAngle = (std::rand() % 2) ? 0.0f : 3.14159f;
    angle += baseAngle;

    mVelX = speed * std::cos(angle);
    mVelY = speed * std::sin(angle);
}

void BallBase::Update(float deltaTime, Paddle *paddle1, Paddle *paddle2, int &score1, int &score2)
{
    mPosX += mVelX * deltaTime;
    mPosY += mVelY * deltaTime;

    if (mPosY <= 0.0f)
    {
        mPosY = 0.0f;
        mVelY *= -1;
    }
    else if (mPosY >= 600.0f)
    {
        mPosY = 600.0f;
        mVelY *= -1;
    }

    if (mPosX <= 0.0f)
    {
        score2++;
        Reset();
    }
    else if (mPosX >= 800.0f)
    {
        score1++;
        Reset();
    }

    SDL_Rect ballRect = {
        static_cast<int>(mPosX - mBallSize / 2.0f),
        static_cast<int>(mPosY - mBallSize / 2.0f),
        static_cast<int>(mBallSize),
        static_cast<int>(mBallSize)};

    SDL_Rect paddle1Rect = paddle1->GetRect();
    SDL_Rect paddle2Rect = paddle2->GetRect();

    if (SDL_HasIntersection(&ballRect, &paddle1Rect))
    {
        mPosX = paddle1Rect.x + paddle1Rect.w + mBallSize / 2.0f;
        mVelX *= -1.1f;
    }
    else if (SDL_HasIntersection(&ballRect, &paddle2Rect))
    {
        mPosX = paddle2Rect.x - mBallSize / 2.0f;
        mVelX *= -1.1f;
    }
}

void BallBase::Reset()
{
    mPosX = 400.0f;
    mPosY = 300.0f;
    RandomizeDirection();
}