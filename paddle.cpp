#include "paddle.hpp"

Paddle::Paddle(int x, bool isLeft)
    : mPosY(300.0f)
    , mPosX(static_cast<float>(x))
    , mPaddleH(100.0f)    // Initialize here
    , mPaddleW(15.0f)     // Initialize here
    , mPaddleSpeed(300.0f) // Initialize here
    , mIsLeft(isLeft)
{}

void Paddle::Update(float deltaTime)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (mIsLeft)
    {
        if (state[SDL_SCANCODE_W])
        {
            mPosY -= mPaddleSpeed * deltaTime;
        }
        if (state[SDL_SCANCODE_S])
        {
            mPosY += mPaddleSpeed * deltaTime;
        }
    }
    else
    {
        if (state[SDL_SCANCODE_UP])
        {
            mPosY -= mPaddleSpeed * deltaTime;
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            mPosY += mPaddleSpeed * deltaTime;
        }
    }

    if (mPosY < mPaddleH / 2.0f)
    {
        mPosY = mPaddleH / 2.0f;
    }
    else if (mPosY > 600.0f - mPaddleH / 2.0f)
    {
        mPosY = 600.0f - mPaddleH / 2.0f;
    }
}

void Paddle::Draw(SDL_Renderer *renderer)
{
    SDL_Rect paddle = {
        static_cast<int>(mPosX - mPaddleW / 2.0f),
        static_cast<int>(mPosY - mPaddleH / 2.0f),
        static_cast<int>(mPaddleW),
        static_cast<int>(mPaddleH)
    };
    SDL_RenderFillRect(renderer, &paddle);
}

SDL_Rect Paddle::GetRect() const
{
    SDL_Rect rect = {
        static_cast<int>(mPosX - mPaddleW / 2.0f),
        static_cast<int>(mPosY - mPaddleH / 2.0f),
        static_cast<int>(mPaddleW),
        static_cast<int>(mPaddleH)
    };
    return rect;
}