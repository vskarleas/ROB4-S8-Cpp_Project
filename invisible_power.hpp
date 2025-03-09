/**
 * @file invisible_power.hpp
 * @brief Header defining the InvisiblePower class for ball visibility effects
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef INVISIBLE_POWER_HPP
#define INVISIBLE_POWER_HPP
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "classic_ball.hpp"
#include <cmath>

/**
 * @class InvisiblePower
 * @brief Power-up that makes the ball temporarily invisible
 *
 * This class implements a special star-shaped power-up that, when collected,
 * makes the ball invisible for a period of time.
 */
class InvisiblePower
{
public:
    /**
     * @brief Constructor for the InvisiblePower class
     * @param screen_width The width of the game screen
     * @param screenHeight The height of the game screen
     */
    InvisiblePower(int screen_width, int screenHeight);

    /**
     * @brief Updates the power's position and the ball's visibility
     * 
     * @param time Time delta since last update
     * @param Ball Pointer to the ball object
     * @param renderer SDL renderer for drawing
     */
    void update(float time, BallBase *Ball, SDL_Renderer *renderer);
    
    /**
     * @brief Renders the power as a star on screen
     * @param renderer SDL renderer for drawing
     */
    void render(SDL_Renderer *renderer);
    
    SDL_Color previousColor; /**< Stores the ball's color before invisibility effect */
    bool is_active;          /**< Whether the power is currently visible and active */
    
    /**
     * @brief Checks for collision between the power and the ball
     * 
     * @param ball Pointer to the ball object
     * @return true if collision detected, false otherwise
     */
    bool check_collision(BallBase *ball) const;

    /**
     * @brief Sets the initialization flag
     * @param init The initialization state to set
     */
    void set_initialisation(bool init) { initialisation = init; }

private:
    float x = 0;                 /**< X position of the power-up */
    float y = 0;                 /**< Y position of the power-up */
    bool play;                   /**< Flag indicating which player is affected */
    int width;                   /**< Width of the power-up */
    int height;                  /**< Height of the power-up */
    float speed;                 /**< Movement speed */
    float invisibility_duration = 0.0f; /**< Time remaining for invisibility effect */
    float repeat;                /**< Timer for power-up respawn */
    bool invisible_ball = false; /**< Whether the ball is currently invisible */
    bool initialisation;         /**< Flag for first-time initialization */
    SDL_Color color;
    float color_change_timer = 0.0f; /**< Timer for color change */
};

#endif
