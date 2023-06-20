/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** contain evrything for the virus movement
*/

#include "game/game_manager.hpp"
#include "window.hpp"
#include "macro.hpp"

void set_virus_position(window::gm_window *window, game::game_manager *game_manager, SDL_Rect map_draw_position)
{
    gm_math::gm_vector new_pos;
    int square_size = game_manager->party->map->square_size;
    game::virus *temp;
    
    for (int i = 0; i < 4; i++) {
        temp = game_manager->party->virus_list[i];
        switch (game_manager->party->virus_list[i]->direction) {
        case game::direction::NONE:
            new_pos.x = (map_draw_position.x + temp->box.x * square_size) + (square_size / 2 - temp->image->get_size().x / 2) + 1;
            new_pos.y = (map_draw_position.y + temp->box.y * square_size) + (square_size / 2 - temp->image->get_size().x / 2) + 1;
            break;
        case game::direction::LEFT:
        case game::direction::RIGHT:
            new_pos.x = (map_draw_position.x + temp->box.x * square_size + temp->box_position.x) - temp->image->get_size().x / 2;
            new_pos.y = (map_draw_position.y + temp->box.y * square_size) + (square_size / 2 - temp->image->get_size().x / 2) + 1;
            break;
        case game::direction::DOWN:
        case game::direction::UP:
            new_pos.x = (map_draw_position.x + temp->box.x * square_size) + (square_size / 2 - temp->image->get_size().x / 2) + 1;
            new_pos.y = (map_draw_position.y + temp->box.y * square_size + temp->box_position.y) - temp->image->get_size().x / 2;
            break;
        }
        temp->image->set_position(new_pos);
    }
}

int branch_number(bool possible_direction[4])
{
    int end = 0;
    for (int i = 0; i < 4; i++) {
        if (possible_direction[i])
            end++;
    }
    return end;
}

game::direction get_random_direction(bool possible_direction[4])
{
    int dir = -1;
    do {
        dir = rand() % 4;
    } while (not possible_direction[dir]);

    switch (dir) {
    case 0:
        return game::LEFT;
    case 1:
        return game::UP;
    case 2:
        return game::RIGHT;
    case 3:
        return game::DOWN;
    }
    return game::NONE;
}

void make_virus_ia(game::game_manager *game_manager, game::virus *virus)
{
    bool possible_direction[4] = {false, false, false, false};

    if (IS_PATH(game_manager->party->map->map_list[(int) virus->box.x - 1][(int) virus->box.y]))
        possible_direction[0] = true;
    if (IS_PATH(game_manager->party->map->map_list[(int) virus->box.x][(int) virus->box.y - 1]))
        possible_direction[1] = true;
    if (IS_PATH(game_manager->party->map->map_list[(int) virus->box.x + 1][(int) virus->box.y]))
        possible_direction[2] = true;
    if (IS_PATH(game_manager->party->map->map_list[(int) virus->box.x][(int) virus->box.y + 1]))
        possible_direction[3] = true;
    if (virus->direction == game::NONE || (branch_number(possible_direction) > 2 && not virus->wait)) {
        virus->direction = get_random_direction(possible_direction);
        virus->wait = true;
    }
}


void fix_position_virus(game::game_manager *game_manager, game::virus *virus)
{
    int square_size = game_manager->party->map->square_size;
    
    if (virus->box_position.x > square_size) {
        virus->box_position.x = (int) virus->box_position.x % square_size;
        if (IS_PATH(game_manager->party->map->map_list[(int) virus->box.x + 1][(int) virus->box.y]))
            virus->box.x++;
        else
            virus->direction = game::direction::NONE;
        virus->wait = false;
    }
    if (virus->box_position.y > square_size) {
        virus->box_position.y = (int) virus->box_position.y % square_size;
        if (IS_PATH(game_manager->party->map->map_list[(int) virus->box.x][(int) virus->box.y + 1]))
            virus->box.y++;
        else
            virus->direction = game::direction::NONE;
        virus->wait = false;
    }
    if (virus->box_position.x < 0) {
        virus->box_position.x = square_size - std::abs(virus->box_position.x);
        if (IS_PATH(game_manager->party->map->map_list[(int) virus->box.x - 1][(int) virus->box.y]))
            virus->box.x--;
        else
            virus->direction = game::direction::NONE;
        virus->wait = false;
    }
    if (virus->box_position.y < 0) {
        virus->box_position.y = square_size - std::abs(virus->box_position.y);
        if (IS_PATH(game_manager->party->map->map_list[(int) virus->box.x][(int) virus->box.y - 1]))
            virus->box.y--;
        else
            virus->direction = game::direction::NONE;
        virus->wait = false;
    }
}


void move_virus(window::gm_window *window, game::game_manager *game_manager)
{
    game::virus *temp;

    for (int i = 0; i < 4; i++) {
        temp = game_manager->party->virus_list[i];
        make_virus_ia(game_manager, temp);
        switch (temp->direction) {
        case game::direction::DOWN:
            temp->box_position.y += VIRUS_SPEED;
            break;
        case game::direction::LEFT:
            temp->box_position.x -= VIRUS_SPEED;
            break;
        case game::direction::RIGHT:
            temp->box_position.x += VIRUS_SPEED;
            break;
        case game::direction::UP:
            temp->box_position.y -= VIRUS_SPEED;
            break;
        case game::direction::NONE:
            break;
        }
        fix_position_virus(game_manager, game_manager->party->virus_list[i]);
    }
}

