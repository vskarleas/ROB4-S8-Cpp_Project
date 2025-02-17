// #############################################################################
// # File mode_menu.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef MODE_MENU_HPP
#define MODE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <array>

class ModeMenu {
private:
    bool ai_mode;
    bool two_players_mode;
    bool storytime_mode;
    bool fun_mode;

    SDL_Texture* texture_menu;
    SDL_Renderer* renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font* police;

    SDL_Rect button_ai_mode;
    SDL_Rect button_two_players_mode;
    SDL_Rect button_storytime_mode;
    SDL_Rect button_fun_mode;

public:
    // Constructor and destructor of the mode menu page
    ModeMenu(SDL_Renderer* _renderer, TTF_Font* font);
    ~ModeMenu();

    bool action_handler(const SDL_Event& event);
    void render_object();

    // Getters for the private variables of the mode menu class
    bool get_ai_mode() const { return ai_mode; }
    bool get_two_players_mode() const { return two_players_mode; }
    bool get_storytime_mode() const { return storytime_mode; }
    bool get_fun_mode() const { return fun_mode; }
};

#endif // MODE_MENU_HPP