/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include <SDL2/SDL.h>

#include "utils/text.hpp"
#include "shapes/rounded_rectangle.hpp"

namespace rbb_widget {
    class rbb_text_rounded_rectangle {
    private:
        SDL_Rect rect;

        rbb_shape::rbb_rounded_rectangle *rectangle;
        rbb_shape::rbb_rounded_rectangle *rectangle_hover;
        SDL_Color rect_base_color[2];
        SDL_Color rect_hover_color[2];
        
        rbb_utils::rbb_text *text;
        rbb_utils::rbb_text *text_hover;
        SDL_Color text_base_color;
        SDL_Color text_hover_color;

        bool is_hover_v = false;
    public:
        rbb_text_rounded_rectangle();
        rbb_text_rounded_rectangle(SDL_Rect rect,
                                   SDL_Color base_back_color[2],
                                   short thickness,
                                   int distances,
                                   SDL_Color hover_back_color[2],
                                   std::string text,
                                   std::string font_path,
                                   SDL_Color base_text_color,
                                   SDL_Color hover_text_color);

        gm_math::gm_vector get_size(void);
        gm_math::gm_vector get_position(void);
        void set_size(gm_math::gm_vector new_size);
        void set_position(gm_math::gm_vector new_position);

        void set_text(std::string new_text);
        void create_text(window::gm_window *window);
        
        bool is_hover(void);
        void refresh(window::gm_window *window, SDL_Rect *viewport);
        
        void create_element(window::gm_window *window);
        void draw(window::gm_window *window);
    };
}
