#include "graphical_derivatives.h"

extern uint8_t tile_check_flag;
extern uint8_t Bit_map[128][8];
extern uint8_t Board[128][8];
extern void (*piktograms[PIKTOGRAMM_ARRAY_LENGTH])(uint8_t,uint8_t);

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


void draw_mine(uint8_t x_number, uint8_t y_number)
{
    tile_check_flag = 0;

    get_tile_coordinates(x_number,y_number);

    put_pixel(setx,sety+0,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
    put_pixel(setx+4,sety+0,CL_BLACK,VIRTUAL);

    put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+1,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+1,CL_BLACK,VIRTUAL);

    put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);
    put_pixel(setx+0,sety+2,CL_BLACK,VIRTUAL);
    put_pixel(setx+4,sety+2,CL_BLACK,VIRTUAL);
    
    put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+3,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);	

    put_pixel(setx,sety+4,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
    put_pixel(setx+4,sety+4,CL_BLACK,VIRTUAL);
}
void draw_flag(uint8_t x_number, uint8_t y_number)
{
    tile_check_flag = 0;

    get_tile_coordinates(x_number,y_number);

    put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

    put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+1,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+1,CL_BLACK,VIRTUAL);
    put_pixel(setx+4,sety+1,CL_BLACK,VIRTUAL);

    put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);    

    put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);   

    put_pixel(setx+0,sety+4,CL_BLACK,VIRTUAL);
    put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
    put_pixel(setx+4,sety+4,CL_BLACK,VIRTUAL); 

}

void draw_mistake(uint8_t x_number, uint8_t y_number)
{
    tile_check_flag = 0;

    get_tile_coordinates(x_number,y_number);

    rectangle(setx-1,sety-1,setx+5,sety+5,CL_BLACK,CL_BLACK,VIRTUAL);

    put_pixel(setx+1,sety+0,CL_WHITE,VIRTUAL);
    put_pixel(setx+2,sety+0,CL_WHITE,VIRTUAL);
    put_pixel(setx+3,sety+0,CL_WHITE,VIRTUAL);

    put_pixel(setx+1,sety+1,CL_WHITE,VIRTUAL);
    put_pixel(setx+2,sety+1,CL_WHITE,VIRTUAL);
    put_pixel(setx+3,sety+1,CL_WHITE,VIRTUAL);
    put_pixel(setx+4,sety+1,CL_WHITE,VIRTUAL);

    put_pixel(setx+1,sety+2,CL_WHITE,VIRTUAL);
    put_pixel(setx+2,sety+2,CL_WHITE,VIRTUAL);
    put_pixel(setx+3,sety+2,CL_WHITE,VIRTUAL);    

    put_pixel(setx+1,sety+3,CL_WHITE,VIRTUAL);   

    put_pixel(setx+0,sety+4,CL_WHITE,VIRTUAL);
    put_pixel(setx+1,sety+4,CL_WHITE,VIRTUAL);
    put_pixel(setx+2,sety+4,CL_WHITE,VIRTUAL);
    put_pixel(setx+3,sety+4,CL_WHITE,VIRTUAL);
    put_pixel(setx+4,sety+4,CL_WHITE,VIRTUAL); 
}

void draw_empty_tile(uint8_t x_number, uint8_t y_number)
{
    tile_check_flag = 0;
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number;

    rectangle(setx-1,sety-1,setx+5,sety+5,1,1,VIRTUAL);
}

void draw_question_mark(uint8_t x_number, uint8_t y_number)
{
    tile_check_flag = 0;

    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number;

    put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

    put_pixel(setx+0,sety+1,CL_BLACK,VIRTUAL);
    put_pixel(setx+4,sety+1,CL_BLACK,VIRTUAL);

    put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);  

    put_pixel(setx+2,sety+3,CL_BLACK,VIRTUAL);   

    put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);   
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

void draw_ok(uint8_t x_number, uint8_t y_number)
{
    tile_check_flag = 1;

    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number;

    put_pixel(setx+4,sety+1,CL_BLACK,VIRTUAL);

    put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

    put_pixel(setx+0,sety+3,CL_BLACK,VIRTUAL);
    put_pixel(setx+2,sety+3,CL_BLACK,VIRTUAL);

    put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);

}

void draw_back(uint8_t x_number, uint8_t y_number)
{
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number;

    put_pixel(setx+0,sety+0,CL_BLACK,VIRTUAL);
    put_pixel(setx+4,sety+0,CL_BLACK,VIRTUAL);

    put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+1,CL_BLACK,VIRTUAL);
    
    put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);

    put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);
    put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

    put_pixel(setx+0,sety+4,CL_BLACK,VIRTUAL);
    put_pixel(setx+4,sety+4,CL_BLACK,VIRTUAL);  
}

void draw_number(uint8_t x_number, uint8_t y_number, uint8_t mine_count)
{
    tile_check_flag = 0;
    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number;
    
    switch (mine_count)
    {
    case 0:
        put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+1,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;

    case 1:
        put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+1,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;

    case 2:
        put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+1,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;   

    case 3:
        put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+1,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;  

    case 4:
        put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+1,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;    
    
    case 5:
        put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;

    case 6:
        put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;

    case 7:
        put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;    

    case 8:
        put_pixel(setx+1,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+0,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+0,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+1,CL_BLACK,VIRTUAL);
        put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+2,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+2,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+3,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+3,CL_BLACK,VIRTUAL);

        put_pixel(setx+1,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+2,sety+4,CL_BLACK,VIRTUAL);
        put_pixel(setx+3,sety+4,CL_BLACK,VIRTUAL);
        break;               

    default:
        break;
    }
}
