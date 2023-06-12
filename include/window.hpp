/*
** EPITECH PROJECT, 2023
** sdl discover
** File description:
** header for window
*/

#pragma once

#define WINDOW_NAME "Parasite"
#define SIZE_X 1080
#define SIZE_Y 1100
#define BG_R 235
#define BG_G 235
#define BG_B 235
#define BG_A 255

#include <SDL2/SDL.h>
#include <string>

#include "gm_event.hpp"
#include "gm_math.hpp"

namespace window {
    class gm_window {
    private:
        SDL_Renderer *renderer;
    public:
        SDL_Window *window;
        event::gm_event *event;
        bool is_open;
        
        gm_window();
        void reset_window(void);
        void refresh_event(void);
        void reset_viewport(void);
        void refresh_window(void);
        float get_scale_factor(void);
        SDL_Renderer *get_renderer(void);
        gm_math::gm_vector get_size(void);
        void set_viewport(SDL_Rect new_rect);
    };
}
