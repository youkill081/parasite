/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include "gm_math.hpp"

namespace gm_math {
    gm_rect::gm_rect() : top(0), left(0), width(0), height(0) {};
    gm_rect::gm_rect(float top, float left, float width, float height)
        : top(top), left(left), width(width), height(height) {};
}
