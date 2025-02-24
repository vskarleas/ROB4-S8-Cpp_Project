// #############################################################################
// # File gui.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun - All rights reserved.
// #############################################################################

#include "gui.hpp"


std::string GUI::getPlayerNameInput(SDL_Renderer *renderer, TTF_Font *font)
{
    std::string playerName;
    SDL_Event event;
    bool typing = true;

    // Couleur du texte
    SDL_Color color = {0, 0, 0, 0};
    SDL_Rect textRect = {260, 150, 200, 100}; // Position du texte du prenom
    SDL_Rect textRect2 = {200, 60, 200, 100};

    SDL_Surface *backgroundSurface = SDL_CreateRGBSurface(0, 800, 600, 32, 0, 0, 0, 0);
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr); // Ajouter l'écran par-dessus sans effacer

    while (typing)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                typing = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    typing = false;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && playerName.length() > 0)
                {
                    playerName.pop_back();
                }
                else if (event.key.keysym.sym != SDLK_RETURN && event.key.keysym.sym != SDLK_BACKSPACE)
                {
                    char c = event.key.keysym.sym;
                    if (isprint(c))
                    {
                        playerName += c;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        // afficher un message d'instruction
        const char *instructionText = "Joueur, veuillez entrer votre prenom:";
        SDL_Surface *instructionSurface = TTF_RenderText_Solid(font, instructionText, color);
        SDL_Texture *instructionTexture = SDL_CreateTextureFromSurface(renderer, instructionSurface);

        // Positionner le message d'instruction
        SDL_Rect instructionRect = {textRect2.x, textRect2.y, instructionSurface->w, instructionSurface->h};

        // Afficher le message d'instruction
        SDL_RenderCopy(renderer, instructionTexture, nullptr, &instructionRect);

        // Libérer la surface et la texture du message après l'affichage
        SDL_FreeSurface(instructionSurface);
        SDL_DestroyTexture(instructionTexture);

        // Afficher le texte saisi
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, playerName.c_str(), color);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        // Rafraîchir l'écran
        SDL_RenderPresent(renderer);
    }

    // Libérer la texture de fond et la surface
    SDL_DestroyTexture(backgroundTexture);
    SDL_FreeSurface(backgroundSurface);

    return playerName;
}