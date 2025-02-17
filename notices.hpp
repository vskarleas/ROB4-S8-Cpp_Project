// #############################################################################
// # File notices.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef NOTICE_MENU_HPP
#define NOTICE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>

class NoticeMenu {
private:
    SDL_Texture* texture_menu;
    SDL_Renderer* renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font* police;

    SDL_Rect button_lets_go;
    SDL_Rect button_back;

    bool notice_displayed;
    bool go_back; // to go back on the modes menu

    int notice_id; // check the mode_menu.hpp for the for the different notice IDs

public:

    // Constructor and destructor of the menu page
    NoticeMenu(SDL_Renderer* _renderer, TTF_Font* font);   
    ~NoticeMenu();

    bool action_handler(const SDL_Event& event);

    bool get_notice_displayed() const { return notice_displayed; }

    // Required for the game lofgic to update the notices tree and remder the correct text every time
    int get_notice_id() const { return notice_id; }
    void set_notice_id(int _id) { notice_id = _id; }

    void render_object();
};


#endif // NOTICE_MENU_HPP

