#include "inverse_power.hpp"

InversiblePower::InversiblePower(int screenWidth, int screenHeight) 
    : Power(screenWidth, screenHeight) {
    reset(screenWidth);
}

void InversiblePower::update(float deltaTime, Paddle* racket1,Paddle* racket2, float ballX, float ballY, float ballRadius, SDL_Renderer* renderer) {
    if (isActive) {
        y += speed * deltaTime;
        // Vérifier la collision avec la balle
        if (checkCollision(ballX, ballY, ballRadius)) {

            if (ballX < x + width / 2)
            {
                effectDuration = 0.0f;  // L'effet dure 5 secondes
                effectActive = true;    // Activer l'effet
                isActive = false;
                racket1->set_up(-1);
                racket1->render_object(renderer);
                joueur = true;
                
            }
            else
            {
                effectDuration = 0.0f;  // L'effet dure 5 secondes
                effectActive = true;    // Activer l'effet
                isActive = false;
                racket2->set_up(-1);
                racket2->render_object(renderer);
                joueur = false;
                
                // Désactiver le bonus après la collision
            }
   
        }
        // Si le bonus sort de l'écran, il remonte
        if (y + height >= WINDOW_HEIGHT || y <= 0) {
            isActive = true;
            speed=-speed;
        }
        }
    else{
            
           if (effectActive) {
            effectDuration += deltaTime;
            if (effectDuration >= 10.0) {
                // Désactiver le bonus après 5 secondes   la collision
                if(joueur){
                    racket1->set_up(1);
                    effectActive = false; // Désactiver l'effet
                    racket1->render_object(renderer);
                    isActive = true;
                    reset(WINDOW_HEIGHT);
                    
                }
                else if (!joueur){
                    racket2->set_up(1);
                    effectActive = false; // Désactiver l'effet
                    racket2->render_object(renderer);
                    isActive = true;
                    reset(WINDOW_HEIGHT);
                }
                
            }
        }
    }
}

void InversiblePower::render(SDL_Renderer* renderer) {
    if (!isActive) return;

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

    isActive = true;  // Activer le bonus
}

