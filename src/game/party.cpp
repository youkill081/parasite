/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** main file for the party struct
*/

#include "game/game_manager.hpp"
#include "macro.hpp"

using namespace game;

game::player::player(void)
{
    this->texture = new rbb_utils::rbb_image(PERSO_TEXTURE, {0, 0, 25, 25}, RBB_IMAGE_RESIZE);
    this->anim_clock = new rbb_clock::rbb_clock();
}

game::virus::virus(void)
{
    this->image = new rbb_utils::rbb_image(VIRUS_TEXTURE, {0, 0, VIRUS_TEXTURE_SIZE}, RBB_IMAGE_RESIZE);
    this->wait = false;
}

game::party::party(void)
{
    this->player = new game::player();

    this->parasite = new rbb_utils::rbb_image(PARASITE_TEXTURE, {0, 0, PARASITE_TEXTURE_SIZE}, RBB_IMAGE_RESIZE);

    for (int i = 0; i < 4; i++) {
        this->virus_list[i] = new virus;
    }
}

void game::party::load_party(struct map *map)
{
    this->map = map;
    
    this->player->box = map->player_spawn;
    this->player->box_position.x = 5;
    this->player->box_position.y = 5;
    this->player->direction = game::direction::NONE;
    this->player->texture->set_size(gm_math::gm_vector(map->square_size - map->square_size / 10, map->square_size - map->square_size / 10));

    this->parasite->set_size(gm_math::gm_vector(map->square_size / 2, map->square_size - map->square_size / 2));
    this->parasite_left = 0;
    
    for (int i = 0; i < map->size; i++) {
        for (int y = 0; y < map->size; y++) {
            if (IS_PATH(map->map_list[i][y]) && (map->player_spawn.x != i || map->player_spawn.y != y)) {
                map->map_list[i][y] = game::GM_PARASITE;
                parasite_left++;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        this->virus_list[i]->box = map->virus_spawn[i];
        this->virus_list[i]->box_position = gm_math::gm_vector(5, 5);
        this->virus_list[i]->direction = game::direction::NONE;
    }

    this->player->alive = true;
}
