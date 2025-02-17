// #############################################################################
// # File menu.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef MENU_HPP
#define MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <array>
#include <string>
#include <functional>

#include "game_save.hpp"


class Menu {
private:
    // Prininting buttons flags
    bool started;
    bool exit_game;
    bool continue_game; 

    int selected_ball;
    int selected_button;
    bool saved_file_exists;

    // SDL objects for the menu page 
    SDL_Texture* texture_menu;
    SDL_Renderer* renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font* police;

    // Buttons
    SDL_Rect button_start;
    SDL_Rect button_circle_ball;
    SDL_Rect button_square_ball;
    SDL_Rect button_triangle_ball;
    SDL_Rect button_exit;
    SDL_Rect button_continue;

    // Ball type buttons for selection
    SDL_Rect mball_typeButtons[3]; 
    std::array<SDL_Texture*, 3> mball_typeTextures;

    bool in_ball_selection;


    void render_button(const char* text, const SDL_Rect& button, const SDL_Color& color);

    void render_main_menu();
    void render_ball_selection();

public:
    // Constructor and destructor of the menu page
    Menu(SDL_Renderer* _renderer, TTF_Font* font);   
    ~Menu();
    
    bool action_handler(const SDL_Event& event);
    void render_object();

    void reset_selection() { in_ball_selection = false; selected_ball = 0; selected_button = -1; }
    
    // Getters for the private variables of the menu class
    bool get_started() const { return started; }
    int get_selected_ball() const { return selected_ball; }
    bool get_exit_game() const { return exit_game; }
    bool get_saved_file_exists() const { return saved_file_exists; }
 
    bool get_continue_game() const { return continue_game; } 

    // Update the continue button
    void set_saved_file_exists() { saved_file_exists = GameSave::save_exists(); }
};

#endif