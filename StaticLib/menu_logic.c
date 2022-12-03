#include "logic.h"

extern bool game_started;

void run_main_menu(void)
{
    game_started = false;
    display_fill(0x00);	
    load_image_from_array((uint8_t *) menu_play_map,0,0,127,63);
    rectangle(48,27,75,38,1,3,1);
    draw_changes();
    while (1)
    {
        /* code */
    }
}

void menu_click_mid(void)
{

}
void menu_click_up(void)
{

}
void menu_click_down(void)
{

}
void menu_click_left(void)
{

}
void menu_click_right(void)
{

}
