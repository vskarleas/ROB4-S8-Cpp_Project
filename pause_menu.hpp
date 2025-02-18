// #############################################################################
// # File pause_menu.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>

class PauseMenu {
public:
    PauseMenu(SDL_Renderer* renderer, TTF_Font* font);
    ~PauseMenu();
    
    void render_object();
    bool action_handler(const SDL_Event& event);
    bool ShouldResume() const { return mResume; }
    bool ShouldSave() const { return mSave; }
    bool get_exit_mode() const { return mExit; }

private:
    SDL_Renderer* renderer;
    TTF_Font* police;
    bool mResume;
    bool mSave;
    bool mExit;
    int selected_button;

    SDL_Rect mResumeButton;
    SDL_Rect mSaveButton;
    SDL_Rect button_exit;
};

#endif