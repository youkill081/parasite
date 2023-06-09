/*
** EPITECH PROJECT, 2023
** aze
** File description:
** aze
*/

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>

#include "scenes/menu.hpp"
#include "window.hpp"

void free_all(window::gm_window *window)
{
    delete window;
    SDL_Quit();
}

int main(int ac, char **av)
{
    window::gm_window* window = NULL;
    int return_value = 84;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || TTF_Init() < 0) {
        std::cout << "Error on SDL initialisation : " << SDL_GetError() << std::endl; 
        return return_value;
    }
    window = new window::gm_window;
    if (window == NULL || window->window == NULL) {
        std::cout << "Error on during window creation : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return return_value;
    }

    gm_scenes::init_draw_menu(window);
    
    return_value = start_game_loop(window);
    free_all(window);
    return return_value;
}
