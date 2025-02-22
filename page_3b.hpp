// #############################################################################
// # File page_3b.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h> 

class page_3b {
public:
    page_3b(SDL_Renderer* renderer, TTF_Font* font);
    ~page_3b();
    
    void render_object();
    bool action_handler(const SDL_Event& event);
    bool ShouldResume() const { return mResume; }
    bool ShouldSave() const { return mSave; }
    bool get_exit_mode() const { return mExit; }

    void set_mode_type(int type) { mode_type = type; } // update the mode type from the outside
    int get_mode_type() const { return mode_type; } // allow to get the mode type for decision making on the game's logic

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

    int mode_type; // used to differetiate the rendering objects and content
};

#endif