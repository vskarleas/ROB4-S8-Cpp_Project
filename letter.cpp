// #############################################################################
// # File letter.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors:  Dounia Bakalem, Vasileios Filippos Skarleas, Yanis Sadoun - All rights reserved.
// #############################################################################

#include "letter.hpp"
#include <SDL_image.h>
#include <vector>

// Constructeur
Letter::Letter(float startX, float startY, float velocity, SDL_Renderer *renderer, TTF_Font *font)
    : currentWordIndex(0), currentLetterIndex(0), x(startX), y(startY), speed(velocity), texture(nullptr),
      width(0), height(0), renderer(renderer), font(font)
{
    word = words[currentWordIndex];
    changeToNextLetter();
}

// Destructeur
Letter::~Letter()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void Letter::changeToNextLetter()
{
    // Vérifier s'il y a une lettre suivante
    if (currentLetterIndex < word.length())
    {
        letter = word[currentLetterIndex];
        currentLetterIndex++;

        // Supprimer l'ancienne texture
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        // Créer une nouvelle texture pour la lettre actuelle
        std::string letterStr(1, letter);
        SDL_Color color = {255, 255, 255, 255}; // Blanc
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, letterStr.c_str(), color);

        if (textSurface)
        {
            texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            width = textSurface->w;
            height = textSurface->h;
            SDL_FreeSurface(textSurface);
        }
        else
        {
            SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        }
    }
}

void Letter::update_letter(float deltaTime, int screenHeight, User *player1, User *player2,
                           float ballX, float ballY, float ballRadius)
{
    // Move the letter
    y += speed * deltaTime;

    // Check if letter hits screen boundaries
    if (y + height >= screenHeight || y <= 0)
    {
        speed = -speed; // Reverse direction
    }

    // Check collision with ball
    if (checkCollision(ballX, ballY, ballRadius))
    {
        // Determine which player scores based on ball position
        if (ballX < x + width / 2)
        {
            player1->increment_score();
        }
        else
        {
            player2->increment_score();
        }

        // Check if it was the last letter of the word
        if (currentLetterIndex >= word.length())
        {
            setNextWord();
        }
        else
        {
            changeToNextLetter();
        }

        // Reset letter position
        y = 0;
        speed = abs(speed);
    }
}

// Afficher la lettre à l'écran
void Letter::render(SDL_Renderer *renderer)
{
    if (texture)
    {
        SDL_Rect destRect = {static_cast<int>(x), static_cast<int>(y), width * 3, height * 3};
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    }
}

void Letter::setNextWord()
{
    currentWordIndex = (currentWordIndex + 1) % words.size(); // Passer au mot suivant
    word = words[currentWordIndex];                           // Charger le nouveau mot
    currentLetterIndex = 0;                                   // Réinitialiser l'index des lettres
    changeToNextLetter();                                     // Charger la première lettre du mot
}

// Vérifier la collision avec la balle
bool Letter::checkCollision(float ballX, float ballY, float ballRadius) const
{
    // Vérifier si le centre de la balle est dans la zone de la lettre
    float closestX = (ballX < x) ? x : (ballX > x + width * 3) ? x + width * 3
                                                               : ballX;
    float closestY = (ballY < y) ? y : (ballY > y + height * 3) ? y + height * 3
                                                                : ballY;

    float distanceX = ballX - closestX;
    float distanceY = ballY - closestY;

    return (distanceX * distanceX + distanceY * distanceY) < (ballRadius * ballRadius);
}
