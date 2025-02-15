#ifndef PADDLE_HPP
#define PADDLE_HPP
#include <SDL.h>

class Paddle
{
public:
    Paddle(int x, bool isLeft);
    void Update(float deltaTime);
    void Draw(SDL_Renderer *renderer);
    float GetPosY() const { return mPosY; }
    SDL_Rect GetRect() const;

private:
    float mPosY;
    float mPosX;
    const float mPaddleH;     
    const float mPaddleW;    
    const float mPaddleSpeed; 
    bool mIsLeft;
};
#endif