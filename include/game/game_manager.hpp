/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** game manager include file
*/

#pragma once

#include "SDL2/SDL.h"

#include <list>

#include "window.hpp"

namespace game {
    enum map_entity {
        GM_PATH,
        GM_VOID,
        GM_PARASITE,
        GM_PERSO,
        GM_UNKNOWN
    };

    struct map {
        bool locked = false;
        int size;
        
        int **map_list = NULL;
        SDL_Texture *map_texture = NULL;
    };
    
    class game_manager {
    private:
        int number_map;

        std::list<struct map *> map_list;
    public:
        game_manager();
        game_manager(window::gm_window *window);
        
        void load_map(int map_number);
        void display_map(window::gm_window *window);

        struct map* get_map(int map_index);
        int get_number_map(void);
    };
}
