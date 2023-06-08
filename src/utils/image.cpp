/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include "utils/image.hpp"

#include <iostream>

using namespace rbb_utils;

rbb_image::rbb_image(void) : rect({0, 0, 0, 0}) {}

rbb_image::rbb_image(std::string path, SDL_Rect rect, int flags)
{
    this->texture_path = path;
    this->rect = rect;
    this->flags = flags;
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

gm_math::gm_vector get_texture_size(SDL_Texture *texture)
{
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    return gm_math::gm_vector(w, h);
}

void rbb_image::draw(window::gm_window *window)
{
    if (this->flags & RBB_IMAGE_RESIZE) {
        if (this->flags & RBB_KEEP_PROPORTION) {
            gm_math::gm_vector tex_size = get_texture_size(this->texture);
            float mul = fmin(std::fabs(this->rect.w / tex_size.x), std::fabs(this->rect.h / tex_size.y));
            SDL_Rect temp = {this->rect.x, this->rect.y, (int) (tex_size.x * mul), (int) (tex_size.y * mul)};
            SDL_RenderCopy(window->get_renderer(), this->texture, NULL, &temp);
        }
        else
            SDL_RenderCopy(window->get_renderer(), this->texture, NULL, &this->rect);
    } else {
        gm_math::gm_vector tex_size = get_texture_size(this->texture);
        SDL_Rect temp = {this->rect.x, this->rect.y, (int) tex_size.x, (int) tex_size.y};
        SDL_RenderCopy(window->get_renderer(),this->texture, NULL, &temp);
    }
}
