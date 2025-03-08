// #############################################################################
// # File power.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "power.hpp"

#include <iostream>

Power::Power(int screen_width, int screenHeight)
{
    width = 30 + rand() % 20; // Taille entre 30 et 50 pixels
    height = 30 + rand() % 20;
    speed = 50.0f;        // Descente à 50 pixels/sec
    srand(time(nullptr)); // Initialiser les couleurs aléatoires
    reset(screen_width);
}

void Power::update(float time, Paddle *racket1, Paddle *racket2, float ball_pos_x, float ball_pos_y, float ball_radius, SDL_Renderer *renderer)
{
    if (is_active)
    {
        y += speed * time;
        // Vérifier la collision avec la balle
        if (collision_check(ball_pos_x, ball_pos_y, ball_radius))
        {

            if (ball_pos_x < x + width / 2)
            {
                racket1->set_racket_height(racket1->get_racket_height() * 2); // Augmente la taille de la raquette
                duration_effect = 0.0f;                                       // L'effet dure 5 secondes
                effect_is_active = true;                                      // Activer l'effet
                is_active = false;
                racket1->render_object(renderer);
                play = true;
            }
            else
            {
                racket2->set_racket_height(racket2->get_racket_height() * 2); // Augmente la taille de la raquette
                duration_effect = 0.0f;                                       // L'effet dure 5 secondes
                effect_is_active = true;                                      // Activer l'effet
                is_active = false;
                racket2->render_object(renderer);
                play = false;

                // Désactiver le bonus après la collision
            }
        }

        // Si le bonus sort de l'écran, il remonte
        if (y + height >= WINDOW_HEIGHT || y <= 0)
        {
            is_active = true;
            speed = -speed;
        }
    }
    else
    {

        if (effect_is_active)
        {
            duration_effect += time;
            if (duration_effect >= 10.0)
            {
                // Désactiver le bonus après 5secode  la collision
                if (play)
                {
                    racket1->set_racket_height(racket1->get_racket_height() / 2); // Remettre la taille normale
                    effect_is_active = false;                                     // Désactiver l'effet
                    racket1->render_object(renderer);
                    is_active = true;
                    reset(WINDOW_HEIGHT);
                }
                else if (!play)
                {
                    // std::cout << "play2: " << play << std::endl;
                    racket2->set_racket_height(racket2->get_racket_height() / 2); // Remettre la taille normale
                    effect_is_active = false;                                     // Désactiver l'effet
                    racket2->render_object(renderer);
                    is_active = true;
                    reset(WINDOW_HEIGHT);
                }
            }
        }
    }
}

void Power::render(SDL_Renderer *renderer)
{
    if (!is_active)
        return;

    SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), width, height};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    SDL_RenderFillRect(renderer, &rect);
}

bool Power::collision_check(float ball_pos_x, float ball_pos_y, float ball_radius) const
{
    if (!is_active)
        return false;

    // Collision rectangle-cercle
    float closestX = (ball_pos_x < x) ? x : (ball_pos_x > x + width) ? x + width
                                                                     : ball_pos_x;
    float closestY = (ball_pos_y < y) ? y : (ball_pos_y > y + height) ? y + height
                                                                      : ball_pos_y;

    float distanceX = ball_pos_x - closestX;
    float distanceY = ball_pos_y - closestY;

    return (distanceX * distanceX + distanceY * distanceY) < (ball_radius * ball_radius);
}

void Power::reset(int screen_width)
{
    // Nouvelle position aléatoire
    x = 100 + rand() % (600);
    y = 1; // Il commence au-dessus de l'écran
    // Couleur aléatoire
    color = {static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
    is_active = true; // Activer le bonus
}
