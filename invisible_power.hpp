// #############################################################################
// # File invisible_power.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef INVISIBLE_POWER_HPP
#define INVISIBLE_POWER_HPP
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()
#include "classic_ball.hpp"
#include <cmath>

class InvisiblePower
{
public:
    InvisiblePower(int screen_width, int screenHeight);

    void update(float time, BallBase *Ball, SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer);
    SDL_Color previousColor; // Sauvegarde la couleur de la balle avant invisibilité
    bool is_active;
    bool check_collision(BallBase *ball) const;

    void set_initialisation(bool init) { initialisation = init; }

private:
    float x = 0;
    float y = 0;
    bool play;
    int width;
    int height;
    float speed;
    float invisibility_duration = 0.0f; // Temps restant avant la fin de l'effet
    float repeat;
    bool invisible_ball = false; // Indique si l'effet est en cours
    bool initialisation;
};

#endif
