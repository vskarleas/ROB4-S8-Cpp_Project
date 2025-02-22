#include "setup.hpp"
#include "renderers.hpp"
#include "macros.hpp"

#include <SDL_ttf.h>

Setup::Setup(SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), 
      font(font), 
      player1Name("Player 1"),
      player2Name("Player 2"),
      isPlayer1Active(true),
      completed(false)
{
    player1Input = {200, 200, 400, 50};
    player2Input = {200, 300, 400, 50};
    submitButton = {350, 400, 100, 50};
}

Setup::~Setup() {}

void Setup::render_object() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color activeColor = {255, 255, 0, 255};

    // Title
    TTF_SetFontSize(font, 32);
    Utilities::render_button(renderer, font, "Setup Players", 
        {WINDOW_WIDTH/2 - 100, 50, 200, 50}, textColor);

    // Player 1 input
    TTF_SetFontSize(font, 24);
    SDL_Color p1Color = isPlayer1Active ? activeColor : textColor;
    Utilities::render_button(renderer, font, "Player 1:", 
        {50, player1Input.y, 130, 50}, textColor);
    Utilities::render_button(renderer, font, player1Name.c_str(), 
        player1Input, p1Color);

    // Player 2 input
    SDL_Color p2Color = !isPlayer1Active ? activeColor : textColor;
    Utilities::render_button(renderer, font, "Player 2:", 
        {50, player2Input.y, 130, 50}, textColor);
    Utilities::render_button(renderer, font, player2Name.c_str(), 
        player2Input, p2Color);

    // Submit button
    Utilities::render_button(renderer, font, "Start", 
        submitButton, textColor);

    SDL_RenderPresent(renderer);
}

bool Setup::action_handler(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;

        if (x >= player1Input.x && x <= player1Input.x + player1Input.w &&
            y >= player1Input.y && y <= player1Input.y + player1Input.h) {
            isPlayer1Active = true;
            return true;
        }

        if (x >= player2Input.x && x <= player2Input.x + player2Input.w &&
            y >= player2Input.y && y <= player2Input.y + player2Input.h) {
            isPlayer1Active = false;
            return true;
        }

        if (x >= submitButton.x && x <= submitButton.x + submitButton.w &&
            y >= submitButton.y && y <= submitButton.y + submitButton.h) {
            completed = true;
            return true;
        }
    }
    else if (event.type == SDL_TEXTINPUT) {
        if (isPlayer1Active && player1Name.length() < 15) {
            player1Name += event.text.text;
        }
        else if (!isPlayer1Active && player2Name.length() < 15) {
            player2Name += event.text.text;
        }
        return true;
    }
    else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            if (isPlayer1Active && !player1Name.empty()) {
                player1Name.pop_back();
            }
            else if (!isPlayer1Active && !player2Name.empty()) {
                player2Name.pop_back();
            }
            return true;
        }
        else if (event.key.keysym.sym == SDLK_TAB) {
            isPlayer1Active = !isPlayer1Active;
            return true;
        }
    }
    return false;
}