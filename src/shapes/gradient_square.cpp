/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <SDL2/SDL.h>

#include "shapes/gradient_square.hpp"
#include "gm_math.hpp"
#include "window.hpp"

namespace rbb_shape {
    gm_math::gm_vector *rbb_gradient_square::get_size()
    {
        return new gm_math::gm_vector(this->rect.w, this->rect.h);
    }

    gm_math::gm_vector *rbb_gradient_square::get_position()
    {
        return new gm_math::gm_vector(this->rect.x, this->rect.y);
    }

    void rbb_gradient_square::set_position(gm_math::gm_vector new_pos)
    {
        this->rect.x = new_pos.x;
        this->rect.y = new_pos.y;
    }

    void rbb_gradient_square::set_size(gm_math::gm_vector new_pos)
    {
        this->rect.w = new_pos.x;
        this->rect.h = new_pos.y;
    }

    SDL_Rect rbb_gradient_square::get_rect()
    {
        return this->rect;
    }

    rbb_gradient_square::rbb_gradient_square()
    {
        this->from = {255, 255, 255, 255};
        this->to = {0, 0, 0, 0};

        this->rect = SDL_Rect();
        this->rect.x = 0;
        this->rect.y = 0;
        this->rect.h = 100;
        this->rect.w = 100;
    }

    rbb_gradient_square::rbb_gradient_square(float x, float y, float width, float height, SDL_Color from, SDL_Color to)
    {
        this->rect = SDL_Rect();
        this->rect.x = x;
        this->rect.y = y;
        this->rect.h = height;
        this->rect.w = width;

        this->from = from;
        this->to = to;
    }
    
    void rbb_gradient_square::create_texture(window::gm_window *window)
    {
        SDL_Surface *surf = SDL_CreateRGBSurface(0, this->rect.w, this->rect.h, 32, 0, 0, 0, 0);

        SDL_LockSurface(surf);

        SDL_PixelFormat *format = surf->format;
        float pow_w = pow(this->rect.w, 2);
        float pow_h = pow(this->rect.h, 2);
        
        for (int y = 0; y < this->rect.h; y++) {
            for (int x = 0; x < this->rect.w; x++) {
                float dist = sqrt(pow(this->rect.w - x, 2) + pow(this->rect.h - (this->rect.h + y), 2));
                float perc = dist / sqrt(pow_w + pow_h);

                Uint8 r = (1 - perc) * this->from.r + perc * this->to.r;
                Uint8 g = (1 - perc) * this->from.g + perc * this->to.g;
                Uint8 b = (1 - perc) * this->from.b + perc * this->to.b;

                ((Uint32 *) surf->pixels)[y * this->rect.w + x] = SDL_MapRGB(format, r, g, b);
            }
        }
        
        SDL_UnlockSurface(surf);

        this->texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf);

        SDL_FreeSurface(surf);
    }

    void rbb_gradient_square::draw_square(window::gm_window *window) {
        SDL_RenderCopy(window->get_renderer(), this->texture, NULL, &this->rect);
    }
} // namespace rbb_shape
