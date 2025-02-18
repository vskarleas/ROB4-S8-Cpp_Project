// #############################################################################
// # File page_4b_1t.hpp
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
    int mode_id;
    bool exit_game;
    /*
    mode = 1 -> AI mode
    mode = 2 -> Two players mode
    mode = 3 -> Storytime mode
    mode = 4 -> Fun mode
    */

    SDL_Texture* texture_menu;
    SDL_Renderer* renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font* police;

    SDL_Rect button_ai_mode;
    SDL_Rect button_two_players_mode;
    SDL_Rect button_storytime_mode;
    SDL_Rect button_fun_mode;
    SDL_Rect button_exit;

public:
    // Constructor and destructor of the mode menu page
    ModeMenu(SDL_Renderer* _renderer, TTF_Font* font);
    ~ModeMenu();

    bool action_handler(const SDL_Event& event);
    void render_object();

    bool get_exit_game() const { return exit_game; }

    // Allows to redirect to correct view using a switch function
    int get_mode_id() const { return mode_id; }
    
};

#endif // MODE_MENU_HPP