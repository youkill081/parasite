/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

#include "window.hpp"
#include "gm_math.hpp"

#include <SDL2/SDL.h>

#include <string>

enum {
    RBB_IMAGE_RESIZE = 1,
    RBB_KEEP_PROPORTION = 2
};

namespace rbb_utils {
    class rbb_image {
    private:
        std::string texture_path;
        SDL_Texture *texture = NULL;
        SDL_Rect rect;

        int flags;
    public:
        rbb_image();
        rbb_image(std::string path, SDL_Rect rect, int flags);
        
        gm_math::gm_vector get_size(void);
        gm_math::gm_vector get_positon(void);
        void set_size(gm_math::gm_vector new_size);
        void set_position(gm_math::gm_vector new_position);

        void create_texture(window::gm_window *window);
        void draw(window::gm_window *window);
    };
}
