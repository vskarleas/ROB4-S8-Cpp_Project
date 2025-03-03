// #############################################################################
// # File user.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun - All rights reserved.
// #############################################################################

#include "user.hpp"

User::User(const std::string &name) : name(name), score(0), round(0) {}

void User::increment_score()
{
    score++;
}

void User::reset_score()
{
    score = 0;
}

int User::get_user_score() const
{
    return score;
}

const std::string &User::get_user_name() const
{
    return name;
}

void User::set_user_name(const std::string &newName)
{
    name = newName;
}