// #############################################################################
// # File letter.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors:  Dounia Bakalem, Vasileios Filippos Skarleas, Yanis Sadoun - All rights reserved.
// #############################################################################

#include "letter.hpp"
#include "macros.hpp"

#include <SDL_image.h>
#include <vector>

// Constructeur
Letter::Letter(int index, float startX, float startY, float velocity, SDL_Renderer *renderer, TTF_Font *font)
    : current_word_index(index), current_letter_index(index), x(startX), y(startY), speed(velocity), texture(nullptr),
      width(0), height(0), renderer(renderer), font(font)
{

    word = words[current_word_index];
    next_letter();
}

void Letter::reset_word(int n)
{
    current_letter_index = n;
    current_word_index = n;
}

// Destructeur
Letter::~Letter()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void Letter::next_letter()
{
    // Vérifier s'il y a une lettre suivante
    if (current_letter_index < word.length())
    {
        letter = word[current_letter_index];
        current_letter_index++;

        // Supprimer l'ancienne texture
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        // Créer une nouvelle texture pour la lettre actuelle
        std::string letter_string(1, letter);
        SDL_Surface *surface = TTF_RenderText_Solid(font, letter_string.c_str(), white);

        if (surface)
        {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            width = surface->w;
            height = surface->h;
            SDL_FreeSurface(surface);
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
    // Letters mouvement
    y += speed * deltaTime;

    // Check if letter reaches the limits 
    if (y + height >= screenHeight || y <= 0)
    {
        speed = -speed;
    }

    if (checkCollision(ballX, ballY, ballRadius)) // Check collision with ball
    {

        // Which player should take extra point ?
        if (ballX < x + width / 2)
        {
            player1->increment_score();
        }
        else
        {
            player2->increment_score();
        }
        lettersAtBottom.push_back(letter);


        // Check if it is the last letter of the word
        if (current_letter_index >= word.length())
        {
            lettersAtBottom.clear();
            next_word();
        }
        else
        {
            next_letter();
        }

        // Reset letter position
        y = 0;
        speed = abs(speed);
    }
}

/* Showing thhe letters on the screen afetr they have been touched from the ball */
void Letter::render(SDL_Renderer *renderer)
{
    if (texture)
    {
        SDL_Rect rectangle = {static_cast<int>(x), static_cast<int>(y), width * 3, height * 3};
        SDL_RenderCopy(renderer, texture, nullptr, &rectangle);
    }

    // Posiotining on the bottom of the screen 
    int pos_x = 150;              
    int pos_y = WINDOW_HEIGHT - 100; 
    int spacing = width * 3 + 10;    

    for (size_t i = 0; i < lettersAtBottom.size(); ++i)
    {
        std::string letter_string(1, lettersAtBottom[i]);
        SDL_Surface *surface = TTF_RenderText_Solid(font, letter_string.c_str(), orange);

        if (surface)
        {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect letterRect = {pos_x + static_cast<int>(i) * spacing, pos_y, width * 4, height * 4};
            SDL_RenderCopy(renderer, texture, nullptr, &letterRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
}

void Letter::next_word()
{
    current_word_index = (current_word_index + 1) % words.size(); // Going to the next word
    word = words[current_word_index]; 
    current_letter_index = 0;
    next_letter();                                     
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
