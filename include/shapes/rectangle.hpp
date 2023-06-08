/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include <SDL2/SDL.h>

#include "window.hpp"
#include "gm_math.hpp"

namespace rbb_shape {
    class rbb_rectangle {
    private:
        SDL_Rect rect;
        SDL_Color draw_color;
    public:
        rbb_rectangle();
        rbb_rectangle(SDL_Rect rect, SDL_Color draw_color);

        gm_math::gm_vector get_size(void);
        gm_math::gm_vector get_position(void);
        void set_size(gm_math::gm_vector new_size);
        void set_position(gm_math::gm_vector new_position);

        SDL_Rect get_rect(void);
        void set_color(SDL_Color new_color);

        void draw(window::gm_window *window);
    };
}
