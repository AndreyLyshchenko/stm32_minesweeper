#ifndef graphical_derivatives_H
    #define graphical_derivatives_H
    
    #include "../constant_set.h"
    #include "graphical_primitives.h"

    void get_tile_coordinates(uint8_t tile_x_number, uint8_t tile_y_number);
    void draw_board(void);
    void draw_selection (uint8_t x_number, uint8_t y_number);
    void draw_default_tile_borders(uint8_t x_number, uint8_t y_number);
    void draw_piktogramm(uint8_t pictogramm_number_in_array, uint8_t x_number, uint8_t y_number);

    void draw_mine(uint8_t x_number, uint8_t y_number);
    void draw_flag(uint8_t x_number, uint8_t y_number);
    void draw_mistake(uint8_t x_number, uint8_t y_number);
    void draw_empty_tile(uint8_t x_number, uint8_t y_number);
    void draw_question_mark(uint8_t x_number, uint8_t y_number);
    void draw_ok(uint8_t x_number, uint8_t y_number);
    void draw_back(uint8_t x_number, uint8_t y_number);
    void draw_number(uint8_t x_number, uint8_t y_number, uint8_t mine_count);

    void select_mode(uint8_t x_number, uint8_t y_number);
    void select_tile(uint8_t x_number, uint8_t y_number);

#endif