/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** main file for the level choose scene
*/

#include <iostream>

#include "scenes/level_choose.hpp"
#include "game/game_manager.hpp"
#include "shapes/triangle.hpp"
#include "clock.hpp"
#include "macro.hpp"
#include "color.h"

namespace gm_scenes {
    struct game::map* current_choosen_map = NULL;
    int current_choosen_map_index = 0;
    int display_size = 450;
    rbb_clock::rbb_clock *wait_button = new rbb_clock::rbb_clock();
    rbb_shape::rbb_triangle *left_arrow = NULL;
    rbb_shape::rbb_triangle *left_arrow_disable = NULL;
    rbb_shape::rbb_triangle *right_arrow = NULL;
    rbb_shape::rbb_triangle *right_arrow_disable = NULL;
    
    bool init_level_choose(window::gm_window *window, game::game_manager *game_manager)
    {
        if (game_manager->get_number_map() <= 0) {
            std::cout << "ERROR: no map loaded -> exit" << std::endl;
            exit(ERROR_CODE);
        }
        current_choosen_map = game_manager->get_map(0);

        left_arrow = new rbb_shape::rbb_triangle({100, (int) window->get_size().y / 2 + TITLE_MARGIN - 130 / 2, 130, 100}, COLOR_YELLOW, COLOR_BLACK, 90);
        left_arrow_disable = new rbb_shape::rbb_triangle({100, (int) window->get_size().y / 2 + TITLE_MARGIN - 130 / 2, 130, 100}, COLOR_GRAY, COLOR_GRAY, 90);
        left_arrow->create_texture(window);
        left_arrow_disable->create_texture(window);
        
        right_arrow = new rbb_shape::rbb_triangle({840, (int) window->get_size().y / 2 + TITLE_MARGIN - 130 / 2, 130, 100}, COLOR_YELLOW, COLOR_BLACK, 90);
        right_arrow_disable = new rbb_shape::rbb_triangle({840, (int) window->get_size().y / 2 + TITLE_MARGIN - 130 / 2, 130, 100}, COLOR_GRAY, COLOR_GRAY, 90);
        right_arrow->create_texture(window);
        right_arrow_disable->create_texture(window);
        
        return false;
    }

    void unlock_next_level(game::game_manager *game_manager)
    {
        if (current_choosen_map_index < game_manager->get_number_map() - 1) {
            game_manager->get_map(current_choosen_map_index + 1)->locked = false;
        } else {
            printf("you have unlocked all level !\n");
        }
    }
    
    int get_return_value_lc(window::gm_window *window, game::game_manager *game_manager)
    {
        if (window->event->key_is_pressed_scancode(SDL_SCANCODE_ESCAPE))
            return SCENE_MENU;
        if (window->event->key_is_pressed(SDLK_KP_ENTER) || window->event->key_is_pressed(SDLK_RETURN)) {
            if (ENABLE_LOCKING == false || not current_choosen_map->locked) {
                game_manager->load_party(current_choosen_map_index);
                game_manager->create_text_texture(window);
                return SCENE_GAME;
            }
        }
        return SCENE_LEVEL_CHOOSE;
    }
    
    void update_level_choose(window::gm_window *window, game::game_manager *game_manager)
    {
        if (wait_button->get_elapsed_second() > 0.2) {
            if ((window->event->key_is_pressed_scancode(SDL_SCANCODE_LEFT) || (left_arrow->is_hover() && window->event->button_is_pressed(BUTTON_LEFT)))
                && current_choosen_map_index > 0) {
                current_choosen_map_index--;
                current_choosen_map = game_manager->get_map(current_choosen_map_index);
                wait_button->restart();
                display_size = 450;
            }
            if ((window->event->key_is_pressed_scancode(SDL_SCANCODE_RIGHT) || (right_arrow->is_hover() && window->event->button_is_pressed(BUTTON_LEFT)))
                && current_choosen_map_index < game_manager->get_number_map() - 1) {

                current_choosen_map_index++;
                current_choosen_map = game_manager->get_map(current_choosen_map_index);
                wait_button->restart();
                display_size = 450;
            }
        }

        left_arrow->update(window, NULL);
        right_arrow->update(window, NULL);
    }
    
    void draw_map_level_choose(window::gm_window *window, game::game_manager *game_manager)
    {
        static SDL_Rect draw_rect = {(int) window->get_size().x / 2 - display_size / 2, (int) (window->get_size().y / 2 + TITLE_MARGIN) - display_size / 2, display_size, display_size};
        game_manager->padlock->set_position(gm_math::gm_vector(
                                                draw_rect.x + draw_rect.w / 2 - game_manager->padlock->get_texture_size().x / 2,
                                                draw_rect.y + draw_rect.h / 2 - game_manager->padlock->get_texture_size().y / 2));
        
        if (window->event->mouse_position.x >= draw_rect.x + GAME_SQUARE_SIZE && window->event->mouse_position.x <= draw_rect.x + draw_rect.w - GAME_SQUARE_SIZE &&
            window->event->mouse_position.y >= draw_rect.y + GAME_SQUARE_SIZE && window->event->mouse_position.y <= draw_rect.y + draw_rect.h - GAME_SQUARE_SIZE) {
            if (display_size < 500)
                display_size *= 1.01;
        } else {
            if (display_size > 450)
                display_size /= 1.01;
        }

        SDL_RenderCopy(window->get_renderer(), current_choosen_map->map_texture, NULL, &draw_rect);

        if (current_choosen_map->locked) {
            game_manager->padlock->draw(window);
        }
    }
    
    int draw_level_choose(window::gm_window *window, game::game_manager *game_manager)
    {
        update_level_choose(window, game_manager);
        draw_map_level_choose(window, game_manager);

        if (current_choosen_map_index > 0)
            left_arrow->draw(window);
        else
            left_arrow_disable->draw(window);
        
        if (current_choosen_map_index < game_manager->get_number_map() - 1)
            right_arrow->draw(window, SDL_FLIP_VERTICAL);
        else
            right_arrow_disable->draw(window, SDL_FLIP_VERTICAL);
        
        return get_return_value_lc(window, game_manager);
    }
}
