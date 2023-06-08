/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <SDL2/SDL.h>

#include "shapes/hole_rectangle.hpp"
#include "window.hpp"

using namespace rbb_shape;

rbb_hole_rectangle::rbb_hole_rectangle()
{
    this->thickness = 20;
    this->color = {0, 0, 255, 255};
    this->rect = {0, 0, 300, 300};
    this->texture = NULL;
}

rbb_hole_rectangle::rbb_hole_rectangle(SDL_Rect rect, SDL_Color color, int thickness)
{
    this->thickness = thickness;
    this->rect = rect;
    this->color = color;
    this->texture = NULL;
}

int rbb_hole_rectangle::get_thickness(void)
{
    return this->thickness;
}

gm_math::gm_vector rbb_hole_rectangle::get_position(void)
{
    return gm_math::gm_vector(this->rect.x, this->rect.y);
}

gm_math::gm_vector rbb_hole_rectangle::get_size(void)
{
    return gm_math::gm_vector(this->rect.w, this->rect.h);
}

void rbb_hole_rectangle::set_thickness(int new_thickness)
{
    this->thickness = new_thickness;
}

void rbb_hole_rectangle::set_position(gm_math::gm_vector new_pos)
{
    this->rect.x = new_pos.x;
    this->rect.y = new_pos.y;
}

void rbb_hole_rectangle::set_size(gm_math::gm_vector new_size)
{
    this->rect.w = new_size.x;
    this->rect.h = new_size.y;
}

void rbb_hole_rectangle::create_texture(window::gm_window *window)
{
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, this->rect.w, this->rect.h, 32, SDL_PIXELFORMAT_RGBA8888);
        
    SDL_PixelFormat *format = surf->format;
    SDL_LockSurface(surf);

    Uint32 color_normal = SDL_MapRGBA(format, this->color.r, this->color.g, this->color.b, this->color.a);
    Uint32 color_transparent = SDL_MapRGBA(format, 0, 0, 0, 0);
    
    for (int y = 0; y < this->rect.h; y++) {
        for (int x = 0; x < this->rect.w; x++) {
            if (y <= this->thickness || x <= thickness ||
                y >= this->rect.h - this->thickness || x >= this->rect.w - this->thickness) {
                ((Uint32*) surf->pixels)[y * this->rect.w + x] = color_normal;
            } else {
                ((Uint32*) surf->pixels)[y * this->rect.w + x] = color_transparent;
            }
        }
    }

    SDL_UnlockSurface(surf);

    if (this->texture != NULL)
        SDL_DestroyTexture(this->texture);
    this->texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf);

    SDL_FreeSurface(surf);
}

void rbb_hole_rectangle::draw(window::gm_window *window)
{
    SDL_RenderCopy(window->get_renderer(), this->texture, NULL, &this->rect);
}
