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
    class rbb_circle {
    private:
        float radius;
        SDL_Rect rect;
        SDL_Color color;
        SDL_Texture *texture;
    public:
        gm_math::gm_vector get_position();
        float get_radius();
        
        void set_position(gm_math::gm_vector new_position);
        void set_radius(float radius);

        SDL_Rect get_rect();
        
        rbb_circle();
        rbb_circle(int x, int y, int radius, SDL_Color color);

        void create_texture(window::gm_window *window);
        void draw(window::gm_window *to_draw);
    };
}
