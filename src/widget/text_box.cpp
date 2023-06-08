/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include "shapes/rectangle.hpp"
#include "widget/text_box.hpp"
#include "macro.hpp"

using namespace rbb_widget;

void rbb_text_box::init_components(window::gm_window *window)
{
    SDL_Rect interior_rect = {
        this->rect.x + this->border_thickness,
        this->rect.y + this->border_thickness,
        this->rect.w - this->border_thickness * 2,
        this->rect.h - this->border_thickness * 2
    };
    
    this->border_rectangle = new rbb_shape::rbb_hole_rectangle(this->rect, this->border_color, this->border_thickness);
    this->border_rectangle->create_texture(window);

    this->interior_rectangle = new rbb_shape::rbb_rectangle(interior_rect, this->interior_color);
    
    this->text = new rbb_utils::rbb_text(" ", this->font_color, this->font_path, this->font_size, interior_rect);
    this->text->create_texture(window);
    this->one_letter_rect = this->text->get_text_area();
    gm_math::gm_vector new_pos = gm_math::gm_vector(interior_rect.x + 5, interior_rect.y + (interior_rect.h / 2 - this->text->get_text_area().h / 2));
    this->text->set_position(new_pos);

    SDL_Rect rect_cursor = {(int) new_pos.x, (int) new_pos.y, 2, this->one_letter_rect.h};
    this->cursor = new rbb_shape::rbb_rectangle(rect_cursor, {0, 0, 0, 255});

    this->cursor_clock = new rbb_clock::rbb_clock();
}

rbb_text_box::rbb_text_box()
{
    this->border_thickness = 5;
    this->rect = {0, 0, 150, 40};
    this->border_color = {0, 255, 0, 255};
    this->interior_color = {255, 0, 0, 255};
    this->over_color = {0, 255, 0, 255};
    
    this->font_size = 10;
    this->font_path = DEFAULT_FONT;
    this->font_color = {0, 0, 0, 255};
}

rbb_text_box::rbb_text_box(SDL_Rect rect, int border_thickness, SDL_Color interior_color, SDL_Color over_color, SDL_Color border_color, std::string font_path, int font_size, SDL_Color font_color)
{
    this->border_thickness = border_thickness;
    this->rect = rect;
    this->border_color = border_color;
    this->interior_color = interior_color;
    this->over_color = over_color;

    this->font_size = font_size;
    this->font_path = font_path;
    this->font_color = font_color;
}

gm_math::gm_vector rbb_text_box::get_size(void)
{
    return gm_math::gm_vector(this->rect.w, this->rect.h);
}

gm_math::gm_vector rbb_text_box::get_position(void)
{
    return gm_math::gm_vector(this->rect.x, this->rect.y);
}

void rbb_text_box::set_size(gm_math::gm_vector new_size)
{
    this->rect.w = new_size.x;
    this->rect.h = new_size.y;
}

void rbb_text_box::set_position(gm_math::gm_vector new_position)
{
    this->rect.x = new_position.x;
    this->rect.y = new_position.y;
}

int rbb_text_box::get_boder_thickness(void)
{
    return this->border_thickness;
}

void rbb_text_box::set_border_thickess(int new_thicknes)
{
    this->border_thickness = new_thicknes;
}

void rbb_text_box::set_interior_color(SDL_Color color)
{
    this->interior_color = color;
}
void rbb_text_box::set_border_color(SDL_Color color)
{
    this->border_color = color;
}

bool rbb_text_box::is_selected(void)
{
    return this->selected;
}

bool rbb_text_box::was_selected(void)
{
    return this->was_selected_var;
}

void rbb_text_box::set_selected(bool new_selection)
{
    this->selected = new_selection;
}

std::string rbb_text_box::get_text(void)
{
    return this->type_text;
}

int size_utf_8(std::string str)
{
    int len  = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] & 0xC0) != 0x80)
            len++;
    }
    return len;
}

char *substr_utf8(std::string str, int i)
{
    while ((str[i] & 0xc0) == 0X80){
        i++;
    }
    return strdup(str.substr(0, i).c_str());
}

int get_i_utf8(std::string str, int index)
{
    int real_index = 0;
    int i = 0;
    while (i != index) {
        real_index++;
        if ((str[real_index] & 0xC0) != 0x80)
            i++;
    }
    return real_index;
}

void rbb_text_box::update(window::gm_window *window, SDL_Rect *view_port)
{
    SDL_Rect rect = this->interior_rectangle->get_rect();

    if (this->state == RBB_TEXT_BOX_STATE_DISABLE)
        return;
    if (view_port != NULL) {
        rect.x += view_port->x;
        rect.y += view_port->y;
    }
    this->was_selected_var = false;
    // choosing
    if (window->event->mouse_position.x >= rect.x && window->event->mouse_position.x <= rect.x + this->get_size().x &&
        window->event->mouse_position.y >= rect.y && window->event->mouse_position.y <= rect.y + this->get_size().y) {
        this->interior_rectangle->set_color(this->over_color);
        window->event->set_cursor(SDL_SYSTEM_CURSOR_HAND);
        if (window->event->button_is_pressed(BUTTON_LEFT)) {
            this->selected = true;
            this->was_selected_var = true;
        }
    } else {
        this->interior_rectangle->set_color(this->interior_color);
    }

    //text editing
    static int to_wait = 0;
    static int last_wait = 40;

    if (this->selected) {
        bool text_was_edit = false;
        if (not window->event->typed.empty()) {
            this->type_text.insert(get_i_utf8(this->type_text, this->cursor_position), window->event->typed);
            this->cursor_position += size_utf_8(window->event->typed);
            text_was_edit = true;
        }
        if (window->event->key_is_pressed(SDLK_BACKSPACE)) {
            to_wait--;
            if (to_wait <= 0 && this->cursor_position != 0) {
                if (not this->type_text.empty()) {
                    int num_bytes_to_delete = 1;
                    while ((this->type_text[get_i_utf8(this->type_text, this->cursor_position) - num_bytes_to_delete] & 0xC0) == 0x80) { 
                        num_bytes_to_delete++;
                    }
                    this->type_text.erase(get_i_utf8(this->type_text, this->cursor_position) - num_bytes_to_delete, num_bytes_to_delete);
                    text_was_edit = true;
                    this->cursor_position--;
                }
                to_wait = last_wait;
                if (last_wait == 40)
                    last_wait = 2;
            }
        } else {
            to_wait = 0;
            last_wait = 40;
        }
        if (text_was_edit) {
            this->text->set_text(this->type_text);
            this->text->create_texture(window);
        }

        //cursor gestion
        static int wait = 0;
        static bool is_first = true;
        if (this->cursor_clock->get_elapsed_second() > CURSOR_TIME) {
            this->cursor_display = not this->cursor_display;
            this->cursor_clock->restart();
        }
        if (window->event->key_is_pressed(SDLK_LEFT) || window->event->key_is_pressed(SDLK_RIGHT)) {
            this->cursor_display = true;
            this->cursor_clock->restart();
            wait--;
            if (wait < 0) {
                if (window->event->key_is_pressed(SDLK_LEFT)) {
                    if (cursor_position == 0 && is_first)
                        this->cursor_position = size_utf_8(this->type_text);
                    else 
                        this->cursor_position--;
                }
                else {
                    if (this->cursor_position == size_utf_8(this->type_text) && is_first)
                        this->cursor_position = 0;
                    else
                        this->cursor_position++;
                }
                text_was_edit = true;
                if (is_first) {
                    wait = 20;
                    is_first = false;
                } else 
                    wait = 2;
            }
        } else {
            wait = 0;
            is_first = true;
        }

        //utils key
        if (window->event->key_is_pressed_scancode(SDL_SCANCODE_END)) {
            this->cursor_display = true;
            this->cursor_clock->restart();
            this->cursor_position = size_utf_8(this->type_text);
            text_was_edit = true;
        }
        if (window->event->key_is_pressed_scancode(SDL_SCANCODE_HOME)) {
            this->cursor_display = true;
            this->cursor_clock->restart();
            this->cursor_position = 0;
            text_was_edit = true;
        }

        //setting grapgical position of cursor if text modified
        if (text_was_edit) {
            if (this->cursor_position < 0)
                this->cursor_position = 0;
            if (this->cursor_position > size_utf_8(this->type_text))
                this->cursor_position = size_utf_8(this->type_text);
            int w, h;
            TTF_SizeUTF8(this->text->get_font(), this->type_text.substr(0, get_i_utf8(this->type_text, this->cursor_position)).c_str(), &w, &h);
            this->cursor->set_position(gm_math::gm_vector(w + this->text->get_position().x, this->cursor->get_position().y));
        }
    }
}

void rbb_text_box::draw(window::gm_window *window)
{
    this->interior_rectangle->draw(window);
    this->border_rectangle->draw(window);
    this->text->draw(window);
    if (this->cursor_display && this->selected)
        this->cursor->draw(window);
}

void rbb_text_box::clear_text(window::gm_window *window)
{   
    this->type_text = "";
    this->cursor_position = 0;
    this->text->set_text(this->type_text);
    this->text->create_texture(window);

    this->cursor->set_position(gm_math::gm_vector(this->rect.x + this->border_thickness + 5, this->text->get_position().y));
}

void rbb_text_box::set_state(rbb_text_box_state new_state)
{
    this->state = new_state;

    if (new_state == RBB_TEXT_BOX_STATE_DISABLE) {
        this->interior_rectangle->set_color(this->disable_color);
    } else {
        this->interior_rectangle->set_color(this->interior_color);
    }
}
