#include "inverse_power.hpp"

InversiblePower::InversiblePower(int screenWidth, int screenHeight) 
    : Power(screenWidth, screenHeight) {
    reset(screenWidth);
}

void InversiblePower::update(float deltaTime, Paddle* racket1,Paddle* racket2, float ballX, float ballY, float ballRadius, SDL_Renderer* renderer) {
    if (is_active) {
        y += speed * deltaTime;
        // Vérifier la collision avec la balle
        if (collision_check(ballX, ballY, ballRadius)) {

            if (ballX < x + width / 2)
            {
                duration_effect = 0.0f;  // L'effet dure 5 secondes
                effect_is_active = true;    // Activer l'effet
                is_active = false;
                racket1->set_up(-1);
                racket1->render_object(renderer);
                play = true;
                
            }
            else
            {
                duration_effect = 0.0f;  // L'effet dure 5 secondes
                effect_is_active = true;    // Activer l'effet
                is_active = false;
                racket2->set_up(-1);
                racket2->render_object(renderer);
                play = false;
                
                // Désactiver le bonus après la collision
            }
   
        }
        // Si le bonus sort de l'écran, il remonte
        if (y + height >= WINDOW_HEIGHT || y <= 0) {
            is_active = true;
            speed=-speed;
        }
        }
    else{
            
           if (effect_is_active) {
            duration_effect += deltaTime;
            if (duration_effect >= 10.0) {
                // Désactiver le bonus après 5 secondes   la collision
                if(play){
                    racket1->set_up(1);
                    effect_is_active = false; // Désactiver l'effet
                    racket1->render_object(renderer);
                    is_active = true;
                    reset(WINDOW_HEIGHT);
                    
                }
                else if (!play){
                    racket2->set_up(1);
                    effect_is_active = false; // Désactiver l'effet
                    racket2->render_object(renderer);
                    is_active = true;
                    reset(WINDOW_HEIGHT);
                }
                
            }
        }
    }
}

void InversiblePower::render(SDL_Renderer* renderer) {
    if (!is_active) return;

    // Définir la couleur de la flèche
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

    // Définir les points de la flèche (un triangle)
    SDL_Point arrow[4] = {
        {static_cast<int>(x) + width / 2, static_cast<int>(y)},            // Sommet de la flèche
        {static_cast<int>(x), static_cast<int>(y) + height},               // Coin bas gauche
        {static_cast<int>(x) + width, static_cast<int>(y) + height},       // Coin bas droit
        {static_cast<int>(x) + width / 2, static_cast<int>(y)}             // Retour au sommet pour fermer le triangle
    };

    // Dessiner le contour de la flèche
    SDL_RenderDrawLines(renderer, arrow, 4);

    // Optionnel : remplir la flèche (rudimentaire)
    for (int i = 0; i < height / 2; i++) {
        SDL_RenderDrawLine(renderer, arrow[0].x - i, arrow[0].y + i, arrow[0].x + i, arrow[0].y + i);
    }
}

void InversiblePower::reset(int screenWidth) {
    // Nouvelle position aléatoire
    x = 100 + rand() % (600);
    y = 1;  // Il commence au-dessus de l'écran

    // Couleur rouge pour indiqué un mallus 
    color = {255,0,0, 255};

    is_active = true;  // Activer le bonus
}

