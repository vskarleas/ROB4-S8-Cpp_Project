// #############################################################################
// # File triangle_ball.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "triangle_ball.hpp"
#include "renderers.hpp"

#include <algorithm>

// Rendering the white triangle ball
void TriangleBall::render_object(SDL_Renderer* renderer) {
    triangle_renderer()(renderer, pos_x, pos_y, ball_size);
}