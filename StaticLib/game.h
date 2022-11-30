#ifndef game_H
    #define game_H

    #include <stm32f10x.h>
    #include "display.h"
    #include "buttons.h"

    #define TILE_SIDE 11
    #define BOARD_START_X 3
    #define BOARD_START_Y 4
    #define X_TILE_COUNT 11
    #define Y_TILE_COUNT 5
    #define PIKTOGRAMM_ARRAY_LENGTH 5

    extern uint8_t Board[128][8];
    extern uint8_t Game_UI[128][8];
    extern uint8_t Bit_map[128][8];

    void inicialise_piktogramm_array(void);
    void draw_board(void);
    void draw_selection (uint8_t x_number, uint8_t y_number);
    void draw_default_tile_borders(uint8_t x_number, uint8_t y_number);
    void draw_mine(uint8_t x_number, uint8_t y_number);
    void select_tile(uint8_t x_number, uint8_t y_number);
    void draw_flag(uint8_t x_number, uint8_t y_number);
    void draw_empty_tile(uint8_t x_number, uint8_t y_number);
    void draw_question_mark(uint8_t x_number, uint8_t y_number);
    void draw_arrows(uint8_t x_number, uint8_t y_number);
    void select_mode(uint8_t x_number, uint8_t y_number);
    void draw_ok(uint8_t x_number, uint8_t y_number);
    void draw_back(uint8_t x_number, uint8_t y_number);

#endif