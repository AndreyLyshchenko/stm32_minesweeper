#include "logic.h"

extern bool game_started;

uint8_t menu_selector;
bool menu_select_mode_enabled;

void draw_menu_play_select();
void draw_menu_difficulty_select();
void draw_menu_easy();
void draw_menu_medium();
void draw_menu_hard();

void draw_menu_easy()
{
    uint8_t start_posx = 51;
    uint8_t start_posy = 43;

    rectangle(start_posx-17,start_posy-1,start_posx+39,start_posy+6,CL_BLACK,CL_BLACK,VIRTUAL);

    // E
    line(start_posx,start_posy,start_posx+3,start_posy,CL_WHITE,VIRTUAL);
    line(start_posx,start_posy,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx,start_posy+3,start_posx+2,start_posy+3,CL_WHITE,VIRTUAL);
    line(start_posx,start_posy+5,start_posx+3,start_posy+5,CL_WHITE,VIRTUAL);
    
    start_posx+=6;
    // A
    line(start_posx,start_posy+1,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+1,start_posy,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+1,start_posy+3,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy+3,CL_WHITE,VIRTUAL);
    line(start_posx+3,start_posy+1,start_posx+3,start_posy+5,CL_WHITE,VIRTUAL);

    start_posx+=6;
    // S
    put_pixel(start_posx+1,start_posy,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy,CL_WHITE,VIRTUAL);
    put_pixel(start_posx,start_posy+1,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+3,start_posy+1,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+1,start_posy+2,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy+3,CL_WHITE,VIRTUAL);
    put_pixel(start_posx,start_posy+4,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+3,start_posy+4,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+1,start_posy+5,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy+5,CL_WHITE,VIRTUAL);

    start_posx+=6;
    // Y
    rectangle(start_posx,start_posy,start_posx+3,start_posy+5,CL_WHITE,CL_WHITE,VIRTUAL);
    rectangle(start_posx+1,start_posy,start_posx+2,start_posy+2,CL_BLACK,NO_FILL,VIRTUAL);
    line(start_posx,start_posy+4,start_posx+2,start_posy+4,CL_BLACK,VIRTUAL);
}

void menu_item_select(uint8_t menu_selector);

void draw_menu_play_select()
{
    rectangle(48,27,75,38,CL_WHITE,NO_FILL,VIRTUAL);
}
void draw_menu_difficulty_select()
{
    rectangle(32,40,92,51,CL_WHITE,NO_FILL,VIRTUAL);
}

void menu_item_select(uint8_t menu_selector)
{
    load_map(Bit_map,Board);
    if (menu_selector == 0) 
    {
        draw_menu_play_select();
    }
    else 
    {
        draw_menu_difficulty_select();
    }
    draw_changes();
}

void run_main_menu(void)
{
    game_started = false;
    menu_selector = 0;
    select_mode_enabled = false;
    display_fill(0x00);	
    load_image_from_array((uint8_t *) menu_bit_map,0,0,127,63);
    copy_map(Board,Bit_map);
    menu_item_select(menu_selector);

    transfer_control_to_buttons();
}

void menu_click_mid(void)
{
    if (menu_selector == 0)
    {
        load_image_from_array((uint8_t *) loading_bit_map,0,0,127,63);
        draw_changes();
        start_game();
    }
    {
        menu_select_mode_enabled = !menu_select_mode_enabled;
    }

}
void menu_click_up(void)
{
    if (menu_selector == 0) 
    {
        menu_selector = 1;
    }
    else
    {
        menu_selector--;
    }
    menu_item_select(menu_selector);

}
void menu_click_down(void)
{
    if (menu_selector == 1) 
    {
        menu_selector = 0;
    }
    else
    {
        menu_selector++;
    }
    menu_item_select(menu_selector);
}
void menu_click_left(void)
{
    if (menu_select_mode_enabled) 
    {
        draw_menu_easy();
        draw_changes();
    }
}
void menu_click_right(void)
{
    if (menu_select_mode_enabled) 
    {
        //
    }
}
