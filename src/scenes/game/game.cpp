/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** main file for the game
*/

#include "scenes/game.hpp"
#include "macro.hpp"
#include "clock.hpp"

void set_player_position(window::gm_window *window, game::game_manager *game_manager, SDL_Rect map_draw_position);
void set_virus_position(window::gm_window *window, game::game_manager *game_manager, SDL_Rect map_draw_position);
void update_kb_input(window::gm_window *window, game::game_manager *game_manager);
void move_player(window::gm_window *window, game::game_manager *game_manager);
void move_virus(window::gm_window *window, game::game_manager *game_manager);

namespace gm_scenes {
    SDL_Rect map_draw_position;
    rbb_clock::rbb_clock *update_clock;

    bool init_game_scene(window::gm_window *window, game::game_manager *game_manager)
    {
        update_clock = new rbb_clock::rbb_clock();
        return false;
    }

    void draw_map(window::gm_window *window, game::game_manager *game_manager)
    {
        int square_size = game_manager->party->map->square_size;
        int map_size = game_manager->party->map->size * game_manager->party->map->square_size;
        
        map_draw_position = {(int) window->get_size().x / 2 - map_size / 2, (int) (window->get_size().y / 2 + TITLE_MARGIN) - map_size / 2, map_size, map_size};
        SDL_RenderCopy(window->get_renderer(), game_manager->party->map->map_texture, NULL, &map_draw_position);

        gm_math::gm_vector temp_pos;
        for (int y = 0; y < game_manager->party->map->size; y++) {
            for (int x = 0; x < game_manager->party->map->size; x++) {
                if (game_manager->party->map->map_list[y][x] == game::GM_PARASITE) {
                    temp_pos.y = map_draw_position.y + game_manager->party->map->square_size * x +game_manager->party->parasite->get_size().y / 2;
                    temp_pos.x = map_draw_position.x + game_manager->party->map->square_size * y + game_manager->party->parasite->get_size().x / 2;
                    game_manager->party->parasite->set_position(temp_pos);
                    game_manager->party->parasite->draw(window);
                }
            }
        }
    }

    void draw_virus(window::gm_window *window, game::game_manager *game_manager)
    {
        for (int i = 0; i < 4; i++) {
            game_manager->party->virus_list[i]->image->draw(window);
        }
    }
    
    void draw_perso(window::gm_window *window, game::game_manager *game_manager)
    {
        game_manager->party->player->texture->draw(window);
    }
    
    void update_game(window::gm_window *window, game::game_manager *game_manager)
    {
        update_kb_input(window, game_manager);
        set_player_position(window, game_manager, map_draw_position);
        set_virus_position(window, game_manager, map_draw_position);
        move_player(window, game_manager);
        move_virus(window, game_manager);
        update_clock->restart();
    }
    
    int draw_game_scene(window::gm_window *window, game::game_manager *game_manager)
    {
        draw_map(window, game_manager);

        if (update_clock->get_elapsed_milisecond() > GAME_UPDATE_TIME)
            update_game(window, game_manager);
        draw_perso(window, game_manager);
        draw_virus(window, game_manager);
        game_manager->point_text->draw(window);
        return SCENE_GAME;
    }
}
