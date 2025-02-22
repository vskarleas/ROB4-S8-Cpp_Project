// #############################################################################
// # File ai.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef AI_HPP
#define AI_HPP

#include "paddle.hpp"
#include "ball_base.hpp"


class AI
{
public:
    AI(Paddle* controlledPaddle);

    // Méthode appelée à chaque frame quand on est en mode IA
    // -> déplace la raquette de sorte à essayer de rattraper la balle
    void updateAI(BallBase* ball, float dt);

    // Ajuste la difficulté (0 = facile, 1 = normal, 2 = difficile)
    void setDifficulty(int difficulty);

private:
    Paddle* mPaddle; // La raquette que l'IA doit bouger
    int mDifficulty; // 0=facile, 1=normal, 2=difficile
};

#endif