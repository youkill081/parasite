/*
** EPITECH PROJECT, 2023
** discover
** File description:
** base for window
*/

#include <SDL2/SDL.h>
#include <string>

#include "gm_math.hpp"
#include "window.hpp"

using namespace window;

gm_window::gm_window()
{
    this->window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
    this->event = new event::gm_event;
    is_open = true;
        
    SDL_SetRenderDrawColor(this->renderer, BG_R, BG_G, BG_B, BG_A);
}

void gm_window::refresh_event(void) {
    this->event->refresh(this);
}

void gm_window::refresh_window(void) {
    SDL_RenderPresent(this->renderer);
}

void gm_window::reset_window(void) {
    SDL_RenderClear(this->renderer);
}

SDL_Renderer *gm_window::get_renderer(void) {
    return this->renderer;
}

gm_math::gm_vector gm_window::get_size(void) {
    int w;
    int h;
    SDL_GetWindowSize(this->window, &w, &h);
    return gm_math::gm_vector(w, h);
}

void gm_window::set_viewport(SDL_Rect new_rect)
{
    SDL_RenderSetViewport(this->renderer, &new_rect);
}

void gm_window::reset_viewport(void)
{
    SDL_RenderSetViewport(this->renderer, NULL);
}

float gm_window::get_scale_factor(void)
{
    gm_math::gm_vector size = this->get_size();
    return std::fmin(size.x / SIZE_X, size.y / SIZE_Y);
}
