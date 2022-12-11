#include "logic.h"

uint8_t menu_selector;
uint8_t selected_difficulty;
bool menu_select_mode_enabled;

void inicialise_difficulties_array();
void menu_item_select(uint8_t menu_selector,uint8_t color);
void menu_select_difficulty(void);
void draw_menu_play_select(uint8_t color);
void draw_menu_difficulty_select(uint8_t color);
void draw_menu_easy();
void draw_menu_medium();
void draw_menu_hard();

void (*difficulties[DIFFICULTIES_ARRAY_LENGTH])(void);


/// @brief Initialising array of pointers on functions, wich used for drawing graphical primitives
void inicialise_difficulties_array(void)
{
   difficulties[0]=draw_menu_easy;
   difficulties[1]=draw_menu_medium;
   difficulties[2]=draw_menu_hard;
}

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

void draw_menu_medium()
{
    uint8_t start_posx = 51;
    uint8_t start_posy = 43;

    rectangle(start_posx-17,start_posy-1,start_posx+39,start_posy+6,CL_BLACK,CL_BLACK,VIRTUAL); 

    start_posx -=7;

    // M
    line(start_posx,start_posy,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+1,start_posy+1,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy+2,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+3,start_posy+1,CL_WHITE,VIRTUAL);
    line(start_posx+4,start_posy,start_posx+4,start_posy+5,CL_WHITE,VIRTUAL);

    start_posx+=7;

    // E
    line(start_posx,start_posy,start_posx+3,start_posy,CL_WHITE,VIRTUAL);
    line(start_posx,start_posy,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx,start_posy+3,start_posx+2,start_posy+3,CL_WHITE,VIRTUAL);
    line(start_posx,start_posy+5,start_posx+3,start_posy+5,CL_WHITE,VIRTUAL);

    start_posx+=6;
    
    // D
    line(start_posx,start_posy,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy,start_posx+2,start_posy,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy+5,start_posx+2,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx+3,start_posy+1,start_posx+3,start_posy+4,CL_WHITE,VIRTUAL);

    start_posx+=6;
    // I
    line(start_posx,start_posy,start_posx+2,start_posy,CL_WHITE,VIRTUAL);
    line(start_posx,start_posy+5,start_posx+2,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy+1,start_posx+1,start_posy+4,CL_WHITE,VIRTUAL);

    start_posx+=5;
    // U
    line(start_posx,start_posy,start_posx,start_posy+4,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy+5,start_posx+2,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx+3,start_posy,start_posx+3,start_posy+4,CL_WHITE,VIRTUAL);

    start_posx+=6;
    // M
    line(start_posx,start_posy,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+1,start_posy+1,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy+2,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+3,start_posy+1,CL_WHITE,VIRTUAL);
    line(start_posx+4,start_posy,start_posx+4,start_posy+5,CL_WHITE,VIRTUAL);
}

void draw_menu_hard()
{
    uint8_t start_posx = 51;
    uint8_t start_posy = 43;

    rectangle(start_posx-17,start_posy-1,start_posx+39,start_posy+6,CL_BLACK,CL_BLACK,VIRTUAL);

    // H
    line(start_posx,start_posy,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy+3,start_posx+2,start_posy+3,CL_WHITE,VIRTUAL);
    line(start_posx+3,start_posy,start_posx+3,start_posy+5,CL_WHITE,VIRTUAL);

    start_posx+= 6;
    // A
    line(start_posx,start_posy+1,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+1,start_posy,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+1,start_posy+3,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy+3,CL_WHITE,VIRTUAL);
    line(start_posx+3,start_posy+1,start_posx+3,start_posy+5,CL_WHITE,VIRTUAL);

    start_posx+=6;
    // R
    line(start_posx,start_posy,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy,start_posx+2,start_posy,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+3,start_posy+1,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy+2,start_posx+3,start_posy+2,CL_WHITE,VIRTUAL);
    put_pixel(start_posx+2,start_posy+3,CL_WHITE,VIRTUAL);
    line(start_posx+3,start_posy+4,start_posx+3,start_posy+5,CL_WHITE,VIRTUAL);
    
    start_posx+=6;
    // D
    line(start_posx,start_posy,start_posx,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy,start_posx+2,start_posy,CL_WHITE,VIRTUAL);
    line(start_posx+1,start_posy+5,start_posx+2,start_posy+5,CL_WHITE,VIRTUAL);
    line(start_posx+3,start_posy+1,start_posx+3,start_posy+4,CL_WHITE,VIRTUAL);
}



void draw_menu_play_select(uint8_t color)
{
    rectangle(48,27,75,38,color,NO_FILL,VIRTUAL);
}
void draw_menu_difficulty_select(uint8_t color)
{
    rectangle(32,40,92,51,color,NO_FILL,VIRTUAL);
    
    if (menu_select_mode_enabled)
    {
    // Left arrow
    line(30,40,30,51,color,VIRTUAL);
    put_pixel(29,40,color,VIRTUAL);
    line(28,40,23,45,color,VIRTUAL);
    put_pixel(29,51,color,VIRTUAL);
    line(23,46,28,51,color,VIRTUAL);    

    // Right arrow
    line(94,40,94,51,color,VIRTUAL);
    put_pixel(95,40,color,VIRTUAL);
    line(96,40,101,45,color,VIRTUAL);
    put_pixel(95,51,color,VIRTUAL);
    line(101,46,96,51,color,VIRTUAL);  
    }
}

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
        selected_difficulty = 1;
    }
    terminator = false;
    game_started = false;
    restart_flag = false;
    menu_selector = 0;
    select_mode_enabled = false;

    put_pixel(0,0,CL_WHITE,REAL);

    inicialise_difficulties_array();
    inicialise_info_about_piktogramm_arrays();
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
        if (selected_difficulty>0)
        {
            selected_difficulty--;
        }
        else
        {
            selected_difficulty = (DIFFICULTIES_ARRAY_LENGTH-1);
        }

        menu_select_difficulty();
    }
}
void menu_click_right(void)
{
    if (menu_select_mode_enabled) 
    {   
        if (selected_difficulty < (DIFFICULTIES_ARRAY_LENGTH-1))
        {
            selected_difficulty++;
        }
        else
        {
            selected_difficulty = 0;
        }
        menu_select_difficulty();
    }
}

void menu_select_difficulty(void)
{
    menu_item_select(menu_selector,CL_BLACK);
    difficulties[selected_difficulty]();
    copy_map(Board,Bit_map);
    menu_item_select(menu_selector,CL_WHITE);
    draw_changes();
}