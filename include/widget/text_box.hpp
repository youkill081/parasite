/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include "clock.hpp"
#include "window.hpp"
#include "gm_math.hpp"
#include "utils/text.hpp"
#include "shapes/rectangle.hpp"
#include "shapes/hole_rectangle.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#define CURSOR_TIME 0.48

enum {
    BOX_CENTERED = 1,
    BOX_MULTIPLE_LINE = 2
};

enum rbb_text_box_state {
    RBB_TEXT_BOX_STATE_ENABLE,
    RBB_TEXT_BOX_STATE_DISABLE
};

namespace rbb_widget {
    class rbb_text_box {
    private:
        SDL_Rect rect;
        SDL_Rect one_letter_rect;
        SDL_Color border_color;
        SDL_Color interior_color;
        SDL_Color disable_color = {100, 100, 100, 255};
        SDL_Color over_color;
        int border_thickness;
        short state = RBB_TEXT_BOX_STATE_ENABLE;
        
        int font_size;
        SDL_Color font_color;
        std::string font_path;
        std::string type_text = "";

        bool cursor_display = true;
        int cursor_position = 0;
        rbb_shape::rbb_rectangle *cursor;
        rbb_clock::rbb_clock *cursor_clock;
        
        bool selected = false;
        bool was_selected_var = false;
        
        rbb_shape::rbb_hole_rectangle *border_rectangle;
        rbb_shape::rbb_rectangle *interior_rectangle;
        rbb_utils::rbb_text *text;
    public:
        rbb_text_box();
        rbb_text_box(SDL_Rect rect, int border_thickness, SDL_Color interior_color, SDL_Color over_color, SDL_Color border_color, std::string font_path, int font_size, SDL_Color font_color);
        void init_components(window::gm_window *window);
        
        gm_math::gm_vector get_size(void);
        gm_math::gm_vector get_position(void);
        void set_size(gm_math::gm_vector new_size);
        void set_position(gm_math::gm_vector new_position);

        int get_boder_thickness(void);
        void set_border_thickess(int new_thicknes);
        void set_interior_color(SDL_Color color);
        void set_border_color(SDL_Color color);

        void set_font_path(std::string new_path);
        void set_font_size(int new_size);
        void set_font_color(SDL_Color font_color);
        void create_font(window::gm_window window);

        bool is_selected(void);
        bool was_selected(void);
        void set_selected(bool new_selection);

        std::string get_text(void);
        void clear_text(window::gm_window *window);

        void set_state(rbb_text_box_state);
        
        void update(window::gm_window *window, SDL_Rect *view_port);
        void draw(window::gm_window *window);
    };
}
