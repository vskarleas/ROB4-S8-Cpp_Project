#ifndef INVERSE_POWER_HPP
#define INVERSE_POWER_HPP

#include "power.hpp"
#include "macros.hpp"

class InversiblePower : public Power {
    public:
        InversiblePower(int screen_width, int screen_height);
        
        void update(float time, Paddle* racket1, Paddle* racket2, SDL_Renderer* renderer, BallBase *ball) override;
        void render(SDL_Renderer* renderer) override;
        void reset(int screen_width) override;

    private:
        bool inverse_paddle = false; /**< Whether the power is currently active for a specific paddle */
        float repeat;               /**< Timer for power-up respawn */
    };



#endif
