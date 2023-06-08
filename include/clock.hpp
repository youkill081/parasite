/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include <SDL2/SDL.h>

namespace rbb_clock {
    class rbb_clock {
    private:
        Uint32 start;
    public:
        float get_elapsed_second(void);
        float get_elapsed_milisecond(void);
        void restart(void);
        rbb_clock();
    };
}
