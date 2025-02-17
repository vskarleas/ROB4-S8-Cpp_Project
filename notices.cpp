// #############################################################################
// # File notices.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "notices.hpp"
#include "render.hpp"
#include "macros.hpp"

NoticeMenu::NoticeMenu(SDL_Renderer *_renderer, TTF_Font *font) : 
    texture_menu(nullptr),
    renderer(_renderer),
    police(font),
    notice_displayed(false),
    notice_id(0) //be default we display the first notice
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
    notice_displayed = false;
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


void NoticeMenu::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Color text_color = {0, 0, 0, 0};

    // Add notice text
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    TTF_SetFontSize(police, 14);

    const char* notice_text[20]; // Define a fixed size array
    int text_size = 0; // To keep track of array size

    switch(notice_id) // a great way to add more notices without creatign new files for the same fuctionality
    {
        case 0:
            notice_text[0] = "Welcome to Pong Game!";
            notice_text[1] = "";
            notice_text[2] = "Player 1 Controls:";
            notice_text[3] = "- Use W to move paddle up";
            notice_text[4] = "- Use S to move paddle down";
            notice_text[5] = "";
            notice_text[6] = "Player 2 Controls:";
            notice_text[7] = "- Use UP ARROW to move paddle up";
            notice_text[8] = "- Use DOWN ARROW to move paddle down";
            notice_text[9] = "";
            notice_text[10] = "Other Controls:";
            notice_text[11] = "- Press Pause to see the inner game menu";
            notice_text[12] = "- Click the Save button to save your game in progress";
            text_size = 13;
            break;

        case 1:
            notice_text[0] = "AI Mode Instructions";
            notice_text[1] = "";
            notice_text[2] = "In this mode, you'll play against the computer!";
            notice_text[3] = "";
            notice_text[4] = "Controls:";
            notice_text[5] = "- Use W/S keys to move your paddle";
            notice_text[6] = "- The AI will control the other paddle";
            text_size = 7;
            break;

        case 2:
            notice_text[0] = "Story Mode Instructions";
            notice_text[1] = "";
            notice_text[2] = "Complete challenges to unlock new features!";
            notice_text[3] = "Progress through levels of increasing difficulty";
            notice_text[4] = "";
            notice_text[5] = "Complete 5 levels to win the game!";
            text_size = 6;
            break;

        default:
            notice_text[0] = "Invalid mode selected";
            text_size = 1;
            break;
    }
    

    int y_position = 100;
    for (int i = 0; i < text_size; i++)
    {
        SDL_Rect text_rect = {WINDOW_WIDTH / 4, y_position, 400, 18};
        Utilities::render_button(renderer, police, notice_text[i], text_rect, text_color);
        y_position += 20;
    }

    // Render Let's Go button
    TTF_SetFontSize(police, 24);
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police,"Let's go", button_lets_go, text_color);

    SDL_RenderPresent(renderer);
}