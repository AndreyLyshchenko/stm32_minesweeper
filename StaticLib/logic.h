#ifndef logic_H
    #define logic_H

    #include <stm32f10x.h>
    #include <stdbool.h>
    #include "constant_set.h"
    #include "buttons.h"
    #include "Graphics/graphical_derivatives.h"

    extern uint8_t Board[128][8];
    extern uint8_t Game_UI[128][8];
    extern uint8_t Bit_map[128][8];
    extern uint8_t menu_bit_map[128*8];
    extern uint8_t loading_bit_map[128*8]; 
    extern int posx;
    extern int posy;
    extern bool select_mode_enabled; 

    void inicialise_piktogramm_array(void);
    void inicialise_tile_memory(void);

    void spawn_mines(uint8_t  mine_field[X_TILE_COUNT][Y_TILE_COUNT]);
    void calculate_how_many_mines_around
        (
         uint8_t  mine_field[X_TILE_COUNT][Y_TILE_COUNT],
         uint8_t  how_many_mines_around[X_TILE_COUNT][Y_TILE_COUNT]
        );
    
    void game_over(void);

    void run_main_menu(void);
    void menu_click_mid(void);
    void menu_click_up(void);
    void menu_click_down(void);
    void menu_click_left(void);
    void menu_click_right(void);

    void start_game(void);
    void ingame_click_mid(void);
    void ingame_click_up(void);
    void ingame_click_down(void);
    void ingame_click_left(void);
    void ingame_click_right(void);

#endif