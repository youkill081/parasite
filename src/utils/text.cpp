/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "utils/text.hpp"
#include "window.hpp"
#include "macro.hpp"

using namespace rbb_utils;

bool rbb_text::recreate_font(void)
{
    if (this->font != NULL)
        TTF_CloseFont(font);
    this->font = TTF_OpenFont(this->font_path.c_str(), this->font_size);
    if (this->font == NULL) {
        std::cout << "Error while creating font : " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

rbb_text::rbb_text()
{
    this->texture = NULL;
    this->font = TTF_OpenFont(DEFAULT_FONT, 60);
    if (this->font == NULL) {
        std::cout << "Error while creating font : " << SDL_GetError() << std::endl;
        return;
    }

    this->color = {0, 0, 255, 255};
    this->text = "default";
    this->rect = {0, 0, 400, 150};
    this->font_path = DEFAULT_FONT;
    this->font_size = 60;
}

rbb_text::rbb_text(std::string text, SDL_Color color, std::string font_path, int font_size, SDL_Rect rect)
{
    this->texture = NULL;
    this->font = TTF_OpenFont(font_path.c_str(), font_size);

    if (this->font == NULL) {
        std::cout << "Error while creating font : " << SDL_GetError() << std::endl;
        return;
    }
    this->text =text;
    this->color = color;
    this->rect = rect;
    this->font_path = font_path;
    this->font_size = font_size;
}

void rbb_text::create_texture(window::gm_window *window)
{
    int w, h;
    SDL_Surface *surf = TTF_RenderUTF8_Blended(this->font, this->text.c_str(), this->color);
    SDL_DestroyTexture(this->texture);
    this->texture = SDL_CreateTextureFromSurface(window->get_renderer(), surf);
    SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
    if (w < this->rect.w) {
        this->draw_rect = {this->rect.x, this->rect.y, w, h};
        this->cut_rect = {0, 0, w, h};
    }
    else {
        this->draw_rect = {this->rect.x, this->rect.y, this->rect.w, h};
        this->cut_rect = {0, 0, this->rect.w, h};
    }
    SDL_FreeSurface(surf);
}

void rbb_text::set_text(std::string text)
{
    this->text = text;
}

std::string rbb_text::get_text(void)
{
    return this->text;
}

gm_math::gm_vector rbb_text::get_size(void)
{
    return gm_math::gm_vector(this->rect.w, this->rect.h);
}

gm_math::gm_vector rbb_text::get_position(void)
{
    return gm_math::gm_vector(this->rect.x, this->rect.y);
}

void rbb_text::set_size(gm_math::gm_vector new_size)
{
    this->rect.w = new_size.x;
    this->rect.h = new_size.y;
}

void rbb_text::set_position(gm_math::gm_vector new_pos)
{
    this->rect.x = new_pos.x;
    this->rect.y = new_pos.y;
    this->recalc_position();
}

SDL_Color rbb_text::get_color(void)
{
    return this->color;
}

void rbb_text::set_font_size(int new_size)
{
    this->font_size = new_size;
}

int rbb_text::get_font_size(void)
{
    return this->font_size;
}

void rbb_text::set_color(SDL_Color new_color)
{
    this->color = new_color;
}

void rbb_text::recalc_position(void)
{
    this->draw_rect.x = this->rect.x;
    this->draw_rect.y = this->rect.y;
}

SDL_Rect rbb_text::get_text_area(void)
{
    int x, y;
    SDL_QueryTexture(this->texture, NULL, NULL, &x, &y);
    return {this->rect.x, this->rect.y, x, y};
}

void rbb_text::draw(window::gm_window *window)
{
    SDL_RenderCopy(window->get_renderer(), this->texture, &this->cut_rect, &this->draw_rect);
}

TTF_Font *rbb_text::get_font(void)
{
    return this->font;
}
