#include "game.h"


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
                0,1,VIRTUAL);
        }
    }
    rectangle(
        BOARD_START_X-2,
        BOARD_START_Y-2,
        BOARD_START_X+1+(10*TILE_SIDE),
        BOARD_START_Y+1+(5*TILE_SIDE),
    1,3,VIRTUAL);
}

void draw_selection(uint8_t x_number, uint8_t y_number)
{
    rectangle(
        BOARD_START_X + (TILE_SIDE * x_number),
        BOARD_START_Y + (TILE_SIDE * y_number),
        BOARD_START_X + (TILE_SIDE * (x_number+1)-1),
        BOARD_START_Y + (TILE_SIDE * (y_number+1)-1),
    1,3,VIRTUAL);

    rectangle(
        BOARD_START_X+(TILE_SIDE * x_number)+1,
        BOARD_START_Y+(TILE_SIDE * y_number)+1,
        BOARD_START_X+(TILE_SIDE * (x_number+1)-2),
        BOARD_START_Y+(TILE_SIDE * (y_number+1)-2),
    0,3,VIRTUAL);
}

void draw_default_tile_borders(uint8_t x_number, uint8_t y_number)
{
    rectangle(
        BOARD_START_X + (TILE_SIDE * x_number),
        BOARD_START_Y + (TILE_SIDE * y_number),
        BOARD_START_X + (TILE_SIDE * (x_number+1)-1),
        BOARD_START_Y + (TILE_SIDE * (y_number+1)-1),
    0,3,VIRTUAL);

    rectangle(
        BOARD_START_X+(TILE_SIDE * x_number)+1,
        BOARD_START_Y+(TILE_SIDE * y_number)+1,
        BOARD_START_X+(TILE_SIDE * (x_number+1)-2),
        BOARD_START_Y+(TILE_SIDE * (y_number+1)-2),
    1,3,VIRTUAL);
}

void draw_mine(uint8_t x_number, uint8_t y_number)
{
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number; 

    put_pixel(setx,sety+0,0,VIRTUAL);
    put_pixel(setx+2,sety+0,0,VIRTUAL);
    put_pixel(setx+4,sety+0,0,VIRTUAL);

    put_pixel(setx+1,sety+1,0,VIRTUAL);
    put_pixel(setx+2,sety+1,0,VIRTUAL);
    put_pixel(setx+3,sety+1,0,VIRTUAL);

    put_pixel(setx+1,sety+2,0,VIRTUAL);
    put_pixel(setx+2,sety+2,0,VIRTUAL);
    put_pixel(setx+3,sety+2,0,VIRTUAL);
    put_pixel(setx+0,sety+2,0,VIRTUAL);
    put_pixel(setx+4,sety+2,0,VIRTUAL);
    
    put_pixel(setx+1,sety+3,0,VIRTUAL);
    put_pixel(setx+2,sety+3,0,VIRTUAL);
    put_pixel(setx+3,sety+3,0,VIRTUAL);	

    put_pixel(setx,sety+4,0,VIRTUAL);
    put_pixel(setx+2,sety+4,0,VIRTUAL);
    put_pixel(setx+4,sety+4,0,VIRTUAL);
}
void draw_flag(uint8_t x_number, uint8_t y_number)
{
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number; 

    put_pixel(setx+1,sety+0,0,VIRTUAL);
    put_pixel(setx+2,sety+0,0,VIRTUAL);
    put_pixel(setx+3,sety+0,0,VIRTUAL);

    put_pixel(setx+1,sety+1,0,VIRTUAL);
    put_pixel(setx+2,sety+1,0,VIRTUAL);
    put_pixel(setx+3,sety+1,0,VIRTUAL);
    put_pixel(setx+4,sety+1,0,VIRTUAL);

    put_pixel(setx+1,sety+2,0,VIRTUAL);
    put_pixel(setx+2,sety+2,0,VIRTUAL);
    put_pixel(setx+3,sety+2,0,VIRTUAL);    

    put_pixel(setx+1,sety+3,0,VIRTUAL);   

    put_pixel(setx+0,sety+4,0,VIRTUAL);
    put_pixel(setx+1,sety+4,0,VIRTUAL);
    put_pixel(setx+2,sety+4,0,VIRTUAL);
    put_pixel(setx+3,sety+4,0,VIRTUAL);
    put_pixel(setx+4,sety+4,0,VIRTUAL); 

}
void draw_empty_tile(uint8_t x_number, uint8_t y_number)
{
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number;

    rectangle(setx-1,sety-1,setx+5,sety+5,1,1,VIRTUAL);
}

void draw_question_mark(uint8_t x_number, uint8_t y_number)
{
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number;

    put_pixel(setx+1,sety+0,0,VIRTUAL);
    put_pixel(setx+2,sety+0,0,VIRTUAL);
    put_pixel(setx+3,sety+0,0,VIRTUAL);

    put_pixel(setx+0,sety+1,0,VIRTUAL);
    put_pixel(setx+4,sety+1,0,VIRTUAL);

    put_pixel(setx+3,sety+2,0,VIRTUAL);  

    put_pixel(setx+2,sety+3,0,VIRTUAL);   

    put_pixel(setx+2,sety+4,0,VIRTUAL);   
 
}
void draw_arrows(uint8_t x_number, uint8_t y_number)
{
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number; 


}

void select_tile(uint8_t x_number, uint8_t y_number)
{
    draw_selection(x_number,y_number);
    load_map(Bit_map,Board);

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

