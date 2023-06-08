/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <SDL2/SDL.h>

#include "widget/text_rectangle.hpp"
#include "macro.hpp"

using namespace rbb_widget;

rbb_text_rectangle::rbb_text_rectangle(void)
{
    this->rect = {0, 0, 200, 100};
    
    this->rect_base_color = {0, 0, 0, 255};
    this->rect_hover_color = {255, 255, 255, 255};
    this->text_base_color = {255, 255, 255, 255};
    this->text_hover_color = {0, 0, 0, 255};

    this->rectangle = new rbb_shape::rbb_rectangle(this->rect, this->rect_base_color);
    this->rectangle_hover = new rbb_shape::rbb_rectangle(this->rect, this->rect_hover_color);
    this->text = new rbb_utils::rbb_text("default", this->text_base_color, DEFAULT_FONT, 30, this->rect);
    this->text_hover = new rbb_utils::rbb_text("default", this->text_hover_color, DEFAULT_FONT, 30, this->rect);
}

rbb_text_rectangle::rbb_text_rectangle(SDL_Rect rect, SDL_Color base_back_color, SDL_Color hover_back_color, std::string text, std::string font_path, SDL_Color base_text_color, SDL_Color hover_text_color)
{
    this->rect = rect;

    this->rect_base_color = base_back_color;
    this->rect_hover_color = hover_back_color;
    this->text_base_color = base_text_color;
    this->text_hover_color = hover_text_color;

    this->rectangle = new rbb_shape::rbb_rectangle(this->rect, this->rect_base_color);
    this->rectangle_hover = new rbb_shape::rbb_rectangle(this->rect, this->rect_hover_color);
    this->text = new rbb_utils::rbb_text(text, this->text_base_color, font_path, 20, this->rect);
    this->text_hover = new rbb_utils::rbb_text(text, this->text_hover_color, font_path, 20, this->rect);
}

void rbb_text_rectangle::create_element(window::gm_window *window)
{
    this->text->create_texture(window);
    this->text_hover->create_texture(window);
    SDL_Rect rect_area = this->rect;
    SDL_Rect text_area = this->text->get_text_area();
    gm_math::gm_vector new_pos = gm_math::gm_vector(rect_area.x + (rect_area.w / 2 - text_area.w / 2), rect_area.y + (rect_area.h / 2 - text_area.h / 2));
    this->text->set_position(new_pos);
    this->text_hover->set_position(new_pos);
}

gm_math::gm_vector rbb_text_rectangle::get_size(void)
{
    return gm_math::gm_vector(this->rect.w, this->rect.h);
}

gm_math::gm_vector rbb_text_rectangle::get_position(void)
{
    return gm_math::gm_vector(this->rect.x, this->rect.y);
}

void rbb_text_rectangle::set_size(gm_math::gm_vector new_size)
{
    this->rect.w = new_size.x;
    this->rect.h = new_size.y;
}

void rbb_text_rectangle::set_position(gm_math::gm_vector new_position)
{
    this->rect.x = new_position.x;
    this->rect.y = new_position.y;
}

void rbb_text_rectangle::refresh(window::gm_window *window, SDL_Rect *viewport)
{
    SDL_Rect real_pos = this->rect;
    if (viewport != NULL) {
        real_pos.x += viewport->x;
        real_pos.y += viewport->y;
    }

    if (window->event->mouse_position.x >= real_pos.x && window->event->mouse_position.x <= real_pos.x + real_pos.w &&
        window->event->mouse_position.y >= real_pos.y && window->event->mouse_position.y <= real_pos.y + real_pos.h)
        this->is_hover_v = true;
    else
        this->is_hover_v = false;
}

void rbb_text_rectangle::draw(window::gm_window *window)
{
    if (!this->is_hover_v) {
        this->rectangle->draw(window);
        this->text->draw(window);
    } else {
        this->rectangle_hover->draw(window);
        this->text_hover->draw(window);
    }
}

bool rbb_text_rectangle::is_hover(void)
{
    return this->is_hover_v;
}
