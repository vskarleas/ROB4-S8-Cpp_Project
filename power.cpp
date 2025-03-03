#include "power.hpp"
#include <iostream>

Power::Power(int screenWidth, int screenHeight)
{
    width = 30 + rand() % 20; // Taille entre 30 et 50 pixels
    height = 30 + rand() % 20;
    speed = 50.0f;        // Descente à 50 pixels/sec
    srand(time(nullptr)); // Initialiser les couleurs aléatoires
    reset(screenWidth);
}

void Power::update(float deltaTime, Paddle *racket1, Paddle *racket2, float ballX, float ballY, float ballRadius, SDL_Renderer *renderer)
{
    if (isActive)
    {
        y += speed * deltaTime;
        // Vérifier la collision avec la balle
        if (checkCollision(ballX, ballY, ballRadius))
        {

            if (ballX < x + width / 2)
            {
                racket1->setRacketHeight(racket1->get_racket_height() * 2); // Augmente la taille de la raquette
                effectDuration = 0.0f;                                      // L'effet dure 5 secondes
                effectActive = true;                                        // Activer l'effet
                isActive = false;
                racket1->render_object(renderer);
                joueur = true;
            }
            else
            {
                racket2->setRacketHeight(racket2->get_racket_height() * 2); // Augmente la taille de la raquette
                effectDuration = 0.0f;                                      // L'effet dure 5 secondes
                effectActive = true;                                        // Activer l'effet
                isActive = false;
                racket2->render_object(renderer);
                joueur = false;

                // Désactiver le bonus après la collision
            }
        }

        // Si le bonus sort de l'écran, il remonte
        if (y + height >= WINDOW_HEIGHT || y <= 0)
        {
            isActive = true;
            speed = -speed;
        }
    }
    else
    {

        if (effectActive)
        {
            effectDuration += deltaTime;
            if (effectDuration >= 10.0)
            {
                // Désactiver le bonus après 5secode  la collision
                if (joueur)
                {
                    racket1->setRacketHeight(racket1->get_racket_height() / 2); // Remettre la taille normale
                    effectActive = false;                                       // Désactiver l'effet
                    racket1->render_object(renderer);
                    isActive = true;
                    reset(WINDOW_HEIGHT);
                }
                else if (!joueur)
                {
                    // std::cout << "joueur2: " << joueur << std::endl;
                    racket2->setRacketHeight(racket2->get_racket_height() / 2); // Remettre la taille normale
                    effectActive = false;                                       // Désactiver l'effet
                    racket2->render_object(renderer);
                    isActive = true;
                    reset(WINDOW_HEIGHT);
                }
            }
        }
    }
}

void Power::render(SDL_Renderer *renderer)
{
    if (!isActive)
        return;

    SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), width, height};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    SDL_RenderFillRect(renderer, &rect);
}

bool Power::checkCollision(float ballX, float ballY, float ballRadius) const
{
    if (!isActive)
        return false;

    // Collision rectangle-cercle
    float closestX = (ballX < x) ? x : (ballX > x + width) ? x + width
                                                           : ballX;
    float closestY = (ballY < y) ? y : (ballY > y + height) ? y + height
                                                            : ballY;

    float distanceX = ballX - closestX;
    float distanceY = ballY - closestY;

    return (distanceX * distanceX + distanceY * distanceY) < (ballRadius * ballRadius);
}

void Power::reset(int screenWidth)
{
    // Nouvelle position aléatoire
    x = 100 + rand() % (600);
    y = 1; // Il commence au-dessus de l'écran
    // Couleur aléatoire
    color = {static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
    isActive = true; // Activer le bonus
}
