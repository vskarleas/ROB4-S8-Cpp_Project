// #############################################################################
// # File paddle.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: EYanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef PADDLE_HPP
#define PADDLE_HPP
#include <SDL.h>

class Paddle
{
public:
    // Constructor
    Paddle(int x, bool on_the_left_side);

    // Methods
    void Update(float travel_time);
    void Draw(SDL_Renderer *renderer);
    SDL_Rect GetRect() const;

    // Giving access to the private variables [getters]
    bool get_is_left() const { return is_left; }
    float get_pos_x() const { return pos_x; }
    float get_pos_y() const { return pos_y; }
    float get_racket_speed() const { return racket_speed; }
    float get_racket_height() const { return racket_height; }
    float get_racket_width() const { return racket_width; }

    // Updating the private variables [setters]
    void set_pos_x(float x) { pos_x = x; }
    void set_pos_y(float y) { pos_y = y; }
    

private:
    float pos_y;
    float pos_x;
    const float racket_height;     
    const float racket_width;    
    const float racket_speed; 
    bool is_left;
};
#endif