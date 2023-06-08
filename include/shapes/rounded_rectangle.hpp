/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include <SDL2/SDL.h>

#include "window.hpp"

namespace rbb_shape {
    class rbb_rounded_rectangle {
    private:
        SDL_Rect rect;

        SDL_Color exterior_color;
        SDL_Color interior_color;
        short thickness;
        int distance;
        
        SDL_Texture *texture = NULL;
    public:
        rbb_rounded_rectangle();
        rbb_rounded_rectangle(SDL_Rect rect, SDL_Color interior_color, SDL_Color exterior_color, short thickness, int distance);

        gm_math::gm_vector get_size(void);
        gm_math::gm_vector get_position(void);
        void set_size(gm_math::gm_vector new_size);
        void set_position(gm_math::gm_vector new_position);
        
        void create_texture(window::gm_window *window);
        void draw(window::gm_window *window);
    };
}
