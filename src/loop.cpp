/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <SDL2/SDL.h>

#include "shapes/gradient_square.hpp"
#include "window.hpp"
#include "macro.hpp"

void display_background(rbb_shape::rbb_gradient_square *square, window::gm_window *window)
{
    int size_x;
    int size_y;
    
    if (window->event->was_resize) {
        SDL_GetWindowSize(window->window, &size_x, &size_y);
        square->set_size(gm_math::gm_vector(size_x, size_y));
    }
    square->draw_square(window);
}

int start_game_loop(window::gm_window *window)
{   
    rbb_shape::rbb_gradient_square *background = new rbb_shape::rbb_gradient_square(0, 0, 1980, 1080, {230, 230, 230, 255}, {190, 190, 190, 255});
    background->create_texture(window);
    
    while (window->is_open) {
        window->refresh_event();
        window->reset_window();
        display_background(background, window);
        window->refresh_window();
    }
    return 0;
}
