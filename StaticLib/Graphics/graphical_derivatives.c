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
    if (pictogramm_number_in_array != PIKTOGRAMM_EMPTY_TILE)
    {
        if (pictogramm_number_in_array == PIKTOGRAMM_OK)
        {
            tile_check_flag = 1;
        }
        else 
        {
            tile_check_flag = 0;
        }
    }
    get_tile_coordinates(x_number,y_number);
    load_piktogramm_from_array(ingame_piktogramms,pictogramm_number_in_array,setx,sety);
}

// void draw_mine(uint8_t x_number, uint8_t y_number)
// {
//     tile_check_flag = 0;

//     get_tile_coordinates(x_number,y_number);

//     load_piktogramm_from_array(ingame_piktogramms,4,setx,sety);
// }
// void draw_flag(uint8_t x_number, uint8_t y_number)
// {
//     tile_check_flag = 0;

//     get_tile_coordinates(x_number,y_number);

//     load_piktogramm_from_array(ingame_piktogramms,0,setx,sety);

// }

// void draw_mistake(uint8_t x_number, uint8_t y_number)
// {
//     tile_check_flag = 0;

//     get_tile_coordinates(x_number,y_number);

//     load_piktogramm_from_array(ingame_piktogramms,5,setx,sety);
// }

// void draw_empty_tile(uint8_t x_number, uint8_t y_number)
// {
//     tile_check_flag = 0;

//     get_tile_coordinates(x_number,y_number);

//     rectangle(setx-1,sety-1,setx+5,sety+5,1,1,VIRTUAL);
// }

// void draw_question_mark(uint8_t x_number, uint8_t y_number)
// {
//     tile_check_flag = 0;

//     get_tile_coordinates(x_number,y_number);

//     load_piktogramm_from_array(ingame_piktogramms,1,setx,sety);   
// }

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

// void draw_ok(uint8_t x_number, uint8_t y_number)
// {
//     tile_check_flag = 1;

//     get_tile_coordinates(x_number,y_number);

//     load_piktogramm_from_array(ingame_piktogramms,2,setx,sety);

// }

// void draw_back(uint8_t x_number, uint8_t y_number)
// {
//     tile_check_flag = 1; 

//     get_tile_coordinates(x_number,y_number);

//     load_piktogramm_from_array(ingame_piktogramms,3,setx,sety);
// }

void draw_number(uint8_t x_number, uint8_t y_number, uint8_t mine_count)
{
    tile_check_flag = 0;
    get_tile_coordinates(x_number,y_number);

    load_piktogramm_from_array(ingame_numbers,mine_count,setx,sety);
}
