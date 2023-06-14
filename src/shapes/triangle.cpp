/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** main file for drawing a triangle
*/

#include "shapes/triangle.hpp"

using namespace rbb_shape;

rbb_triangle::rbb_triangle(void)
{
    this->rect = {0, 0, 100, 125};
    this->color = {0, 255, 0, 255};
    this->hover_color = {255, 0, 0, 255};
    this->angle = 0;
}

rbb_triangle::rbb_triangle(SDL_Rect rect, SDL_Color draw_color, SDL_Color hover_color, int angle)
{
    this->rect = rect;
    this->color = draw_color;
    this->hover_color = hover_color;
    this->angle = angle;

    this->hover = false;
}

void rbb_triangle::create_texture(window::gm_window *window)
{
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, this->rect.w, this->rect.h, 32, SDL_PIXELFORMAT_RGBA8888);
    SDL_Surface *surf_hover = SDL_CreateRGBSurfaceWithFormat(0, this->rect.w, this->rect.h, 32, SDL_PIXELFORMAT_RGBA8888);
    
    SDL_PixelFormat *format = surf->format;
    SDL_LockSurface(surf);
    SDL_LockSurface(surf_hover);

    Uint32 maped_color = SDL_MapRGBA(format, this->color.r, this->color.g, this->color.b, this->color.a);
    Uint32 maped_color_hover = SDL_MapRGBA(format, this->hover_color.r, this->hover_color.g, this->hover_color.b, this->hover_color.a);
    
    for (int y = 0; y < this->rect.h; y++) {
        int demi_row_size = this->rect.w / 2 - (y * this->rect.w / 2) / this->rect.h;
        int row_left = this->rect.w / 2 - demi_row_size;

        for (int x = 0; x < this->rect.w; x++) {
            if (x >= row_left && x < row_left + 2 * demi_row_size) {
                ((Uint32*)surf->pixels)[y * this->rect.w + x] = maped_color;
                ((Uint32*)surf_hover->pixels)[y * this->rect.w + x] = maped_color_hover;
            }
        }
    }

    SDL_UnlockSurface(surf);
    SDL_UnlockSurface(surf_hover);
    
    this->texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf);
    this->hover_texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf_hover);
    
    SDL_FreeSurface(surf);
}

gm_math::gm_vector rbb_triangle::get_size(void)
{
    return gm_math::gm_vector(this->rect.w, this->rect.h);
}

gm_math::gm_vector rbb_triangle::get_position(void)
{
    return gm_math::gm_vector(this->rect.x, this->rect.y);
}

void rbb_triangle::set_size(gm_math::gm_vector new_size)
{
    this->rect.w = new_size.x;
    this->rect.h = new_size.y;
}
void rbb_triangle::set_position(gm_math::gm_vector new_position)
{
    this->rect.x = new_position.x;
    this->rect.y = new_position.y;
}

SDL_Rect rbb_triangle::get_rect(void)
{
    return this->rect;
}

void rbb_triangle::set_color(SDL_Color new_color)
{
    this->color = new_color;
}

void rbb_triangle::update(window::gm_window *window, SDL_Rect *view_port)
{
    SDL_Rect real_rect = this->rect;

    if (view_port != NULL) {
        real_rect.x += view_port->x;
        real_rect.y += view_port->y;
    }

    if (window->event->mouse_position.x >= real_rect.x && window->event->mouse_position.x <= real_rect.x + real_rect.w &&
        window->event->mouse_position.y >= real_rect.y && window->event->mouse_position.y <= real_rect.y + real_rect.h)
        this->hover = true;
    else
        this->hover = false;
}

bool rbb_triangle::is_hover(void)
{
    return this->hover;
}

void rbb_triangle::draw(window::gm_window *window)
{
    if (not this->hover)
        SDL_RenderCopyEx(window->get_renderer(), this->texture, NULL, &this->rect, this->angle, NULL, SDL_FLIP_NONE);
    else
        SDL_RenderCopyEx(window->get_renderer(), this->hover_texture, NULL, &this->rect, this->angle, NULL, SDL_FLIP_NONE);
}

void rbb_triangle::draw(window::gm_window *window, SDL_RendererFlip flags)
{
    if (not this->hover)
        SDL_RenderCopyEx(window->get_renderer(), this->texture, NULL, &this->rect, this->angle, NULL, flags);
    else
        SDL_RenderCopyEx(window->get_renderer(), this->hover_texture, NULL, &this->rect, this->angle, NULL, flags);
}
