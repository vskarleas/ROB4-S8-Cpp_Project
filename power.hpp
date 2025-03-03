#ifndef POWER_HPP
#define POWER_HPP

#include <SDL.h>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()

#include "paddle.hpp"
#include "macros.hpp"

class Power
{
public:
    Power(int screenWidth, int screenHeight); // Constructeur

    virtual void update(float deltaTime, Paddle *racket1, Paddle *racket2, float ballX, float ballY, float ballRadius, SDL_Renderer *renderer); // Fait descendre le bonus
    virtual void render(SDL_Renderer *renderer);                                                                                                // Affiche le bonus
    bool checkCollision(float ballX, float ballY, float ballRadius) const;                                                                      // Vérifie la collision avec la balle
    virtual void reset(int screenWidth);                                                                                                        // Réapparaît avec une nouvelle couleur et position

    bool isActive; // Indique si le bonus est actif ou pas

protected:
    float x = 0;
    float y = 0;
    bool joueur;
    int width, height;
    float speed;
    float effectDuration = 0.0f; // Temps restant avant la fin de l'effet
    bool effectActive = false;   // Indique si l'effet est en cours
    SDL_Color color;
};

#endif
