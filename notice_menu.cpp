// #############################################################################
// # File notice_menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "notice_menu.hpp"
#include "macros.hpp"

NoticeMenu::NoticeMenu(SDL_Renderer *_renderer, TTF_Font *font) : texture_menu(nullptr),
                                                                  renderer(_renderer),
                                                                  police(font)
{
    button_lets_go = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 300, 200, 50};
}

NoticeMenu::~NoticeMenu()
{
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

bool NoticeMenu::action_handler(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &button_lets_go))
        {
            notice_displayed = true;
            return true;
        }
    }

    return false;
}

void NoticeMenu::render_button(const char *text, const SDL_Rect &button, const SDL_Color &color)
{

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

void NoticeMenu::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Color text_color = {0, 0, 0, 0};

    // Add notice text
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    TTF_SetFontSize(police, 14);

    const char *notice_text[] = {
        "Welcome to Pong Game!",
        "",
        "Player 1 Controls:",
        "- Use W to move paddle up",
        "- Use S to move paddle down",
        "",
        "Player 2 Controls:",
        "- Use UP ARROW to move paddle up",
        "- Use DOWN ARROW to move paddle down",
        "",
        "Other Controls:",
        "- Press Pause to see the inner game menu",
        "- Click the Save button to save your game in progress"};

    int y_position = 100;
    for (const auto &line : notice_text)
    {
        SDL_Rect text_rect = {WINDOW_WIDTH / 4, y_position, 400, 18}; // Reduced height
        render_button(line, text_rect, text_color);
        y_position += 20; // Much smaller line spacing
    }

    // Render Let's Go button
    TTF_SetFontSize(police, 24);
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    render_button("Let's go", button_lets_go, text_color);

    SDL_RenderPresent(renderer);
}