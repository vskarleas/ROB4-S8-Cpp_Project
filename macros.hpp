#ifndef MACROS_HPP
#define MACROS_HPP

#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

#define GAME_NAME "The NEW Pong"

#define AI_MODE 1
#define TWO_PLAYERS_MODE 2
#define STORYTIME_MODE 3
#define FUN_MODE 4
#define GAME_SAVED 5

#define BALL_TYPE_SELECTION 2
#define AI_MODE_SELECTION 1

#define AI_MODE_EASY     0
#define AI_MODE_NORMAL   1
#define AI_MODE_HARD     2

const SDL_Color white = {255, 255,255, 255};
const SDL_Color black = {0, 0, 0, 255 };
const SDL_Color yellow = {255, 255, 0, 255};
const SDL_Color orange = {255, 165, 0, 255};
const SDL_Color red = {220, 20, 60, 255};
const SDL_Color green = {34, 139, 34, 255};
const SDL_Color blue = {0, 0, 255, 255};
const SDL_Color purple = {128, 0, 128, 255};

#endif