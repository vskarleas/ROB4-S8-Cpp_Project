#include "square_ball.hpp"

#include "square_ball.hpp"

void SquareBall::Draw(SDL_Renderer *renderer)
{
    SDL_Rect ball = {
        static_cast<int>(mPosX - mBallSize / 2.0f),
        static_cast<int>(mPosY - mBallSize / 2.0f),
        static_cast<int>(mBallSize),
        static_cast<int>(mBallSize)
    };
    // Set color to white (R=255, G=255, B=255, A=255)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Fill the rectangle
    SDL_RenderFillRect(renderer, &ball);
}