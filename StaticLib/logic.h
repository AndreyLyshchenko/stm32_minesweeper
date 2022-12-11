#ifndef logic_H
    #define logic_H

    #include <stm32f10x.h>
    #include <stdbool.h>
    #include "constant_set.h"
    #include "buttons.h"
    #include "Graphics/graphical_derivatives.h"

   // void inicialise_piktogramm_array(void);
    void inicialise_tile_memory(void);
    void reset_recursion_markers(void);
    uint8_t searching_for_tiles_around_selected_one(uint8_t x_number, uint8_t y_number);
    void spawn_mines();
    void open_tile(uint8_t x_number, uint8_t y_number);
    void filling_surrounding_tiles(uint8_t map, uint8_t x_number, uint8_t y_number, uint8_t filler);
    void calculate_how_many_mines_around(void);
    
    void game_over(void);
    void win_check(void);

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

    void create_end_dialog_window(void);
    void end_dialog_click_mid(void);
    void end_dialog_click_up(void);
    void end_dialog_click_down(void);
    void end_dialog_click_left(void);
    void end_dialog_click_right(void);

    void end_dialog_item_select(void);
#endif