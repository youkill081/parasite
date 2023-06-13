/*
** EPITECH PROJECT, 2023
** ratrapge
** File description:
** some utils for the game manager
*/

#include "game/game_manager.hpp"

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
