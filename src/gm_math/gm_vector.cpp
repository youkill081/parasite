/*
** EPITECH PROJECT, 2023
** azee
** File description:
** eza
*/

#include "gm_math.hpp"

namespace gm_math {
    gm_vector::gm_vector() : x(0), y(0) {};
    gm_vector::gm_vector(float x_val, float y_val) : x(x_val), y(y_val) {}
    void gm_vector::sum(float x, float y)
    {
        this->x += x;
        this->y += y;
    }
}
