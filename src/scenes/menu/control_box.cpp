/*
** EPITECH PROJECT, 2023
** ratrapge
** File description:
** for the control box
*/

#include "scenes/menu.hpp"

#include "shapes/rounded_rectangle.hpp"
#include "color.h"

namespace gm_scenes{
    namespace menu {
        namespace control_box{
            SDL_Rect control_box_view_port = {0, 0, 500, 500};
            rbb_shape::rbb_rounded_rectangle *border = NULL;
        
            bool init_control_box(window::gm_window *window)
            {
                border = new rbb_shape::rbb_rounded_rectangle(control_box_view_port, COLOR_TRANSPARENT, COLOR_LIGHT_GRAY, 5, 30);
                border->create_texture(window);
                return false;
            }

            void update_control_box(window::gm_window *window)
            {
                control_box_view_port.x = window->event->mouse_position.x;
                control_box_view_port.y = window->event->mouse_position.y - control_box_view_port.h;
            }
        
            void draw_control_box(window::gm_window *window)
            {
                update_control_box(window);

                window->set_viewport(control_box_view_port);

                border->draw(window);
            
                window->reset_viewport();
            }
        }
    }
}
