// #############################################################################
// # File game_over.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include <SDL.h>
#include <SDL_ttf.h>

class game_over {
private:
    SDL_Texture* texture_menu;
    SDL_Renderer* renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font* police;

    SDL_Rect button_back;

    bool go_back; // to go back on the modes menu

    int game_mode; // check the page_4b_1t.hpp for the for the different notice IDs

public:

    // Constructor and destructor of the notice page
    game_over(SDL_Renderer* _renderer, TTF_Font* font);   
    ~game_over();

    bool action_handler(const SDL_Event& event);

    bool get_go_back() const { return go_back; }

    // Required for the game lofgic to update the notices tree and remder the correct text every time
    int get_game_mode() const { return game_mode; }
    void set_game_mode(int _id) { game_mode = _id; }

    void render_object();
};


#endif // NOTICE_MENU_HPP

