// #############################################################################
// # File page_3b_1t.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################
#ifndef MIDDLE_MENU_HPP
#define MIDDLE_MENU_HPP


#include <SDL.h>
#include <SDL_ttf.h>


#include <array>

class MiddleMenu {
private:
    int selected_button;

    int mode_type; // used to universalize this object

    // SDL objects for the middle menu page 
    SDL_Texture* texture_middle_menu;
    SDL_Renderer* renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font* police;

    // Buttons
    SDL_Rect button_1;
    SDL_Rect button_2;
    SDL_Rect button_3;

public:
    // Constructor and destructor of the middle menu page
    MiddleMenu(SDL_Renderer* _renderer, TTF_Font* font);   
    ~MiddleMenu();

    int get_selected_option() const { return selected_button; } // allow to get the selected ball type on other parts of the program
    
    bool action_handler(const SDL_Event& event);
    void render_object();

    int get_mode_type() const { return mode_type; } // allow to get the mode type for decision making on the game's logic
    void set_mode_type(int type) { mode_type = type; } // updatet the game mode type from the outside
};

#endif // MIDDLE_MENU_HPP
