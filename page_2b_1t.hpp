// #############################################################################
// # File page_2b_1t.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef NOTICE_MENU_HPP
#define NOTICE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h> 

class page_2b_1t {
private:
    SDL_Texture* texture_menu;
    SDL_Renderer* renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font* police;

    SDL_Rect button_lets_go;
    SDL_Rect button_back;

    bool next_view;
    bool go_back; // to go back on the modes menu

    int notice_id; // check the page_4b_1t.hpp for the for the different notice IDs

public:

    // Constructor and destructor of the notice page
    page_2b_1t(SDL_Renderer* _renderer, TTF_Font* font);   
    ~page_2b_1t();

    bool action_handler(const SDL_Event& event);

    bool get_next_view() const { return next_view; }
    bool get_go_back() const { return go_back; }

    // Required for the game lofgic to update the notices tree and remder the correct text every time
    int get_notice_id() const { return notice_id; }
    void set_notice_id(int _id) { notice_id = _id; }

    void render_object();
};


#endif // NOTICE_MENU_HPP

