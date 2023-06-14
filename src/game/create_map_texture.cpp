/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** to create the map textures
*/

#include "game/game_manager.hpp"
#include "macro.hpp"
#include "color.h"

void draw_wall_left(int x, int y, SDL_Surface *surf, Uint32 color, int tex_size)
{
    for (int y2 = GAME_SQUARE_SIZE * y; y2 <= GAME_SQUARE_SIZE * y + GAME_SQUARE_SIZE; y2++) {
        for (int x2 = GAME_SQUARE_SIZE * x; x2 <= GAME_SQUARE_SIZE * x + GAME_WALL_THICKNESS; x2++) {
            ((Uint32*) surf->pixels)[y2 * tex_size + x2] = color;
        }
    }
}

void draw_wall_right(int x, int y, SDL_Surface *surf, Uint32 color, int tex_size)
{
    for (int y2 = GAME_SQUARE_SIZE * y; y2 <= GAME_SQUARE_SIZE * y + GAME_SQUARE_SIZE; y2++) {
        for (int x2 = GAME_SQUARE_SIZE * x + GAME_SQUARE_SIZE - GAME_WALL_THICKNESS; x2 <= GAME_SQUARE_SIZE * x + GAME_SQUARE_SIZE; x2++) {
            ((Uint32*) surf->pixels)[y2 * tex_size + x2] = color;
        }
    }
}

void draw_wall_top(int x, int y, SDL_Surface *surf, Uint32 color, int tex_size)
{
    for (int y2 = GAME_SQUARE_SIZE * y; y2 <= GAME_SQUARE_SIZE * y + GAME_WALL_THICKNESS; y2++) {
        for (int x2 = GAME_SQUARE_SIZE * x; x2 <= GAME_SQUARE_SIZE * x + GAME_SQUARE_SIZE; x2++) {
            ((Uint32*) surf->pixels)[y2 * tex_size + x2] = color;
        }
    }
}

void draw_wall_bottom(int x, int y, SDL_Surface *surf, Uint32 color, int tex_size)
{
    for (int y2 = GAME_SQUARE_SIZE * y + GAME_SQUARE_SIZE - GAME_WALL_THICKNESS; y2 <= GAME_SQUARE_SIZE * y + GAME_SQUARE_SIZE; y2++) {
        for (int x2 = GAME_SQUARE_SIZE * x; x2 <= GAME_SQUARE_SIZE * x + GAME_SQUARE_SIZE; x2++) {
            ((Uint32*) surf->pixels)[y2 * tex_size + x2] = color;
        }
    }
}

void create_texture_square(int x, int y, struct game::map *map, SDL_Surface *surf, Uint32 color_w)
{
    int type = map->map_list[x][y];
    int tex_size = map->size * GAME_SQUARE_SIZE;
    
    if (type == game::GM_PATH)
        return;
    
    if (x > 0 && map->map_list[x - 1][y] == game::GM_PATH)
        draw_wall_left(x, y, surf, color_w, tex_size);
    if (x < map->size - 1 && map->map_list[x + 1][y] == game::GM_PATH)
        draw_wall_right(x, y, surf, color_w, tex_size);
    if (y > 0 && map->map_list[x][y - 1] == game::GM_PATH)
        draw_wall_top(x, y, surf, color_w, tex_size);
    if (y < map->size - 1 && map->map_list[x][y + 1] == game::GM_PATH)
        draw_wall_bottom(x, y, surf, color_w, tex_size);
}

void create_texture_map(struct game::map *map, window::gm_window *window)
{
    int tex_size = map->size * GAME_SQUARE_SIZE;
    
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, tex_size, tex_size, 32, SDL_PIXELFORMAT_RGBA8888);
    
    SDL_PixelFormat *format = surf->format;
    SDL_LockSurface(surf);

    Uint32 color_wall = SDL_MapRGBA(format, COLOR_YELLOW_WB);
    
    for (int x = 0; x < map->size; x++) {
        for (int y = 0; y < map->size; y++) {
            create_texture_square(x, y, map, surf, color_wall);
        }
    }

    SDL_UnlockSurface(surf);
    map->map_texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf);
    SDL_FreeSurface(surf);
}
