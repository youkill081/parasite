/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

/*
class rbb_rectangle {
private:
    SDL_Rect rect;
    SDL_Color draw_color;
public:
    rbb_rectangle();
    rbb_rectangle(SDL_Rect rect, SDL_Color draw_color);

    gm_math::gm_vector get_size(void);
    gm_math::gm_vector get_position(void);
    void set_size(gm_math::gm_vector new_size);
    void set_position(gm_math::gm_vector new_position);

    void set_color(SDL_Color new_color);

    void draw(window::gm_window *window);
};
*/

#include "shapes/rectangle.hpp"

using namespace rbb_shape;

rbb_rectangle::rbb_rectangle(void)
{
    this->rect = {0, 0, 300, 50};
    this->draw_color = {0, 0, 0, 255};
}

rbb_rectangle::rbb_rectangle(SDL_Rect rect, SDL_Color color) : rect(rect), draw_color(color) {}

gm_math::gm_vector rbb_rectangle::get_size(void)
{
    return gm_math::gm_vector(this->rect.w, this->rect.h);
}

gm_math::gm_vector rbb_rectangle::get_position(void)
{
    return gm_math::gm_vector(this->rect.x, this->rect.y);
}

void rbb_rectangle::set_size(gm_math::gm_vector new_size)
{
    this->rect.w = new_size.x;
    this->rect.h = new_size.y;
}

void rbb_rectangle::set_position(gm_math::gm_vector new_size)
{
    this->rect.x = new_size.x;
    this->rect.y = new_size.y;
}

void rbb_rectangle::set_color(SDL_Color new_color)
{
    this->draw_color = new_color;
}

SDL_Rect rbb_rectangle::get_rect(void)
{
    return this->rect;
}

void rbb_rectangle::draw(window::gm_window *window)
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(window->get_renderer(), &r, &g, &b, &a);
    SDL_SetRenderDrawColor(window->get_renderer(), this->draw_color.r, this->draw_color.g, this->draw_color.b, this->draw_color.a);
    SDL_RenderFillRect(window->get_renderer(), &this->rect);
    SDL_SetRenderDrawColor(window->get_renderer(), r, g, b, a);
}
