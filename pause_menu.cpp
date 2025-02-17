// #############################################################################
// # File pause_menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "pause_menu.hpp"

PauseMenu::PauseMenu(SDL_Renderer *renderer, TTF_Font *font)
    : renderer(renderer), police(font), mResume(false), mSave(false), mExit(false), selected_button(-1)
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
    render_button("Resume", mResumeButton, selected_button == 0 ? text_color_selected : normalColor);
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);

    render_button("Save", mSaveButton, selected_button == 1 ? text_color_selected : normalColor);
    render_button("Back to menu", button_exit, selected_button == 2 ? text_color_selected : normalColor);

    SDL_RenderPresent(renderer);
}

bool PauseMenu::action_handler(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION) //for color changes only
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
        else if (SDL_PointInRect(&point, &mSaveButton))
        {
            mSave = true;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_exit))
        {
            mExit = true;
            return true;
        }
    }
    return false;
}

void PauseMenu::render_button(const char *text, const SDL_Rect &button, const SDL_Color &color)
{
    // Draw button background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &button);

    // Render text
    SDL_Surface *text_surface = TTF_RenderText_Solid(police, text, color);
    if (text_surface)
    {
        SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (text_texture)
        {
            SDL_Rect textRect = {
                button.x + (button.w - text_surface->w) / 2,
                button.y + (button.h - text_surface->h) / 2,
                text_surface->w,
                text_surface->h};
            SDL_RenderCopy(renderer, text_texture, nullptr, &textRect);
            SDL_DestroyTexture(text_texture);
        }
        SDL_FreeSurface(text_surface);
    }
}