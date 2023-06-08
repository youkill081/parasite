/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <SDL2/SDL.h>

#include "clock.hpp"

namespace rbb_clock {
    rbb_clock::rbb_clock() : start(SDL_GetTicks()) {}

    void rbb_clock::restart(void)
    {
        this->start = SDL_GetTicks();
    }

    float rbb_clock::get_elapsed_milisecond(void)
    {
        return SDL_GetTicks() - this->start;
    }
    
    float rbb_clock::get_elapsed_second(void)
    {
        return this->get_elapsed_milisecond() / 1000;
    }
}
