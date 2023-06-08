/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include <SDL2/SDL.h>

#include "gm_math.hpp"
#include "window.hpp"

namespace rbb_shape {
    class rbb_gradient_square {
    private:
        SDL_Rect rect;
        SDL_Color to;
        SDL_Color from;
        SDL_Texture *texture;
    public:
        gm_math::gm_vector *get_position();
        gm_math::gm_vector *get_size();
        
        void set_position(gm_math::gm_vector new_position);
        void set_size(gm_math::gm_vector new_size);

        SDL_Rect get_rect();
        
        rbb_gradient_square();
        rbb_gradient_square(float x, float y, float width, float height, SDL_Color from, SDL_Color to);

        void create_texture(window::gm_window *window);
        void draw_square(window::gm_window *window);
    };
}
