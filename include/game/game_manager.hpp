/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** game manager include file
*/

#pragma once

#include "SDL2/SDL.h"

#include <list>

#include "utils/image.hpp"
#include "window.hpp"

namespace game {
    enum map_entity {
        GM_PATH,
        GM_VOID,
        GM_PARASITE,
        GM_UNKNOWN
    };

    enum direction {
        UP,
        LEFT,
        RIGHT,
        DOWN,
        NONE
    };
    
    struct map {
        bool locked = false;
        int size;

        int square_size;
        
        int **map_list = NULL;
        SDL_Texture *map_texture = NULL;

        gm_math::gm_vector player_spawn;
    };

    class player {
    public:
        player();
        
        rbb_utils::rbb_image *texture;

        gm_math::gm_vector box;
        gm_math::gm_vector box_position;
        game::direction direction;
    };
    
    class party {
    public:
        party(void);

        rbb_utils::rbb_image *parasite;
        
        struct map *map;
        game::player *player = NULL;
        void load_party(struct map *map);
    };
    
    class game_manager {
    private:
        int number_map;

        std::list<struct map *> map_list;
    public:
        game_manager();
        game_manager(window::gm_window *window);

        game::party *party = NULL;
        
        void load_party(int map_number);
        void display_party(window::gm_window *window);

        void create_player_texture(window::gm_window *window);
        
        struct map* get_map(int map_index);
            
        int get_number_map(void);
    };
}


#define IS_PATH(map_entity) \
    (map_entity == game::GM_PATH || map_entity == game::GM_PARASITE)
