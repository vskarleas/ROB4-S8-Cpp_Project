// #############################################################################
// # File game_over.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "game_over.hpp"
#include "renderers.hpp"
#include "macros.hpp"

game_over::game_over(SDL_Renderer *_renderer, TTF_Font *font) : 
    texture_menu(nullptr),
    renderer(_renderer),
    police(font),
    go_back(false) //be default we don't go back on the modes menu
{
    const int button_width = 200;
    const int button_height = 50;
    const int base_y = WINDOW_WIDTH - 400;
    const int center_x = WINDOW_HEIGHT / 2;

    // "Go back" button above "Let's go" button
    button_back = SDL_Rect{center_x, base_y, button_width, button_height};
}

game_over::~game_over()
{
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

bool game_over::action_handler(const SDL_Event &event)
{
    go_back = false; // Reset the flag for going back on the choose menu

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &button_back))
        {
            go_back = true;
            return true;
        }
    }

    return false;
}


void game_over::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Add notice text
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    TTF_SetFontSize(police, 14);

    const char* notice_text[20]; // Define a fixed size array
    int text_size = 0; // To keep track of array size

    notice_text[0] = "Game is over !";
    notice_text[1] = "";
    std::string winner = "Winner: " + winner_name + "!";
    notice_text[2] = winner.c_str();
    notice_text[3] = "Feel free to go back to the new menu ";
    text_size = 4;
    

    int y_position = 100;
    for (int i = 0; i < text_size; i++)
    {
        SDL_Rect text_rect = {WINDOW_WIDTH / 4, y_position, 400, 18};
        Utilities::render_button(renderer, police, notice_text[i], text_rect, black);
        y_position += 20;
    }

    // Render Let's Go button
    TTF_SetFontSize(police, 24);
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police,"Back to menu", button_back, black);


    SDL_RenderPresent(renderer);
}

void game_over::set_winner(const std::string& name) {
    winner_name = name;
}