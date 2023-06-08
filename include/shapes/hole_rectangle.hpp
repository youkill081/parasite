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
    class rbb_hole_rectangle {
    private:
        int thickness;
        SDL_Rect rect;
        SDL_Color color;
        SDL_Texture *texture;
    public:
        rbb_hole_rectangle();
        rbb_hole_rectangle(SDL_Rect rect, SDL_Color color, int thickness);

        int get_thickness(void);
        gm_math::gm_vector get_size(void);
        gm_math::gm_vector get_position(void);
        void set_thickness(int new_thickness);
        void set_size(gm_math::gm_vector new_size);
        void set_position(gm_math::gm_vector new_pos);
        SDL_Rect get_rect(void);
        
        void create_texture(window::gm_window *window);
        void draw(window::gm_window *window);
    };
}
