// #############################################################################
// # File menu.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef MENU_HPP
#define MENU_HPP

#include "game_save.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <array>

class Menu {
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font);   
    ~Menu();
    
    bool HandleEvent(const SDL_Event& event);
    void Draw();
    
    bool HasStarted() const { return mStarted; }
    int GetSelectedBallType() const { return mSelectedBallType; }
    bool ShouldExit() const { return mShouldExit; }

    bool HasContinue() const { return mHasContinue; }

    bool IsStarted() const { return mStarted; } 
    bool IsContinueGame() const { return mContinueGame; } 

    void UpdateContinueButton() { mHasContinue = GameSave::SaveExists(); }

private:
    void DrawButton(const char* text, const SDL_Rect& button, const SDL_Color& color);

    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    bool mStarted;
    bool mShouldExit;
    int mSelectedBallType;
    int mSelectedButton;

    std::array<SDL_Texture*, 3> mBallTypeTextures;

    SDL_Texture* mStartTexture;
    SDL_Rect mStartButton;
    SDL_Rect mClassicButton;
    SDL_Rect mSquareButton;
    SDL_Rect mTriangleButton;
    SDL_Rect mExitButton;
    SDL_Rect mBallTypeButtons[3]; 

    SDL_Rect mContinueButton;
    bool mHasContinue;

    bool mContinueGame; 
};

#endif