/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** file for the level_choose 
*/

#pragma once

#include "game/game_manager.hpp"

#include "window.hpp"

namespace gm_scenes {
    bool init_level_choose(window::gm_window *window, game::game_manager *game_manager);
    int draw_level_choose(window::gm_window *window, game::game_manager *game_manager);
}
