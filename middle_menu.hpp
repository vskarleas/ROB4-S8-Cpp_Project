// #############################################################################
// # File middle_menu.hpp
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
    int selected_ball;
    int selected_button;

    // SDL objects for the middle menu page 
    SDL_Texture* texture_middle_menu;
    SDL_Renderer* renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font* police;

    // Buttons
    SDL_Rect button_circle_ball;
    SDL_Rect button_square_ball;
    SDL_Rect button_triangle_ball;

    void render_button(const char* text, const SDL_Rect& button, const SDL_Color& color);

public:
    // Constructor and destructor of the middle menu page
    MiddleMenu(SDL_Renderer* _renderer, TTF_Font* font);   
    ~MiddleMenu();

    int get_selected_ball() const { return selected_ball; } // allow to get the selected ball type on other parts of the program
    
    bool action_handler(const SDL_Event& event);
    void render_object();
};

#endif // MIDDLE_MENU_HPP
