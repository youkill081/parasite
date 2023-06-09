/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** the cpp file for the menu
*/

#include <iostream>

#include "widget/text_rounded_rectangle.hpp"
#include "scenes/menu.hpp"
#include "window.hpp"
#include "macro.hpp"
#include "color.h"

namespace gm_scenes {
    rbb_widget::rbb_text_rounded_rectangle *start_button = NULL;
    rbb_widget::rbb_text_rounded_rectangle *rule_button = NULL;
    rbb_widget::rbb_text_rounded_rectangle *control_button = NULL;
    rbb_utils::rbb_text *credit_text = NULL;
    
    bool init_draw_menu(window::gm_window *window)
    {
        SDL_Color buttons_base_colors[2] = {COLOR_LIGHT_RED, {255, 102, 102, 200}};
        SDL_Color buttons_hover_colors[2] = {{255, 70, 70, 255}, {255, 70, 70, 200}};

        short default_button_height = 400;
        
        start_button = new rbb_widget::rbb_text_rounded_rectangle(
            {(int) window->get_size().x / 2 - 200, default_button_height, 400, 100},
            buttons_base_colors,
            4,
            50,
            buttons_hover_colors,
            "Play",
            DEFAULT_FONT,
            COLOR_BLACK,
            COLOR_BLACK);

        rule_button = new rbb_widget::rbb_text_rounded_rectangle(
            {(int) window->get_size().x / 2 - 200, default_button_height + 150, 400, 100},
            buttons_base_colors,
            4,
            50,
            buttons_hover_colors,
            "Rule",
            DEFAULT_FONT,
            COLOR_BLACK,
            COLOR_BLACK);

        control_button = new rbb_widget::rbb_text_rounded_rectangle(
            {(int) window->get_size().x / 2 - 200, default_button_height + 300, 400, 100},
            buttons_base_colors,
            4,
            50,
            buttons_hover_colors,
            "Controls",
            DEFAULT_FONT,
            COLOR_BLACK,
            COLOR_BLACK);

        start_button->create_element(window);
        rule_button->create_element(window);
        control_button->create_element(window);

        credit_text = new rbb_utils::rbb_text("Created by Julien SERIN", COLOR_BLACK, DEFAULT_FONT, 25, {0, 0, 1000, 100});
        credit_text->create_texture(window);
        SDL_Rect text_area = credit_text->get_text_area();
        credit_text->set_position(gm_math::gm_vector(window->get_size().x - text_area.w - 5, window->get_size().y - text_area.h - 5));
        
        return false;
    }

    void update_menu(window::gm_window *window)
    {
        start_button->refresh(window, NULL);
        rule_button->refresh(window, NULL);
        control_button->refresh(window, NULL);
    }
    
    int draw_menu(window::gm_window *window)
    {
        update_menu(window);

        start_button->draw(window);
        rule_button->draw(window);
        control_button->draw(window);

        credit_text->draw(window);
        
        return 0;
    }
}
