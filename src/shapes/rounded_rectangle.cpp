/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include "shapes/rounded_rectangle.hpp"

using namespace rbb_shape;

rbb_rounded_rectangle::rbb_rounded_rectangle(void)
{
    this->rect = {0, 0, 300, 100};
    this->exterior_color = {255, 0, 0, 255};
    this->interior_color = {0, 255, 0, 255};
    this->thickness = 2;
    this->distance = 20;
}

rbb_rounded_rectangle::rbb_rounded_rectangle(SDL_Rect rect, SDL_Color interior_color, SDL_Color exterior_color, short thickness, int distances)
{
    this->rect = rect;
    this->distance = distances;
    this->thickness = thickness;
    this->exterior_color = exterior_color;
    this->interior_color = interior_color;
}

gm_math::gm_vector rbb_rounded_rectangle::get_size(void)
{
    return gm_math::gm_vector(this->rect.w, this->rect.h);
}

gm_math::gm_vector rbb_rounded_rectangle::get_position(void)
{
    return gm_math::gm_vector(this->rect.x, this->rect.y);
}

void rbb_rounded_rectangle::set_size(gm_math::gm_vector new_size)
{
    this->rect.w = new_size.x;
    this->rect.h = new_size.y;
}

void rbb_rounded_rectangle::set_position(gm_math::gm_vector new_position)
{
    this->rect.x = new_position.x;
    this->rect.y = new_position.y;
}

bool draw_top_left(SDL_Surface *to_draw, int x, int y, Uint32 color_exterior, Uint32 color_interior, SDL_Rect *rect, int r, int distance)
{
    int r_pos_tl = distance;
    
    if (x <= r_pos_tl && y <= r_pos_tl) {
        int dx = std::abs(x - r_pos_tl);
        int dy = std::abs(y - r_pos_tl);
        if (dx * dx + dy * dy <= (distance - r) * (distance - r))
            ((Uint32 *)to_draw->pixels)[y * rect->w + x] = color_interior;
        else if (dx * dx + dy * dy <= distance * distance)
            ((Uint32 *)to_draw->pixels)[y * rect->w + x] = color_exterior;
        return true;
    }
    return false;
}

bool draw_top_right(SDL_Surface *to_draw, int x, int y, Uint32 color_exterior, Uint32 color_interior, SDL_Rect *rect, int r, int distance)
{
    int r_pos_x = rect->w - distance;
    int r_pos_y = distance;
    
    if (x >= r_pos_x && y <= r_pos_y) {
        int dx = std::abs(x - r_pos_x);
        int dy = std::abs(y - r_pos_y);
        if (dx * dx + dy * dy <= (distance - r) * (distance - r))
            ((Uint32 *)to_draw->pixels)[y * rect->w + x] = color_interior;
        else if (dx * dx + dy * dy <= distance * distance)
            ((Uint32 *)to_draw->pixels)[y * rect->w + x] = color_exterior;
        return true;
    }
    return false;
}

bool draw_bottom_left(SDL_Surface *to_draw, int x, int y, Uint32 color_exterior, Uint32 color_interior, SDL_Rect *rect, int r, int distance)
{
    int r_pos_x = distance;
    int r_pos_y = rect->h - distance;
    
    if (x <= r_pos_x && y >= r_pos_y) {
        int dx = std::abs(x - r_pos_x);
        int dy = std::abs(y - r_pos_y);
        if (dx * dx + dy * dy <= (distance - r) * (distance - r))
            ((Uint32 *)to_draw->pixels)[y * rect->w + x] = color_interior;
        else if (dx * dx + dy * dy <= distance * distance)
            ((Uint32 *)to_draw->pixels)[y * rect->w + x] = color_exterior;
        return true;
    }
    return false;
}

bool draw_bottom_right(SDL_Surface *to_draw, int x, int y, Uint32 color_exterior, Uint32 color_interior, SDL_Rect *rect, int r, int distance)
{
    int r_pos_x = rect->w - distance;
    int r_pos_y = rect->h - distance;
    
    if (x >= r_pos_x && y >= r_pos_y) {
        int dx = std::abs(x - r_pos_x);
        int dy = std::abs(y - r_pos_y);
        if (dx * dx + dy * dy <= (distance - r) * (distance - r))
            ((Uint32 *)to_draw->pixels)[y * rect->w + x] = color_interior;
        else if (dx * dx + dy * dy <= distance * distance)
            ((Uint32 *)to_draw->pixels)[y * rect->w + x] = color_exterior;
        return true;
    }
    return false;
}

void rbb_rounded_rectangle::create_texture(window::gm_window *window)
{
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, this->rect.w, this->rect.h, 32, SDL_PIXELFORMAT_RGBA8888);
        
    SDL_PixelFormat *format = surf->format;
    SDL_LockSurface(surf);

    Uint32 color_interior = SDL_MapRGBA(format, this->interior_color.r, this->interior_color.g, this->interior_color.b, this->interior_color.a);
    Uint32 color_exterior = SDL_MapRGBA(format, this->exterior_color.r, this->exterior_color.g, this->exterior_color.b, this->exterior_color.a);
    Uint32 color_transparent = SDL_MapRGBA(format, 0, 0, 0, 0);
    Uint32 color_black = SDL_MapRGBA(format, 0, 0, 0, 255);
    
    int r = this->thickness;
    
    for (int y = 0; y < this->rect.h; y++) {
        for (int x = 0; x < this->rect.w; x++) {
            if (draw_top_left(surf, x, y, color_exterior, color_interior, &this->rect, this->thickness, this->distance))
                continue;
            if (draw_top_right(surf, x, y, color_exterior, color_interior, &this->rect, this->thickness, this->distance))
                continue;
            if (draw_bottom_left(surf, x, y, color_exterior, color_interior, &this->rect, this->thickness, this->distance))
                continue;
            if (draw_bottom_right(surf, x, y, color_exterior, color_interior, &this->rect, this->thickness, this->distance))
                continue;
            if (x < this->thickness || y < this->thickness || this->rect.w - x <= this->thickness || this->rect.h - y <= this->thickness)
                ((Uint32*) surf->pixels)[y * this->rect.w + x] = color_exterior;
            else
                ((Uint32*) surf->pixels)[y * this->rect.w + x] = color_interior;
        }
    }

    SDL_UnlockSurface(surf);

    if (this->texture != NULL)
        SDL_DestroyTexture(this->texture);
    this->texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf);

    SDL_FreeSurface(surf);
}

void rbb_rounded_rectangle::draw(window::gm_window *window)
{
    if (this->texture == NULL)
        return;
    SDL_RenderCopy(window->get_renderer(), this->texture, NULL, &this->rect);
}
