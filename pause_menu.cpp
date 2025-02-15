// #############################################################################
// # File pause_menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "pause_menu.hpp"

PauseMenu::PauseMenu(SDL_Renderer* renderer, TTF_Font* font)
    : mRenderer(renderer)
    , mFont(font)
    , mResume(false)
    , mSave(false)
    , mExit(false)
    , mSelectedButton(-1)
{
    // Center the buttons on screen
    mResumeButton = {300, 200, 200, 50};
    mSaveButton = {300, 280, 200, 50};
    mExitButton = {300, 360, 200, 50};
}

PauseMenu::~PauseMenu() {}

void PauseMenu::Draw()
{
    // Semi-transparent background
    SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 128);
    SDL_Rect fullscreen = {0, 0, 800, 600};
    SDL_RenderFillRect(mRenderer, &fullscreen);

    // Draw buttons
    SDL_Color normalColor = {255, 255, 255, 255};
    SDL_Color selectedColor = {0, 255, 255, 255};

    DrawButton("Resume", mResumeButton, mSelectedButton == 0 ? selectedColor : normalColor);
    DrawButton("Save", mSaveButton, mSelectedButton == 1 ? selectedColor : normalColor);
    DrawButton("Exit", mExitButton, mSelectedButton == 2 ? selectedColor : normalColor);
}

bool PauseMenu::HandleEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        SDL_Point point = {event.motion.x, event.motion.y};
        mSelectedButton = -1;
        
        if (SDL_PointInRect(&point, &mResumeButton)) mSelectedButton = 0;
        else if (SDL_PointInRect(&point, &mSaveButton)) mSelectedButton = 1;
        else if (SDL_PointInRect(&point, &mExitButton)) mSelectedButton = 2;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};
        
        if (SDL_PointInRect(&point, &mResumeButton))
        {
            mResume = true;
            return true;
        }
        else if (SDL_PointInRect(&point, &mSaveButton))
        {
            mSave = true;
            return true;
        }
        else if (SDL_PointInRect(&point, &mExitButton))
        {
            mExit = true;
            return true;
        }
    }
    return false;
}

void PauseMenu::DrawButton(const char* text, const SDL_Rect& button, const SDL_Color& color)
{
    // Draw button background
    SDL_SetRenderDrawColor(mRenderer, 50, 50, 50, 255);
    SDL_RenderFillRect(mRenderer, &button);
    
    // Render text
    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text, color);
    if (textSurface)
    {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
        if (textTexture)
        {
            SDL_Rect textRect = {
                button.x + (button.w - textSurface->w) / 2,
                button.y + (button.h - textSurface->h) / 2,
                textSurface->w,
                textSurface->h
            };
            SDL_RenderCopy(mRenderer, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}