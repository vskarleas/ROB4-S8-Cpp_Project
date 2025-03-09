#ifndef INVERSE_POWER_HPP
#define INVERSE_POWER_HPP

#include "power.hpp"
#include "macros.hpp"

class InversiblePower : public Power {
    public:
        InversiblePower(int screenWidth, int screenHeight);
        
        void update(float deltaTime, Paddle* racket1, Paddle* racket2, float ballX, float ballY, float ballRadius, SDL_Renderer* renderer) override;
        void render(SDL_Renderer* renderer) override;
        void reset(int screenWidth) override;
    };

#endif
