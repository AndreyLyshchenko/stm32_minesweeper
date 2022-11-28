#include "game.h"


void draw_board(void)
{
    //int board_x = 7;
    //int board_y = 2;
    //int board_side = 11;

    for (int i = 0; i < X_TILE_COUNT; i++)
    {
        for (int j = 0; j < Y_TILE_COUNT; j++)
        {
            rectangle(
                BOARD_START_X+(i*TILE_SIDE),
                BOARD_START_Y+(j*TILE_SIDE),
                BOARD_START_X+((i+1)*TILE_SIDE-1),
                BOARD_START_Y+((j+1)*TILE_SIDE-1),
                0,1,REAL);
        }
    }
    rectangle(
        BOARD_START_X-2,
        BOARD_START_Y-2,
        BOARD_START_X+1+(10*TILE_SIDE),
        BOARD_START_Y+1+(5*TILE_SIDE),
    1,3,REAL);
}

void select_tile(uint8_t x_number, uint8_t y_number)
{
    rectangle(
        BOARD_START_X + (TILE_SIDE * x_number),
        BOARD_START_Y + (TILE_SIDE * y_number),
        BOARD_START_X + (TILE_SIDE * (x_number+1)-1),
        BOARD_START_Y + (TILE_SIDE * (y_number+1)-1),
    1,3,REAL);

    rectangle(
        BOARD_START_X+(TILE_SIDE * x_number)+1,
        BOARD_START_Y+(TILE_SIDE * y_number)+1,
        BOARD_START_X+(TILE_SIDE * (x_number+1)-2),
        BOARD_START_Y+(TILE_SIDE * (y_number+1)-2),
    0,3,REAL);
}

void draw_mine(uint8_t x_number, uint8_t y_number)
{
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number; 

    put_pixel(setx,sety+0,0,REAL);
    put_pixel(setx+2,sety+0,0,REAL);
    put_pixel(setx+4,sety+0,0,REAL);

    put_pixel(setx+1,sety+1,0,REAL);
    put_pixel(setx+2,sety+1,0,REAL);
    put_pixel(setx+3,sety+1,0,REAL);

    put_pixel(setx+1,sety+2,0,REAL);
    put_pixel(setx+2,sety+2,0,REAL);
    put_pixel(setx+3,sety+2,0,REAL);
    put_pixel(setx+0,sety+2,0,REAL);
    put_pixel(setx+4,sety+2,0,REAL);
    
    put_pixel(setx+1,sety+3,0,REAL);
    put_pixel(setx+2,sety+3,0,REAL);
    put_pixel(setx+3,sety+3,0,REAL);	

    put_pixel(setx,sety+4,0,REAL);
    put_pixel(setx+2,sety+4,0,REAL);
    put_pixel(setx+4,sety+4,0,REAL);
}