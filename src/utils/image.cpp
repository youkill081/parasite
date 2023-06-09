/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include "utils/image.hpp"

#include <iostream>

using namespace rbb_utils;

rbb_image::rbb_image(void) : rect({0, 0, 0, 0}), texture_rect(NULL) {}

rbb_image::rbb_image(std::string path, SDL_Rect rect, int flags)
{
    this->texture_path = path;
    this->rect = rect;
    this->flags = flags;
    this->texture_rect = NULL;
}

gm_math::gm_vector rbb_image::get_size(void)
{
    return gm_math::gm_vector(this->rect.w, this->rect.h);
}

gm_math::gm_vector rbb_image::get_positon(void)
{
    return gm_math::gm_vector(this->rect.x, this->rect.y);
}

void rbb_image::set_size(gm_math::gm_vector new_size)
{
    this->rect.w = new_size.x;
    this->rect.h = new_size.y;
}

void rbb_image::set_position(gm_math::gm_vector new_position)
{
    this->rect.x = new_position.x;
    this->rect.y = new_position.y;
}

void rbb_image::create_texture(window::gm_window *window)
{
    if (this->texture != NULL)
        SDL_DestroyTexture(this->texture);
    SDL_Surface *surf = SDL_LoadBMP(this->texture_path.c_str());
    if (surf == NULL) {
        std::cout << "Error: image not found -> " << this->texture_path << std::endl;
        return;
    }
    this->texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf);
    SDL_FreeSurface(surf);
}

gm_math::gm_vector rbb_image::get_texture_size(void)
{
    int w, h;
    SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
    return gm_math::gm_vector(w, h);
}

void rbb_image::set_texture_rect(SDL_Rect new_rect)
{
    if (this->texture_rect != NULL)
        free(texture_rect);
    this->texture_rect = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    this->texture_rect->x = new_rect.x;
    this->texture_rect->y = new_rect.y;
    this->texture_rect->w = new_rect.w;
    this->texture_rect->h = new_rect.h;
}

void rbb_image::move_texutre_rect(gm_math::gm_vector move)
{
    this->texture_rect->x += move.x;
    this->texture_rect->y += move.y;
}

void rbb_image::draw(window::gm_window *window)
{
    if (this->flags & RBB_IMAGE_RESIZE) {
        if (this->flags & RBB_KEEP_PROPORTION) {
            gm_math::gm_vector tex_size = this->get_texture_size();
            float mul = fmin(std::fabs(this->rect.w / tex_size.x), std::fabs(this->rect.h / tex_size.y));
            SDL_Rect temp = {this->rect.x, this->rect.y, (int) (tex_size.x * mul), (int) (tex_size.y * mul)};
            SDL_RenderCopy(window->get_renderer(), this->texture, this->texture_rect, &temp);
        }
        else
            SDL_RenderCopy(window->get_renderer(), this->texture, this->texture_rect, &this->rect);
    } else {
        gm_math::gm_vector tex_size = this->get_texture_size();
        SDL_Rect temp = {this->rect.x, this->rect.y, (int) tex_size.x, (int) tex_size.y};
        SDL_RenderCopy(window->get_renderer(),this->texture, this->texture_rect, &temp);
    }
}
