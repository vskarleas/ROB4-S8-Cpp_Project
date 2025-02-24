// #############################################################################
// # File sound_effects.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Vasileios Filippos Skarleas, Yanis Sadoun, Dounia Bakalem - All rights reserved.
// #############################################################################

#include "sound_effects.hpp"
#include <SDL.h>

void SoundEffects::change_music_track(Mix_Music* music_file, 
                                   int fade_out_duration,
                                   int fade_in_duration,
                                   int volume) {
    Mix_FadeOutMusic(fade_out_duration);
    // SDL_Delay(5);
    Mix_FadeInMusic(music_file, -1, fade_in_duration);
    Mix_VolumeMusic(volume);
}