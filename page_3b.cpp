// #############################################################################
// # File page_3b.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "page_3b.hpp"
#include "renderers.hpp"
#include "macros.hpp"

PauseMenu::PauseMenu(SDL_Renderer *renderer, TTF_Font *font)
    : renderer(renderer), police(font), mResume(false), mSave(false), mExit(false), selected_button(-1), mode_type(-1)
{
    // Center the buttons on screen
    mResumeButton = {300, 200, 200, 50};
    mSaveButton = {300, 280, 200, 50};
    button_exit = {300, 360, 200, 50};
}

PauseMenu::~PauseMenu() {}

void PauseMenu::render_object()
{
    // Semi-transparent background
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    // SDL_Rect fullscreen = {0, 0, 800, 600};
    // SDL_RenderFillRect(renderer, &fullscreen);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw buttons
    SDL_Color normalColor = {0, 0, 0, 0};
    SDL_Color text_color_selected = {0, 255, 255, 255};

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police, "Resume", mResumeButton, selected_button == 0 ? text_color_selected : normalColor);
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);

    if (mode_type == TWO_PLAYERS_MODE)
    {
        Utilities::render_button(renderer, police, "Save", mSaveButton, selected_button == 1 ? text_color_selected : normalColor);
    }
    Utilities::render_button(renderer, police, "Back to menu", button_exit, selected_button == 2 ? text_color_selected : normalColor);

    SDL_RenderPresent(renderer);
}

bool PauseMenu::action_handler(const SDL_Event &event)
{
    // We reinitialise the state of the buttons after each event
    mResume = false;
    mSave = false;
    mExit = false;

    // mode_type = -1;

    if (event.type == SDL_MOUSEMOTION) // for color changes only
    {
        SDL_Point point = {event.motion.x, event.motion.y};
        selected_button = -1;

        if (SDL_PointInRect(&point, &mResumeButton))
            selected_button = 0;
        else if (SDL_PointInRect(&point, &mSaveButton))
            selected_button = 1;
        else if (SDL_PointInRect(&point, &button_exit))
            selected_button = 2;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &mResumeButton))
        {
            mResume = true;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_exit))
        {
            mExit = true;
            return true;
        }

        if (mode_type == TWO_PLAYERS_MODE) // detect this only for two players mode 
        {
            if (SDL_PointInRect(&point, &mSaveButton))
            {
                mSave = true;
                return true;
            }
        }
    }
    return false;
}