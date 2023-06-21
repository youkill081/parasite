/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** to update player movement 
*/

#include "game/game_manager.hpp"
#include "window.hpp"
#include "macro.hpp"

void update_kb_input(window::gm_window *window, game::game_manager *game_manager)
{
    int map_size = game_manager->party->map->size;
    int square_size = game_manager->party->map->square_size;
    
    if (window->event->key_is_pressed_scancode(SDL_SCANCODE_LEFT)) {
        if (game_manager->party->player->box.x > 0 && IS_PATH(game_manager->party->map->map_list[(int) game_manager->party->player->box.x - 1][(int) game_manager->party->player->box.y])) {
            game_manager->party->player->direction = game::direction::LEFT;
            game_manager->party->player->box_position.y = square_size / 2;
        }
    }
    if (window->event->key_is_pressed_scancode(SDL_SCANCODE_RIGHT)) {
        if (game_manager->party->player->box.x < map_size - 1 && IS_PATH(game_manager->party->map->map_list[(int) game_manager->party->player->box.x + 1][(int) game_manager->party->player->box.y])) {
            game_manager->party->player->direction = game::direction::RIGHT;
            game_manager->party->player->box_position.y = square_size / 2;
        }
    }
    if (window->event->key_is_pressed_scancode(SDL_SCANCODE_UP)) {
        if (game_manager->party->player->box.y > 0 && IS_PATH(game_manager->party->map->map_list[(int) game_manager->party->player->box.x][(int) game_manager->party->player->box.y - 1])) {
            game_manager->party->player->direction = game::direction::UP;
            game_manager->party->player->box_position.x= square_size / 2;
        }
    }
    if (window->event->key_is_pressed_scancode(SDL_SCANCODE_DOWN)) {
        if (game_manager->party->player->box.y < map_size - 1 && IS_PATH(game_manager->party->map->map_list[(int) game_manager->party->player->box.x][(int) game_manager->party->player->box.y + 1])) {
            game_manager->party->player->direction = game::direction::DOWN;
            game_manager->party->player->box_position.x = square_size / 2;
        }
    }
}

void set_player_position(window::gm_window *window, game::game_manager *game_manager, SDL_Rect map_draw_position)
{
    gm_math::gm_vector new_pos;
    int square_size = game_manager->party->map->square_size;
    
    switch (game_manager->party->player->direction) {
        case game::direction::NONE:
            new_pos.x = (map_draw_position.x + game_manager->party->player->box.x * square_size) + (square_size / 2 - game_manager->party->player->texture->get_size().x / 2) + 1;
            new_pos.y = (map_draw_position.y + game_manager->party->player->box.y * square_size) + (square_size / 2 - game_manager->party->player->texture->get_size().x / 2) + 1;
            break;
        case game::direction::LEFT:
        case game::direction::RIGHT:
            new_pos.x = (map_draw_position.x + game_manager->party->player->box.x * square_size + game_manager->party->player->box_position.x) - game_manager->party->player->texture->get_size().x / 2;
            new_pos.y = (map_draw_position.y + game_manager->party->player->box.y * square_size) + (square_size / 2 - game_manager->party->player->texture->get_size().x / 2) + 1;
            break;
        case game::direction::DOWN:
        case game::direction::UP:
            new_pos.x = (map_draw_position.x + game_manager->party->player->box.x * square_size) + (square_size / 2 - game_manager->party->player->texture->get_size().x / 2) + 1;
            new_pos.y = (map_draw_position.y + game_manager->party->player->box.y * square_size + game_manager->party->player->box_position.y) - game_manager->party->player->texture->get_size().x / 2;
            break;
        }
        game_manager->party->player->texture->set_position(new_pos);
}

void fix_position(game::game_manager *game_manager, window::gm_window *window)
{
    int square_size = game_manager->party->map->square_size;
    
    if (game_manager->party->player->box_position.x > square_size) {
        game_manager->party->player->box_position.x = (int) game_manager->party->player->box_position.x % square_size;
        if (IS_PATH(game_manager->party->map->map_list[(int) game_manager->party->player->box.x + 1][(int) game_manager->party->player->box.y])) {
            game_manager->party->player->box.x++;
            eat_parasite(game_manager, window);
        }
        else
            game_manager->party->player->direction = game::direction::NONE;
    }
    if (game_manager->party->player->box_position.y > square_size) {
        game_manager->party->player->box_position.y = (int)game_manager->party->player->box_position.y % square_size;
        if (IS_PATH(game_manager->party->map->map_list[(int) game_manager->party->player->box.x][(int) game_manager->party->player->box.y + 1])) {
            game_manager->party->player->box.y++;
            eat_parasite(game_manager, window);
        }
        else
            game_manager->party->player->direction = game::direction::NONE;
    }
    if (game_manager->party->player->box_position.x < 0) {
        game_manager->party->player->box_position.x = square_size - std::abs(game_manager->party->player->box_position.x);
        if (IS_PATH(game_manager->party->map->map_list[(int) game_manager->party->player->box.x - 1][(int) game_manager->party->player->box.y])) {
            game_manager->party->player->box.x--;
            eat_parasite(game_manager, window);
        }
        else
            game_manager->party->player->direction = game::direction::NONE;
    }
    if (game_manager->party->player->box_position.y < 0) {
        game_manager->party->player->box_position.y = square_size - std::abs(game_manager->party->player->box_position.y);
        if (IS_PATH(game_manager->party->map->map_list[(int) game_manager->party->player->box.x][(int) game_manager->party->player->box.y - 1])) {
            game_manager->party->player->box.y--;
            eat_parasite(game_manager, window);
        }
        else
            game_manager->party->player->direction = game::direction::NONE;
    }
}

void move_player(window::gm_window *window, game::game_manager *game_manager)
{
    switch (game_manager->party->player->direction) {
    case game::direction::DOWN:
        game_manager->party->player->box_position.y += PLAYER_SPEED;
        break;
    case game::direction::LEFT:
        game_manager->party->player->box_position.x -= PLAYER_SPEED;
        break;
    case game::direction::RIGHT:
        game_manager->party->player->box_position.x += PLAYER_SPEED;
        break;
    case game::direction::UP:
        game_manager->party->player->box_position.y -= PLAYER_SPEED;
        break;
    case game::direction::NONE:
        break;
    }
    fix_position(game_manager, window);
}
