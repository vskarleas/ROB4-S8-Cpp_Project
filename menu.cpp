// #############################################################################
// # File menu.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include <string>

#include "menu.hpp"
#include "game_save.hpp"
#include "macros.hpp"

Menu::Menu(SDL_Renderer *_renderer, TTF_Font *font): 
    /* Follwoing the order in the class declaration*/
    started(false), 
    exit_game(false), 
    continue_game(false),
    selected_ball(0),
    selected_button(-1),
    saved_file_exists(GameSave::save_exists()), // calls the save_exists() function to check if a game state file exists

    texture_menu(nullptr), 
    renderer(_renderer), 
    police(font)
{
    for (auto &texture : mball_typeTextures)
    {
        texture = nullptr; // all button tectures set to NILL (nullptr) for initialisation
    }

    // Buttons positioning on the menu page
    button_start = SDL_Rect{WINDOW_HEIGHT/2, 100, 200, 50};
    button_continue = SDL_Rect{WINDOW_HEIGHT/2, 180, 200, 50};
    button_circle_ball = SDL_Rect{WINDOW_HEIGHT/2, WINDOW_WIDTH - 500, 200, 40}; // The tree following buttons willbe closer to each other
    button_square_ball = SDL_Rect{WINDOW_HEIGHT/2, WINDOW_WIDTH - 450, 200, 40};   
    button_triangle_ball = SDL_Rect{WINDOW_HEIGHT/2, WINDOW_WIDTH - 400, 200, 40}; 
    button_exit = SDL_Rect{WINDOW_HEIGHT/2, WINDOW_WIDTH - 300, 200, 50}; // Keep space before exit

    // Initialize ball type buttons array for the selection
    mball_typeButtons[0] = button_circle_ball;
    mball_typeButtons[1] = button_square_ball;
    mball_typeButtons[2] = button_triangle_ball;
}


/* Rendering an SDL rectangle which plays the role of a button */
void Menu::render_button(const char *text, const SDL_Rect &button, const SDL_Color &color)
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

Menu::~Menu()
{
    // Deallocate menu texture
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }

    // all removing all the ball textures (array) from the memory
    for (auto &texture : mball_typeTextures)
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
}

bool Menu::action_handler(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION) // tracking the mouse mouvement
    {
        SDL_Point point = {event.motion.x, event.motion.y};
        selected_button = -1;

        // Check if the mouse is over a button. Button's specifications can be found on the menu costractor above
        if (SDL_PointInRect(&point, &button_start))
            selected_button = 0;
        else if (saved_file_exists && SDL_PointInRect(&point, &button_continue))
            selected_button = 1;
        else if (SDL_PointInRect(&point, &button_circle_ball))
            selected_button = 2;
        else if (SDL_PointInRect(&point, &button_square_ball))
            selected_button = 3;
        else if (SDL_PointInRect(&point, &button_triangle_ball))
            selected_button = 4;
        else if (SDL_PointInRect(&point, &button_exit))
            selected_button = 5;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) // if the mause is clicked
    {
        SDL_Point point = {event.button.x, event.button.y};

        // updating the game flags for its state
        if (SDL_PointInRect(&point, &button_start))
        {
            started = true;
            return true;
        }
        else if (saved_file_exists && SDL_PointInRect(&point, &button_continue))
        {
            started = true;
            continue_game = true;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_exit))
        {
            exit_game = true;
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
            return true;
        }

        // Ball type selection rollover
        if (SDL_PointInRect(&point, &button_circle_ball))
        {
            selected_ball = 0;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_square_ball))
        {
            selected_ball = 1;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_triangle_ball))
        {
            selected_ball = 2;
            return true;
        }
    }
    return false;
}

void Menu::render_object()
{
    // Black background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Normal white text
    SDL_Color text_color = {0, 0, 0, 0};
    // Selected cyan text
    SDL_Color text_color_selected = {100, 180, 190, 220};

    // Draw Start button in bold
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    render_button("Start New Game", button_start,
               selected_button == 0 ? text_color_selected : text_color);

    // reset font style for other buttons
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);

    // Check if save file exists and draw Continue button
    if (GameSave::save_exists())
    {
        render_button("Continue Game", button_continue,
                  selected_button == 1 ? text_color_selected : text_color);
    }

    // Draw ball type buttons
    render_button("- Classic Ball", button_circle_ball,
               (selected_button == 2 || selected_ball == 0) ? text_color_selected : text_color);
    render_button("- Square Ball", button_square_ball,
               (selected_button == 3 || selected_ball == 1) ? text_color_selected : text_color);
    render_button("- Triangle Ball", button_triangle_ball,
               (selected_button == 4 || selected_ball == 2) ? text_color_selected : text_color);

    // Draw Exit button in bold
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    render_button("Exit Game", button_exit,
               selected_button == 5 ? text_color_selected : text_color);

    SDL_RenderPresent(renderer);
}
