#ifndef SETUP_HPP
#define SETUP_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "user.hpp"

class Setup {
public:
    Setup(SDL_Renderer* renderer, TTF_Font* font);
    ~Setup();
    void render_object();
    bool action_handler(SDL_Event& event);
    const std::string& getPlayer1Name() const { return player1Name; }
    const std::string& getPlayer2Name() const { return player2Name; }
    bool isCompleted() const { return completed; }

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string player1Name;
    std::string player2Name;
    bool isPlayer1Active;
    bool completed;
    SDL_Rect player1Input;
    SDL_Rect player2Input;
    SDL_Rect submitButton;
};

#endif