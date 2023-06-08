/*
** EPITECH PROJECT, 2023
** azee
** File description:
** eza
*/

#pragma once

namespace gm_math {
    class gm_vector {
    public:
        float x;
        float y;
        gm_vector();
        gm_vector(float x_val, float y_val);
        void sum(float x, float y);
    };

    class gm_rect {
    public:
        float top;
        float left;
        float width;
        float height;
        gm_rect();
        gm_rect(float left, float top, float width, float height);
    };
}
