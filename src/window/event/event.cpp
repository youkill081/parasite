/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <SDL2/SDL.h>

#include "window.hpp"

/*
class gm_event {
public:
    bool is_open;
    void refresh(gm_window* window);
};
*/

namespace window {
    namespace event {
        
        gm_event::gm_event()
        {
            for (int i = 0; i < 500; i++)
                this->keys[i] = false;
        }

        void update_cursor(SDL_SystemCursor cursor)
        {
            static SDL_Cursor *hand_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
            static SDL_Cursor *default_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

            if (hand_cursor == NULL || default_cursor == NULL) {
                return;
            }
            
            switch (cursor) {
            case SDL_SYSTEM_CURSOR_HAND:
                SDL_SetCursor(hand_cursor);
                break;
            default:
                SDL_SetCursor(default_cursor);
            }
        }
        
        void gm_event::refresh(gm_window *window) {
            SDL_Event e;

            this->was_resize = false;
            for (int i = 0; i < 3; i++)
                if (window->event->mouse[i] == PRESSED)
                    window->event->mouse[i] = HOLD;
            this->typed.clear();
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    window->is_open = false;
                    this->is_open = false;
                }
                if (e.type == SDL_WINDOWEVENT) {
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED){
                        this->was_resize = true;
                    }
                }
                if (e.type == SDL_KEYUP)
                {
                    this->keys[e.key.keysym.sym % 500] = false;
                }
                if (e.type == SDL_KEYDOWN)
                {
                    this->keys[e.key.keysym.sym % 500] = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    this->mouse[e.button.button - 1] = PRESSED;
                }
                if (e.type == SDL_MOUSEBUTTONUP) {
                    this->mouse[e.button.button - 1] = RELEASED;
                }
                if (e.type == SDL_TEXTINPUT) {
                    this->typed.append(e.text.text);
                }
            }
            //update mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);
            this->mouse_position.x = x; this->mouse_position.y = y;

            //update mouse cursor
            update_cursor((SDL_SystemCursor) this->cursor);
            this->cursor = SDL_SYSTEM_CURSOR_ARROW;
        }

        bool gm_event::key_is_pressed(int key)
        {
            return this->keys[key % 500];
        }

        bool gm_event::button_is_pressed(int button)
        {
            if (this->mouse[button] == PRESSED)
                return true;
            return false;
        }

        bool gm_event::button_is_hold(int button)
        {
            if (this->mouse[button] == HOLD)
                return true;
            return false;
        }

        bool gm_event::key_is_pressed_scancode(int key)
        {
            const Uint8* state = SDL_GetKeyboardState(nullptr);

            if (state[key]) {
                return true;
            }
            return false;
        }

        void gm_event::set_cursor(int new_cursor) {
            this->cursor = new_cursor;
        }
    }
}
