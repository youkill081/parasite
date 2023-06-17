/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** main file for the party struct
*/

#include "game/game_manager.hpp"
#include "macro.hpp"

using namespace game;

/*class player {
public:
    SDL_Texture *texture;

    gm_math::gm_vector box;
    gm_math::gm_vector box_position;
    game::direction direction;
};
    
class party {
private:
    struct map *map;
    
    game::player *player = NULL;
public:
    party(void);

    void load_party(struct map *map);
};*/

game::player::player()
{
    this->texture = new rbb_utils::rbb_image(PERSO_TEXTURE, {0, 0, 25, 25}, RBB_IMAGE_RESIZE);
}

game::party::party(void)
{
    this->player = new game::player();
}

void game::party::load_party(struct map *map)
{
    this->map = map;
    
    this->player->box = map->player_spawn;
    this->player->box_position.x = 5;
    this->player->box_position.y = 5;
    this->player->direction = game::direction::NONE;
    this->player->texture->set_size(gm_math::gm_vector(map->square_size - 5, map->square_size - 5));
}
