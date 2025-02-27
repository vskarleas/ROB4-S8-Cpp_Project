// #############################################################################
// # File game.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun - All rights reserved.
// #############################################################################

#ifndef LETTER_HPP
#define LETTER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

#include "user.hpp"
#include "macros.hpp"

class Letter
{
private:
    std::vector<std::string> words = {"yanis", "dounia", "vasilis"}; // list of storytime words
    std::vector<char> lettersAtBottom;
    std::string word;
    int currentWordIndex;
    int currentLetterIndex;
    char letter;
    float x, y;
    float speed; // Movement speed
    SDL_Texture *texture;
    int width, height;
    SDL_Renderer *renderer;
    TTF_Font *font;

public:
    Letter(int index,float startX, float startY, float velocity, SDL_Renderer *renderer, TTF_Font *font);
    ~Letter();

    void update_letter(float deltaTime, int screenHeight, User* player1, User* player2, float ballX, float ballY, float ballRadius);
    void render(SDL_Renderer *renderer);
    bool checkCollision(float ballX, float ballY, float ballRadius) const;
    void changeToNextLetter();
    void setNextWord();
    void reset_word(int n);

    float getX() const { return x; }
    float getY() const { return y; }
};

#endif
