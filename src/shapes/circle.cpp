/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include "shapes/circle.hpp"
#include "gm_math.hpp"

namespace rbb_shape {
    gm_math::gm_vector rbb_circle::get_position()
    {
        return gm_math::gm_vector(this->rect.x, this->rect.y);
    }

    float rbb_circle::get_radius()
    {
        return this->radius;
    }

    void rbb_circle::set_position(gm_math::gm_vector new_pos)
    {
        this->rect.x = new_pos.x;
        this->rect.y = new_pos.y;
    }

    void rbb_circle::set_radius(float new_radius)
    {
        this->rect.h = new_radius;
        this->rect.w = new_radius; 
        this->radius = new_radius;
    }

    SDL_Rect rbb_circle::get_rect(void)
    {
        return this->rect;
    }

    rbb_circle::rbb_circle()
    {
        this->color = {0, 255, 0, 255};
        this->rect = {0, 0, 100, 100};
        this->radius = 100;
    }

    rbb_circle::rbb_circle(int x, int y, int radius, SDL_Color color)
    {
        this->color = color;
        this->rect = {x, y, radius, radius};
        this->radius = radius;
    }

    void rbb_circle::draw(window::gm_window *window)
    {
        SDL_RenderCopy(window->get_renderer(), this->texture, NULL, &this->rect);
    }
    
    void rbb_circle::create_texture(window::gm_window *window)
    {
        SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, this->rect.w, this->rect.h, 32, SDL_PIXELFORMAT_RGBA8888);
        
        SDL_PixelFormat *format = surf->format;
        SDL_LockSurface(surf);

        for (int y = 0; y < this->rect.h; y++) {
            for (int x = 0; x < this->rect.w; x++) {
                int dx = x - this->rect.w / 2;
                int dy = y - this->rect.h / 2;
                if (dx * dx + dy * dy <= (this->rect.w / 2) * (this->rect.w / 2)) {
                    ((Uint32*) surf->pixels)[y * this->rect.w + x] = SDL_MapRGBA(format, this->color.r, this->color.g, this->color.b, this->color.a);
                } else {
                    ((Uint32*) surf->pixels)[y * this->rect.w + x] = SDL_MapRGBA(format, 140, 10, 150, 0);
                }
            }
        }

        SDL_UnlockSurface(surf);

        this->texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf);

        SDL_FreeSurface(surf);
    }
}
