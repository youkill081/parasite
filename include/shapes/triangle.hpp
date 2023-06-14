/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** include for the triangle shape
*/

#pragma once

#include <SDL2/SDL.h>

#include "gm_math.hpp"
#include "window.hpp"

namespace rbb_shape {
    class rbb_triangle {
    private:
        SDL_Rect rect;
        SDL_Color color;
        SDL_Color hover_color;
        
        SDL_Texture *texture;
        SDL_Texture *hover_texture;
        int angle;

        bool hover = false;
    public:
        rbb_triangle();
        rbb_triangle(SDL_Rect rect, SDL_Color draw_color, SDL_Color hover_color, int angle);

        void create_texture(window::gm_window *window);
        
        gm_math::gm_vector get_size(void);
        gm_math::gm_vector get_position(void);
        void set_size(gm_math::gm_vector new_size);
        void set_position(gm_math::gm_vector new_position);
        
        SDL_Rect get_rect(void);
        void set_color(SDL_Color new_color);

        void update(window::gm_window *window, SDL_Rect *view_port);
        bool is_hover(void);
        
        void draw(window::gm_window *window);
        void draw(window::gm_window *window, SDL_RendererFlip flags);
    };
}
