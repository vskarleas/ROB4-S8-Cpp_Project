#include "ball.hpp"
#include "paddle.hpp"

Ball::Ball()
    : mPosX(400.0f), mPosY(300.0f), mVelX(-200.0f), mVelY(235.0f), mBallSize(15.0f) // Initialize here
{
}

void Ball::Update(float deltaTime, Paddle *paddle1, Paddle *paddle2, int &score1, int &score2)
{
    mPosX += mVelX * deltaTime;
    mPosY += mVelY * deltaTime;

    // Bounce off top and bottom walls
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

    // Check for scoring
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

    // Check collision with paddles
    SDL_Rect ballRect = {
        static_cast<int>(mPosX - mBallSize / 2.0f),
        static_cast<int>(mPosY - mBallSize / 2.0f),
        static_cast<int>(mBallSize),
        static_cast<int>(mBallSize)};

    // Get paddle rectangles once to avoid temporary objects
    SDL_Rect paddle1Rect = paddle1->GetRect();
    SDL_Rect paddle2Rect = paddle2->GetRect();

    if (SDL_HasIntersection(&ballRect, &paddle1Rect))
    {
        mPosX = paddle1Rect.x + paddle1Rect.w + mBallSize / 2.0f;
        mVelX *= -1.1f; // Increase speed slightly
    }
    else if (SDL_HasIntersection(&ballRect, &paddle2Rect))
    {
        mPosX = paddle2Rect.x - mBallSize / 2.0f;
        mVelX *= -1.1f; // Increase speed slightly
    }
}

void Ball::Draw(SDL_Renderer *renderer)
{
    SDL_Rect ball = {
        static_cast<int>(mPosX - mBallSize / 2.0f),
        static_cast<int>(mPosY - mBallSize / 2.0f),
        static_cast<int>(mBallSize),
        static_cast<int>(mBallSize)
    };
    SDL_RenderFillRect(renderer, &ball);
}

void Ball::Reset()
{
    mPosX = 400.0f;
    mPosY = 300.0f;
    mVelX = -200.0f;
    mVelY = 235.0f;
}