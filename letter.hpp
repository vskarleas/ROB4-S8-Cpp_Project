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
    std::vector<std::string> words = {"Polytech", "Sorbonne", "2025"}; // list of storytime words
    std::vector<char> lettersAtBottom;
    std::string word;
    int current_word_index;
    int current_letter_index;
    char letter;
    float x, y;
    float speed; // Movement speed
    SDL_Texture *texture;
    int width, height;
    SDL_Renderer *renderer;
    TTF_Font *font;

public:
    Letter(int index, float startX, float startY, float velocity, SDL_Renderer *renderer, TTF_Font *font);
    ~Letter();

    void update_letter(float time, int screenHeight, User *player1, User *player2, float ball_pos_x, float ball_pos_y, float ball_radius);
    void render(SDL_Renderer *renderer);
    bool collision_check(float ball_pos_x, float ball_pos_y, float ball_radius) const;
    void next_letter();
    void next_word();
    void reset_word(int n);

    float getX() const { return x; }
    float getY() const { return y; }
};

#endif
