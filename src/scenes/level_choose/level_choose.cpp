/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** main file for the level choose scene
*/

#include <iostream>

#include "scenes/level_choose.hpp"
#include "game/game_manager.hpp"
#include "clock.hpp"
#include "macro.hpp"

namespace gm_scenes {
    struct game::map* current_choosen_map = NULL;
    int current_choosen_map_index = 0;
    int display_size = 450;
    int title_margin = 50;
    rbb_clock::rbb_clock *wait_button = new rbb_clock::rbb_clock();
    
    bool init_level_choose(window::gm_window *window, game::game_manager *game_manager)
    {
        if (game_manager->get_number_map() <= 0) {
            std::cout << "ERROR: no map loaded -> exit" << std::endl;
            exit(ERROR_CODE);
        }
        current_choosen_map = game_manager->get_map(0);
        return false;
    }

    int get_return_value_lc(window::gm_window *window)
    {
        if (window->event->key_is_pressed_scancode(SDL_SCANCODE_ESCAPE))
            return SCENE_MENU;
        return SCENE_LEVEL_CHOOSE;
    }
    
    void update_level_choose(window::gm_window *window, game::game_manager *game_manager)
    {
        if (wait_button->get_elapsed_second() > 0.2) {
            if (window->event->key_is_pressed_scancode(SDL_SCANCODE_LEFT) && current_choosen_map_index > 0) {
                current_choosen_map_index--;
                current_choosen_map = game_manager->get_map(current_choosen_map_index);
                wait_button->restart();
                display_size = 450;
            }
            if (window->event->key_is_pressed_scancode(SDL_SCANCODE_RIGHT) && current_choosen_map_index < game_manager->get_number_map() - 1) {
                current_choosen_map_index++;
                current_choosen_map = game_manager->get_map(current_choosen_map_index);
                wait_button->restart();
                display_size = 450;
            }
        }
    }
    
    void draw_map(window::gm_window *window)
    {
        SDL_Rect draw_rect = {(int) window->get_size().x / 2 - display_size / 2, (int) (window->get_size().y / 2 + title_margin) - display_size / 2, display_size, display_size};

        if (window->event->mouse_position.x >= draw_rect.x + GAME_SQUARE_SIZE && window->event->mouse_position.x <= draw_rect.x + draw_rect.w - GAME_SQUARE_SIZE &&
            window->event->mouse_position.y >= draw_rect.y + GAME_SQUARE_SIZE && window->event->mouse_position.y <= draw_rect.y + draw_rect.h - GAME_SQUARE_SIZE) {
            if (display_size < 500)
                display_size *= 1.01;
        } else {
            if (display_size > 450)
                display_size /= 1.01;
        }

        SDL_RenderCopy(window->get_renderer(), current_choosen_map->map_texture, NULL, &draw_rect);
    }
    
    int draw_level_choose(window::gm_window *window, game::game_manager *game_manager)
    {
        update_level_choose(window, game_manager);
        draw_map(window);
        return get_return_value_lc(window);
    }
}
