/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

#include "gm_math.hpp"
#include "window.hpp"

namespace rbb_utils {
    class rbb_text {
    private:
        SDL_Rect rect;
        SDL_Rect draw_rect;
        SDL_Rect cut_rect;
        TTF_Font *font;
        SDL_Color color;
        std::string text;
        std::string font_path;
        int font_size;
        SDL_Texture *texture;
    public:
        rbb_text();
        rbb_text(std::string text, SDL_Color color, std::string font_path, int font_size, SDL_Rect rect);

        void set_text(std::string text);
        std::string get_text(void);

        void create_texture(window::gm_window *window);
        
        SDL_Color get_color(void);
        void set_color(SDL_Color);

        gm_math::gm_vector get_size(void);
        gm_math::gm_vector get_position(void);
        void set_size(gm_math::gm_vector);
        void set_position(gm_math::gm_vector);

        void set_font_size(int new_size);
        int  get_font_size(void);
        TTF_Font *get_font(void);
        bool recreate_font();

        void recalc_position(void);
        SDL_Rect get_text_area(void);
        
        void draw(window::gm_window *window);
    };
}
