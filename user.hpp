// #############################################################################
// # File user.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun - All rights reserved.
// #############################################################################

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class User
{
public:
    User(const std::string &name = "Player");
    void increment_score();
    void reset_score();
    int get_user_score() const;
    void set_user_score(int _score) { score = _score; };
    const std::string &get_user_name() const; // It is a contstant since once it is set, it doesn't change afterward
    void set_user_name(const std::string &name);

    void set_round(int _round) { round = _round; }
    int get_round() const { return round; }

private:
    std::string name;
    int score;
    int round; // used for story mode, to know how many rounds have been played
};

#endif