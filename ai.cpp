// #############################################################################
// # File ai.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

// #############################################################################
// # File ai.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "ai.hpp"
#include <cmath> // pour fabs si besoin

/* Constructeur */
AI::AI(Paddle* controlledPaddle)
    : mPaddle(controlledPaddle),
      mDifficulty(1) // Niveau normal par défaut
{
}

/* Ajuste la difficulté de l'IA (0=facile, 1=normal, 2=difficile) */
void AI::setDifficulty(int difficulty)
{
    mDifficulty = difficulty;
}

/* Mise à jour de la raquette contrôlée par l'IA selon la balle */
void AI::updateAI(BallBase* ball, float dt)
{
    if (!mPaddle || !ball)
        return; // sécurité

    // On récupère la position de la raquette et de la balle
    float paddleY = mPaddle->get_pos_y();
    float ballY   = ball->get_pos_y();
    float speed   = mPaddle->get_racket_speed(); // ex: 300

    // offset : pour ne pas être parfait
    float offset = 10.0f;

    // On règle la vitesse de réaction selon la difficulté
    float reactionFactor = 1.0f;
    switch (mDifficulty)
    {
    case 0: // facile
        reactionFactor = 0.6f; // plus lent => plus simple de passer
        break;
    case 1: // normal
        reactionFactor = 1.0f;
        break;
    case 2: // difficile
        reactionFactor = 1.4f; // plus rapide => plus dur pour le joueur
        break;
    }

    // Si la balle est au-dessus de la raquette, on monte
    if (ballY < paddleY - offset)
    {
        mPaddle->set_pos_y(paddleY - speed * reactionFactor * dt);
    }
    // Si la balle est en dessous, on descend
    else if (ballY > paddleY + offset)
    {
        mPaddle->set_pos_y(paddleY + speed * reactionFactor * dt);
    }

    // Empêche la raquette de sortir de l'écran (0..600)
    float halfH = mPaddle->get_racket_height() / 2.0f;
    if (mPaddle->get_pos_y() < halfH)
    {
        mPaddle->set_pos_y(halfH);
    }
    else if (mPaddle->get_pos_y() > (600.0f - halfH))
    {
        mPaddle->set_pos_y(600.0f - halfH);
    }
}
