/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** for the rule box
*/
#include "scenes/menu.hpp"

#include "shapes/rounded_rectangle.hpp"
#include "color.h"

namespace gm_scenes{
    namespace menu {
        namespace rule_box{
            SDL_Rect rule_box_view_port = {0, 0, 500, 500};
            rbb_shape::rbb_rounded_rectangle *border = NULL;
        
            bool init_rule_box(window::gm_window *window)
            {
                border = new rbb_shape::rbb_rounded_rectangle(rule_box_view_port, COLOR_TRANSPARENT, COLOR_LIGHT_GRAY, 5, 30);
                border->create_texture(window);
                return false;
            }

            void update_rule_box(window::gm_window *window)
            {
                rule_box_view_port.x = window->event->mouse_position.x;
                rule_box_view_port.y = window->event->mouse_position.y - rule_box_view_port.h;
            }
        
            void draw_rule_box(window::gm_window *window)
            {
                update_rule_box(window);

                window->set_viewport(rule_box_view_port);

                border->draw(window);
            
                window->reset_viewport();
            }
        }
    }
}
