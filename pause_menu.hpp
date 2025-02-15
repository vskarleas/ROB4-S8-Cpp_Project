// #############################################################################
// # File pause_menu.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>

class PauseMenu {
public:
    PauseMenu(SDL_Renderer* renderer, TTF_Font* font);
    ~PauseMenu();
    
    void Draw();
    bool HandleEvent(const SDL_Event& event);
    bool ShouldResume() const { return mResume; }
    bool ShouldSave() const { return mSave; }
    bool ShouldExit() const { return mExit; }

private:
    void DrawButton(const char* text, const SDL_Rect& button, const SDL_Color& color);

    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    bool mResume;
    bool mSave;
    bool mExit;
    int mSelectedButton;

    SDL_Rect mResumeButton;
    SDL_Rect mSaveButton;
    SDL_Rect mExitButton;
};

#endif