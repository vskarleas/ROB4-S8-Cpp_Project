// #############################################################################
// # File sound_effects.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef SOUND_EFFECTS_HPP
#define SOUND_EFFECTS_HPP

#include <SDL_mixer.h>

class SoundEffects
{
public:
    /**
     * @brief Changes background music with fade effect
     *
     * @param music_file The new music track to play
     * @param fade_out_duration Duration of fade out in milliseconds
     * @param fade_in_duration Duration of fade in in milliseconds
     * @param volume Volume level (0-128)
     */
    static void change_music_track(Mix_Music *music_file,
                                 int fade_out_duration = 500,
                                 int fade_in_duration = 500,
                                 int volume = MIX_MAX_VOLUME / 3);
};

#endif