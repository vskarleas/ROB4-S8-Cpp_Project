// #############################################################################
// # File menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include <string>

#include "menu.hpp"
#include "game_save.hpp"

Menu::Menu(SDL_Renderer *renderer, TTF_Font *font)
    : mRenderer(renderer), mFont(font), mStarted(false), mShouldExit(false), mSelectedBallType(0), mSelectedButton(-1), mStartTexture(nullptr), mHasContinue(GameSave::SaveExists()), mContinueGame(false)
{
    for (auto &texture : mBallTypeTextures)
    {
        texture = nullptr;
    }

    // Adjust vertical positions (moved up by 60 pixels)
    mStartButton = SDL_Rect{300, 100, 200, 50};
    mContinueButton = SDL_Rect{300, 180, 200, 50};
    mClassicButton = SDL_Rect{300, 300, 200, 40};  // Start ball options group
    mSquareButton = SDL_Rect{300, 350, 200, 40};   // Reduced spacing
    mTriangleButton = SDL_Rect{300, 400, 200, 40}; // Reduced spacing
    mExitButton = SDL_Rect{300, 500, 200, 50};     // Keep space before exit

    // Initialize ball type buttons array
    mBallTypeButtons[0] = mClassicButton;
    mBallTypeButtons[1] = mSquareButton;
    mBallTypeButtons[2] = mTriangleButton;
}

void Menu::DrawButton(const char *text, const SDL_Rect &button, const SDL_Color &color)
{
    // Don't draw button background in black theme

    // Render text with Helvetica
    SDL_Surface *textSurface = TTF_RenderText_Solid(mFont, text, color);
    if (textSurface)
    {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
        if (textTexture)
        {
            SDL_Rect textRect = {
                button.x + (button.w - textSurface->w) / 2,
                button.y + (button.h - textSurface->h) / 2,
                textSurface->w,
                textSurface->h};
            SDL_RenderCopy(mRenderer, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

Menu::~Menu()
{
    // Safe cleanup of textures
    if (mStartTexture)
    {
        SDL_DestroyTexture(mStartTexture);
        mStartTexture = nullptr;
    }

    for (auto &texture : mBallTypeTextures)
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
}

bool Menu::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        SDL_Point point = {event.motion.x, event.motion.y};
        mSelectedButton = -1;

        if (SDL_PointInRect(&point, &mStartButton))
            mSelectedButton = 0;
        else if (mHasContinue && SDL_PointInRect(&point, &mContinueButton))
            mSelectedButton = 1;
        else if (SDL_PointInRect(&point, &mClassicButton))
            mSelectedButton = 2;
        else if (SDL_PointInRect(&point, &mSquareButton))
            mSelectedButton = 3;
        else if (SDL_PointInRect(&point, &mTriangleButton))
            mSelectedButton = 4;
        else if (SDL_PointInRect(&point, &mExitButton))
            mSelectedButton = 5;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &mStartButton))
        {
            mStarted = true;
            return true;
        }
        else if (mHasContinue && SDL_PointInRect(&point, &mContinueButton))
        {
            mStarted = true;
            mContinueGame = true;
            return true;
        }
        else if (SDL_PointInRect(&point, &mExitButton))
        {
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
            return true;
        }

        // Ball type selection
        if (SDL_PointInRect(&point, &mClassicButton))
        {
            mSelectedBallType = 0;
            return true;
        }
        else if (SDL_PointInRect(&point, &mSquareButton))
        {
            mSelectedBallType = 1;
            return true;
        }
        else if (SDL_PointInRect(&point, &mTriangleButton))
        {
            mSelectedBallType = 2;
            return true;
        }
    }
    return false;
}

void Menu::Draw()
{
    // Black background
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    // Normal white text
    SDL_Color textColor = {255, 255, 255, 255};
    // Selected cyan text
    SDL_Color selectedColor = {0, 255, 255, 255};

    // Draw Start button in bold
    TTF_SetFontStyle(mFont, TTF_STYLE_BOLD);
    DrawButton("Start New Game", mStartButton,
               mSelectedButton == 0 ? selectedColor : textColor);

    // Reset font style for other buttons
    TTF_SetFontStyle(mFont, TTF_STYLE_NORMAL);

    // Check if save file exists and draw Continue button
    if (GameSave::SaveExists())
    {
        DrawButton("Continue Game", mContinueButton,
                  mSelectedButton == 1 ? selectedColor : textColor);
    }

    // Draw ball type buttons
    DrawButton("- Classic Ball", mClassicButton,
               (mSelectedButton == 2 || mSelectedBallType == 0) ? selectedColor : textColor);
    DrawButton("- Square Ball", mSquareButton,
               (mSelectedButton == 3 || mSelectedBallType == 1) ? selectedColor : textColor);
    DrawButton("- Triangle Ball", mTriangleButton,
               (mSelectedButton == 4 || mSelectedBallType == 2) ? selectedColor : textColor);

    // Draw Exit button in bold
    TTF_SetFontStyle(mFont, TTF_STYLE_BOLD);
    DrawButton("Exit Game", mExitButton,
               mSelectedButton == 5 ? selectedColor : textColor);

    SDL_RenderPresent(mRenderer);
}
