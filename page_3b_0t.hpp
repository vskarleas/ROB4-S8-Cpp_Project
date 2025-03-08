// #############################################################################
// # File page_3b_0t.hpp
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
#include <SDL_mixer.h>

#include "game_save.hpp"

class page_3b_0t
{
private:
    // Prininting buttons flags
    bool start_new_game;
    bool exit_mode;
    bool continue_game;

    bool saved_file_exists;

    // SDL objects for the menu page
    SDL_Texture *texture_menu;
    SDL_Renderer *renderer; // Responsible for placing the objects on the SDL screen
    TTF_Font *police;

    // Buttons
    SDL_Rect button_start;
    SDL_Rect button_exit;
    SDL_Rect button_continue;

public:
    // Constructor and destructor of the menu page
    page_3b_0t(SDL_Renderer *_renderer, TTF_Font *font);
    ~page_3b_0t();

    bool action_handler(const SDL_Event &event);
    void render_object(int mode, const std::string &highscore_name, int highscore);

    // Getters for the private variables of the menu class
    bool get_started() const { return start_new_game; }
    bool get_exit_mode() const { return exit_mode; }
    bool get_saved_file_exists() const { return saved_file_exists; }
    bool get_continue_game() const { return continue_game; }

    // Update the continue button
    void set_saved_file_exists() { saved_file_exists = Saving::save_exists(); }
};

#endif