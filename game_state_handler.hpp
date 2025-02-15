// #############################################################################
// # File game_state_handler.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef GAMESTATE_HANDLER_HPP
#define GAMESTATE_HANDLER_HPP

#include <functional>
#include <type_traits>
#include "game_save.hpp"

template<typename T>
class GameStateHandler {
public:
    // Template method for state validation
    template<typename Validator>
    bool ValidateState(const T& state, Validator validator) {
        static_assert(std::is_invocable_r<bool, Validator, const T&>::value,
            "Validator must be callable with const T& and return bool");
        return validator(state);
    }

    // Lambda storage for state transitions
    void SetStateTransition(std::function<void(T&)> transition) {
        mStateTransition = transition;
    }

    // Function overloading for state updates
    void UpdateState(T& state) {
        if (mStateTransition) mStateTransition(state);
    }

    void UpdateState(T& state, const std::function<void(T&)>& customTransition) {
        customTransition(state);
    }

private:
    std::function<void(T&)> mStateTransition;
};

#endif