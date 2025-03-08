/**
 * @file power.hpp
 * @brief Header defining the Power class for special game effects
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef POWER_HPP
#define POWER_HPP

#include <SDL.h>
#include <cstdlib>
#include <ctime>

#include "paddle.hpp"
#include "macros.hpp"

/**
 * @class Power
 * @brief Class representing power-up items that affect gameplay
 *
 * This class defines powerups that can be collected during gameplay 
 * to modify game elements like paddle size.
 */
class Power
{
public:
    /**
     * @brief Constructor for the Power class
     * @param screen_width The width of the game screen
     * @param screenHeight The height of the game screen
     */
    Power(int screen_width, int screenHeight);

    /**
     * @brief Updates the power's position and effect
     * 
     * Virtual method that updates the game's parameters based on power effects
     * 
     * @param time Time delta since last update
     * @param racket1 Pointer to first paddle
     * @param racket2 Pointer to second paddle
     * @param ball_pos_x Ball's X position
     * @param ball_pos_y Ball's Y position
     * @param ball_radius Ball's radius
     * @param renderer SDL renderer for drawing
     */
    virtual void update(float time, Paddle *racket1, Paddle *racket2, float ball_pos_x, float ball_pos_y, float ball_radius, SDL_Renderer *renderer);
    
    /**
     * @brief Renders the power on screen
     * @param renderer SDL renderer for drawing
     */
    virtual void render(SDL_Renderer *renderer);

    /**
     * @brief Checks if the ball has hit this power-up
     * 
     * @param ball_pos_x Ball's X position
     * @param ball_pos_y Ball's Y position
     * @param ball_radius Ball's radius
     * @return true if collision detected, false otherwise
     */
    bool collision_check(float ball_pos_x, float ball_pos_y, float ball_radius) const;
    
    /**
     * @brief Resets the power-up to a new random position
     * @param screen_width The width of the game screen
     */
    virtual void reset(int screen_width);

    bool is_active; /**< Used to determine if the power is currently visible and active */

protected:
    float x = 0;                  /**< X position of the power-up */
    float y = 0;                  /**< Y position of the power-up */
    bool play;                    /**< Flag to determine which player gets the effect */
    int width, height;            /**< Dimensions of the power-up */
    float speed;                  /**< Movement speed */
    float duration_effect = 0.0f; /**< Time remaining until effect ends */
    bool effect_is_active = false;/**< Whether the power's effect is currently active */
    SDL_Color color;              /**< Color of the power-up */
};

#endif
