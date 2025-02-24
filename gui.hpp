// #############################################################################
// # File gui.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun - All rights reserved.
// #############################################################################

#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class GUI
{
public:
    /**
     * @brief Get the player's name input from the SDL window.
     * 
     * This function handles the SDL events to capture the player's name input
     * from the keyboard. It displays the input text on the screen and updates
     * it in real-time as the player types.
     * 
     * @param renderer The SDL_Renderer used to render the text.
     * @param font The TTF_Font used to render the text.
     * @return std::string The player's name input.
     */
    static std::string getPlayerNameInput(SDL_Renderer* renderer, TTF_Font* font);
};

#endif