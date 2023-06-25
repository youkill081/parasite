/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** header for the game scene
*/

#pragma once

#include "game/game_manager.hpp"
#include "window.hpp"

namespace gm_scenes {
    bool init_game_scene(window::gm_window *window, game::game_manager *game_manager);
    int draw_game_scene(window::gm_window *window, game::game_manager *game_manager);

    void unlock_next_level(game::game_manager *game_manager);
}
