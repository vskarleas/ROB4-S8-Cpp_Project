// #############################################################################
// # File square_ball.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "square_ball.hpp"
#include "renderers.hpp"

// Rendering the white square ball
void SquareBall::render_object(SDL_Renderer* renderer) {
    square_renderer()(renderer, pos_x, pos_y, ball_size);
}