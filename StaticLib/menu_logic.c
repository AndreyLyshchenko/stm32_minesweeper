#include "logic.h"

uint8_t menu_selector;
uint8_t selected_difficulty;
bool menu_select_mode_enabled;

void menu_item_select(uint8_t menu_selector,uint8_t color);
void menu_select_difficulty(void);


void menu_item_select(uint8_t menu_selector, uint8_t color)
{
    load_map(Bit_map,Board);
    if (menu_selector == 0) 
    {
        draw_menu_play_select(CL_WHITE);
    }
    else 
    {
        draw_menu_difficulty_select(color);
    }
    draw_changes();
}

void run_main_menu(void)
{
    if (!terminator)
    {
        selected_difficulty = MENU_MEDIUM;
    }
    terminator = false;
    game_started = false;
    restart_flag = false;
    menu_selector = 0;
    select_mode_enabled = false;

    put_pixel(0,0,CL_WHITE,REAL);

    inicialise_info_about_graphic_arrays();
    display_fill(0x00);	
    load_image_from_array((uint8_t *) menu_bit_map,0,0,127,63);
    copy_map(Board,Bit_map);
    menu_item_select(menu_selector,CL_WHITE);

    transfer_control_to_buttons();

    while (restart_flag)
    {
        start_game();
    }
}

void menu_click_mid(void)
{
    if (menu_selector == 0)
    {
        load_image_from_array((uint8_t *) loading_bit_map,0,0,127,63);
        draw_changes();
        start_game();
    }
    else
    {
        menu_select_mode_enabled = !menu_select_mode_enabled;
        menu_select_difficulty();
    }

}
void menu_click_up(void)
{
    if (!menu_select_mode_enabled)
    {
        if (menu_selector == 0) 
        {
            menu_selector = 1;
        }
        else
        {
            menu_selector--;
        }
        menu_item_select(menu_selector,CL_WHITE);
    }
}
void menu_click_down(void)
{   if (!menu_select_mode_enabled)
    {
        if (menu_selector == 1) 
        {
            menu_selector = 0;
        }
        else
        {
            menu_selector++;
        }
        menu_item_select(menu_selector,CL_WHITE);
    }
}
void menu_click_left(void)
{
    if (menu_select_mode_enabled) 
    {
        if (selected_difficulty == MENU_MEDIUM)
        {
            selected_difficulty = MENU_EASY;
        }
        else if (selected_difficulty == MENU_EASY)
        {
            selected_difficulty = MENU_HARD;
        }
        else 
        {
            selected_difficulty = MENU_MEDIUM;
        }
        menu_select_difficulty();
    }
}
void menu_click_right(void)
{
    if (menu_select_mode_enabled) 
    {   
        if (selected_difficulty == MENU_MEDIUM)
        {
            selected_difficulty = MENU_HARD;
        }
        else if (selected_difficulty == MENU_EASY)
        {
            selected_difficulty = MENU_MEDIUM;
        }
        else 
        {
            selected_difficulty = MENU_EASY;
        }
        menu_select_difficulty();
    }
}

void menu_select_difficulty(void)
{
    menu_item_select(menu_selector,CL_BLACK);
    draw_menu_difficulty(selected_difficulty);
    copy_map(Board,Bit_map);
    menu_item_select(menu_selector,CL_WHITE);
    draw_changes();
}