/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <SDL2/SDL.h>

#include "shapes/gradient_square.hpp"
#include "scenes/level_choose.hpp"
#include "game/game_manager.hpp"
#include "scenes/menu.hpp"
#include "utils/text.hpp"
#include "window.hpp"
#include "macro.hpp"
#include "color.h"

rbb_utils::rbb_text *create_title(window::gm_window *window)
{
    rbb_utils::rbb_text *title_text = new rbb_utils::rbb_text("Parasite", COLOR_LIGHT_RED, DEFAULT_FONT, 150, {0, 0, 1000, 1000});
    title_text->create_texture(window);
    SDL_Rect text_area = title_text->get_text_area();
    title_text->set_position(gm_math::gm_vector(window->get_size().x / 2 - text_area.w / 2, 50));
    return title_text;
}

rbb_utils::rbb_text *create_credit(window::gm_window *window)
{
    rbb_utils::rbb_text *credit_text = new rbb_utils::rbb_text("Created by Julien SERIN", COLOR_BLACK, DEFAULT_FONT, 25, {0, 0, 1000, 100});
    credit_text->create_texture(window);
    SDL_Rect text_area = credit_text->get_text_area();
    credit_text->set_position(gm_math::gm_vector(window->get_size().x - text_area.w - 5, window->get_size().y - text_area.h - 5));
    return credit_text;
}

void display_background(rbb_shape::rbb_gradient_square *square, window::gm_window *window)
{
    int size_x;
    int size_y;
    
    if (window->event->was_resize) {
        SDL_GetWindowSize(window->window, &size_x, &size_y);
        square->set_size(gm_math::gm_vector(size_x, size_y));
    }
    square->draw_square(window);
}

int start_game_loop(window::gm_window *window, game::game_manager *game_manager)
{
    int scene = SCENE_MENU;
    rbb_shape::rbb_gradient_square *background = new rbb_shape::rbb_gradient_square(0, 0, window->get_size().x, window->get_size().y, {230, 230, 230, 255}, {190, 190, 190, 255});
    rbb_utils::rbb_text *title_text = create_title(window);
    rbb_utils::rbb_text *credit_text = create_credit(window);
    background->create_texture(window);
    
    while (window->is_open) {
        window->refresh_event();
        window->reset_window();
        display_background(background, window);
        title_text->draw(window);
        credit_text->draw(window);

        switch (scene) {
        case SCENE_MENU:
            scene = gm_scenes::draw_menu(window);
            break;
        case SCENE_LEVEL_CHOOSE:
            scene = gm_scenes::draw_level_choose(window, game_manager);
            break;
        }

        window->refresh_window();
    }
    return 0;
}
