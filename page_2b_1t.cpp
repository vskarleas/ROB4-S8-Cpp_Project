// #############################################################################
// # File page_2b_1t.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "page_2b_1t.hpp"
#include "renderers.hpp"
#include "macros.hpp"

page_2b_1t::page_2b_1t(SDL_Renderer *_renderer, TTF_Font *font) : 
    texture_menu(nullptr),
    renderer(_renderer),
    police(font),
    next_view(false),
    go_back(false), //be default we don't go back on the modes menu
    notice_id(-1) //be default we display the general notice
{
    const int button_width = 200;
    const int button_height = 50;
    const int base_y = WINDOW_WIDTH - 400;
    const int center_x = WINDOW_HEIGHT / 2;

    // "Go back" button above "Let's go" button
    button_back = SDL_Rect{center_x, base_y, button_width, button_height};
    button_lets_go = SDL_Rect{center_x, base_y + 70, button_width, button_height};
}

page_2b_1t::~page_2b_1t()
{
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

bool page_2b_1t::action_handler(const SDL_Event &event)
{
    next_view = false;

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &button_lets_go))
        {
            next_view = true;
            return true;
        }

        if (SDL_PointInRect(&point, &button_back))
        {
            go_back = true;
            return true;
        }
    }

    return false;
}


void page_2b_1t::render_object()
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
        case TWO_PLAYERS_MODE:
            notice_text[0] = "Default Pong Game instructions";
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

        case AI_MODE:
            notice_text[0] = "AI Mode Instructions";
            notice_text[1] = "";
            notice_text[2] = "In this mode, you'll play against the computer!";
            notice_text[3] = "";
            notice_text[4] = "Controls:";
            notice_text[5] = "- Use W/S keys to move your paddle";
            notice_text[6] = "- The AI will control the other paddle";
            text_size = 7;
            break;

        case STORYTIME_MODE:
            notice_text[0] = "Story Mode Instructions";
            notice_text[1] = "";
            notice_text[2] = "Complete challenges to unlock new features!";
            notice_text[3] = "Progress through levels of increasing difficulty";
            notice_text[4] = "";
            notice_text[5] = "Complete 5 levels to win the game!";
            text_size = 6;
            break;

        case FUN_MODE:
            notice_text[0] = "Fun Mode Instructions";
            notice_text[1] = "";
            notice_text[2] = "In this mode, you'll play against the computer!";
            notice_text[3] = "The ball will change its shape randomly!";
            notice_text[4] = "";
            notice_text[5] = "Controls:";
            notice_text[6] = "- Use W/S keys to move your paddle";
            notice_text[7] = "- The AI will control the other paddle";
            text_size = 8;
            break;
        case GAME_SAVED:
            notice_text[0] = "Game has been saved! succesfully !";
            notice_text[1] = "";
            notice_text[2] = "Please note that you can Continue the game only when you are on the Classic Pong Game mode";
            text_size = 3;
            break;

        case -1:
            notice_text[0] = "Welcome to the Pong Game!";
            notice_text[1] = "";
            notice_text[2] = "This game was developed using the SDL library and OOP principles.";
            notice_text[3] = "It was developed with inheritance, polymorphisms, lamda functions and functors in mind.";
            notice_text[4] = "";
            notice_text[5] = "There are four game modes available. Each mode has its own set of instructions for you to discover.";
            notice_text[6] = "";
            notice_text[7] = "Let's go and select a mode to start playing!";
            text_size = 8;
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
    Utilities::render_button(renderer, police,"Alright", button_lets_go, text_color);

    // if (!(notice_id != -1 || notice_id == GAME_SAVED)) // hide the go back button if we are in the game saved notice
    // {
    //     TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    //     Utilities::render_button(renderer, police,"Go back", button_back, text_color);
    // }

    if (notice_id != -1 && notice_id != GAME_SAVED) // show the go back button only if we are not in the general notice
    {
        TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
        Utilities::render_button(renderer, police,"Go back", button_back, text_color);
    }

    SDL_RenderPresent(renderer);
}