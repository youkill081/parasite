/*
** EPITECH PROJECT, 2023
** retrapage
** File description:
** to make parasite work
*/

#include "game/game_manager.hpp"

void eat_parasite(game::game_manager *game_manager, window::gm_window *window)
{
    if (game_manager->party->map->map_list[(int) game_manager->party->player->box.x][(int) game_manager->party->player->box.y] == game::GM_PARASITE) {
        game_manager->party->map->map_list[(int) game_manager->party->player->box.x][(int) game_manager->party->player->box.y] = game::GM_PATH;
        game_manager->party->parasite_left--;
        game_manager->point_text->set_text("parasite left: " + std::to_string(game_manager->party->parasite_left));
        game_manager->point_text->create_texture(window);
    }
}
