#include "graphical_derivatives.h"

int setx;
int sety;

void get_tile_coordinates(uint8_t tile_x_number, uint8_t tile_y_number)
{
    setx = BOARD_START_X+3;
    sety = BOARD_START_Y+3;
    setx += TILE_SIDE * tile_x_number;
    sety += TILE_SIDE * tile_y_number; 
}

/// @brief Drawing game board frame and tiles inside it 
void draw_board(void)
{
    for (int i = 0; i < X_TILE_COUNT; i++)
    {
        for (int j = 0; j < Y_TILE_COUNT; j++)
        {
            rectangle(
                BOARD_START_X+(i*TILE_SIDE),
                BOARD_START_Y+(j*TILE_SIDE),
                BOARD_START_X+((i+1)*TILE_SIDE-1),
                BOARD_START_Y+((j+1)*TILE_SIDE-1),
                CL_BLACK,FILL_WHITE,VIRTUAL
            );
        }
    }
    rectangle(
        BOARD_START_X-2,
        BOARD_START_Y-2,
        BOARD_START_X+1+(X_TILE_COUNT*TILE_SIDE),
        BOARD_START_Y+1+(Y_TILE_COUNT*TILE_SIDE),
        CL_WHITE,NO_FILL,VIRTUAL
    );
}

void draw_selection(uint8_t x_number, uint8_t y_number)
{
    rectangle(
        BOARD_START_X + (TILE_SIDE * x_number),
        BOARD_START_Y + (TILE_SIDE * y_number),
        BOARD_START_X + (TILE_SIDE * (x_number+1)-1),
        BOARD_START_Y + (TILE_SIDE * (y_number+1)-1),
        CL_WHITE,NO_FILL,VIRTUAL
        );

    rectangle(
        BOARD_START_X+(TILE_SIDE * x_number)+1,
        BOARD_START_Y+(TILE_SIDE * y_number)+1,
        BOARD_START_X+(TILE_SIDE * (x_number+1)-2),
        BOARD_START_Y+(TILE_SIDE * (y_number+1)-2),
        CL_BLACK,NO_FILL,VIRTUAL
        );
}

void draw_default_tile_borders(uint8_t x_number, uint8_t y_number)
{
    rectangle(
        BOARD_START_X + (TILE_SIDE * x_number),
        BOARD_START_Y + (TILE_SIDE * y_number),
        BOARD_START_X + (TILE_SIDE * (x_number+1)-1),
        BOARD_START_Y + (TILE_SIDE * (y_number+1)-1),
        CL_BLACK,NO_FILL,VIRTUAL
    );

    rectangle(
        BOARD_START_X+(TILE_SIDE * x_number)+1,
        BOARD_START_Y+(TILE_SIDE * y_number)+1,
        BOARD_START_X+(TILE_SIDE * (x_number+1)-2),
        BOARD_START_Y+(TILE_SIDE * (y_number+1)-2),
        CL_WHITE,NO_FILL,VIRTUAL
    );
}

void draw_piktogramm(uint8_t pictogramm_number_in_array, uint8_t x_number, uint8_t y_number)
{   
    if (pictogramm_number_in_array == PIKTOGRAMM_OK)
    {
        tile_check_flag = 1;
    }
    else 
    {
        tile_check_flag = 0;
    }
    get_tile_coordinates(x_number,y_number);
    load_piktogramm_from_array(ingame_piktogramms,pictogramm_number_in_array,setx,sety);
}

void select_mode(uint8_t x_number, uint8_t y_number)
{
    static uint8_t color = 1;
    color = !color;    
    rectangle(
        BOARD_START_X + (TILE_SIDE * x_number),
        BOARD_START_Y + (TILE_SIDE * y_number),
        BOARD_START_X + (TILE_SIDE * (x_number+1)-1),
        BOARD_START_Y + (TILE_SIDE * (y_number+1)-1),
    color,3,VIRTUAL);
    rectangle(
        BOARD_START_X+(TILE_SIDE * x_number)+1,
        BOARD_START_Y+(TILE_SIDE * y_number)+1,
        BOARD_START_X+(TILE_SIDE * (x_number+1)-2),
        BOARD_START_Y+(TILE_SIDE * (y_number+1)-2),
    0,3,VIRTUAL);
    draw_changes();
}

void draw_number(uint8_t x_number, uint8_t y_number, uint8_t mine_count)
{
    tile_check_flag = 0;
    get_tile_coordinates(x_number,y_number);

    load_piktogramm_from_array(ingame_numbers,mine_count,setx,sety);
}


void draw_menu_difficulty(uint8_t difficulty)
{
    uint8_t start_posx = 51;
    uint8_t start_posy = 43;

    rectangle(start_posx-17,start_posy-1,start_posx+39,start_posy+6,CL_BLACK,CL_BLACK,VIRTUAL);
    load_piktogramm_from_array(menu_difficulty,difficulty,start_posx-7,start_posy);
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
