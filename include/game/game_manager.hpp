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
#include "utils/text.hpp"
#include "window.hpp"
#include "clock.hpp"

namespace game {
    enum map_entity {
        GM_PATH,
        GM_VOID,
        GM_PARASITE,
        GM_UNKNOWN
    };

    enum direction {
        UP = 3,
        LEFT = 2,
        RIGHT = 1,
        DOWN = 0,
        NONE = 4
    };
    
    struct map {
        bool locked = false;
        int size;

        int square_size;
        
        int **map_list = NULL;
        SDL_Texture *map_texture = NULL;

        gm_math::gm_vector virus_spawn[4];
        gm_math::gm_vector player_spawn;
    };

    class virus {
    public:
        virus();

        bool wait;
        rbb_utils::rbb_image *image;

        gm_math::gm_vector box;
        gm_math::gm_vector box_position;
        game::direction direction;
    };
    
    class player {
    public:
        player();

        bool alive = true;
        
        rbb_utils::rbb_image *texture;

        gm_math::gm_vector box;
        gm_math::gm_vector box_position;
        game::direction direction;
        rbb_clock::rbb_clock *anim_clock;
        int animation_state = 0;
        
        void draw_player(window::gm_window *window);
    };
    
    class party {
    public:
        party(void);

        rbb_utils::rbb_image *parasite;
        virus *virus_list[4];
        
        int  parasite_left;
        
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
        rbb_utils::rbb_text *win_text;
        rbb_utils::rbb_text *lose_text;
        rbb_utils::rbb_text *point_text;
        rbb_utils::rbb_image *padlock;
        
        void load_party(int map_number);
        void display_party(window::gm_window *window);

        void create_player_texture(window::gm_window *window);
        void create_text_texture(window::gm_window *window);
        
        struct map* get_map(int map_index);
            
        int get_number_map(void);
    };
}


#define IS_PATH(map_entity) \
    (map_entity == game::GM_PATH || map_entity == game::GM_PARASITE)

void eat_parasite(game::game_manager *game_manager, window::gm_window *window);
