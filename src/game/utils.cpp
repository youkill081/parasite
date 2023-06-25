/*
** EPITECH PROJECT, 2023
** ratrapge
** File description:
** some utils for the game manager
*/

#include "game/game_manager.hpp"
#include "macro.hpp"

using namespace game;

struct map* game_manager::get_map(int index)
{
    std::list<struct map *>::iterator curs = this->map_list.begin();
    std::advance(curs, index);
    return *curs;
}

int game_manager::get_number_map(void)
{
    return this->map_list.size();
}

void game_manager::load_party(int map_number)
{
    this->party->load_party(this->get_map(map_number));
    this->point_text->set_text("parasite left: " + std::to_string(this->party->parasite_left));
}

void game_manager::create_player_texture(window::gm_window *window)
{
    this->party->player->texture->create_texture(window);
}

void game_manager::create_text_texture(window::gm_window *window)
{
    this->point_text->create_texture(window);
}

void game::player::draw_player(window::gm_window *window)
{
    if (this->anim_clock->get_elapsed_second() > PLAYER_ANIMATION_WAIT) {
        this->animation_state++;
        if (animation_state > 3)
            animation_state = 0;
        this->texture->set_texture_rect({this->direction * PERSO_TEXTURE_SQUARE, PERSO_TEXTURE_SQUARE * this->animation_state, 21, 21});
        this->anim_clock->restart();
    }
    this->texture->draw(window);
}
