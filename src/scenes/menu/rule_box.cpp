/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** for the rule box
*/
#include "scenes/menu.hpp"

#include "shapes/rounded_rectangle.hpp"
#include "utils/image.hpp"
#include "utils/text.hpp"
#include "macro.hpp"
#include "color.h"

namespace gm_scenes{
    namespace menu {
        namespace rule_box{
            SDL_Rect rule_box_view_port = {0, 0, 500, 500};
            rbb_shape::rbb_rounded_rectangle *border = NULL;
            rbb_utils::rbb_text *explication_text;
            rbb_utils::rbb_image *image;

            bool init_rule_box(window::gm_window *window)
            {
                border = new rbb_shape::rbb_rounded_rectangle(rule_box_view_port, COLOR_TRANSPARENT, COLOR_LIGHT_GRAY, 5, 30);
                border->create_texture(window);

                explication_text = new rbb_utils::rbb_text(RULES_TEXT, COLOR_BLACK, DEFAULT_FONT, 30, {10, 10, 490, 490});
                explication_text->create_texture(window);
                
                image = new rbb_utils::rbb_image(RULES_IMAGE, {420, 300, 80, 400}, RBB_IMAGE_RESIZE | RBB_KEEP_PROPORTION);
                image->create_texture(window);
                image->set_position(gm_math::gm_vector((int) explication_text->get_text_area().w / 2 - image->get_texture_size().x / 2, explication_text->get_text_area().h + 30));
                
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
                explication_text->draw(window);
                image->draw(window);
                
                window->reset_viewport();
            }
        }
    }
}
