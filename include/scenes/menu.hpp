/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** for the menu scene
*/


#pragma once

#include "window.hpp"

namespace gm_scenes {
    bool init_draw_menu(window::gm_window *window);
    int draw_menu(window::gm_window *window);

    namespace menu {
        namespace control_box{
            bool init_control_box(window::gm_window *window);
            void draw_control_box(window::gm_window *window);
        }

        namespace rule_box {
            bool init_rule_box(window::gm_window *window);
            void draw_rule_box(window::gm_window *window);
        }
    }
}
