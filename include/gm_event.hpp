/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include <string>

#include "gm_math.hpp"

enum {
    RELEASED,
    PRESSED,
    HOLD
};

enum {
    BUTTON_LEFT,
    BUTTON_MIDDLE,
    BUTTON_RIGHT
};

namespace window {
    class gm_window;
    
    namespace event {
        class gm_event {
        private:
            bool keys[500];
            short mouse[3];

            int cursor;
        public:
            bool is_open;
            bool was_resize;
            std::string typed;
            gm_math::gm_vector mouse_position;
            gm_event();
            void refresh(gm_window* window);
            bool key_is_pressed(int key);
            bool button_is_pressed(int button);
            bool button_is_hold(int button);
            bool key_is_pressed_scancode(int key);
            void set_cursor(int new_cursor);
        };
    }
}
