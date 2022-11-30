#include "game.h"

uint8_t mine_field[X_TILE_COUNT][Y_TILE_COUNT]; // if 0 - tile containing no mines, 1 - tile containing a mine
uint8_t how_many_mines_around[X_TILE_COUNT][Y_TILE_COUNT]; // X(0..8) mines placed around tile
uint8_t tile_check_flag; // This flag is used to tell the programm that we are going to open a tile

void (*piktograms[PIKTOGRAMM_ARRAY_LENGTH])(uint8_t,uint8_t);

/// @brief Initialising array of pointers on functions, wich used for drawing graphical primitives
void inicialise_piktogramm_array(void)
{
    piktograms[0]=draw_mine;
    piktograms[1]=draw_flag;
    piktograms[2]=draw_question_mark;
    piktograms[3]=draw_ok;
    piktograms[4]=draw_empty_tile;
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

    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number; 

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

    int setx = BOARD_START_X+3;
    int sety = BOARD_START_Y+3;
    setx += TILE_SIDE * x_number;
    sety += TILE_SIDE * y_number; 

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

void spawn_mines(uint8_t  mine_field[X_TILE_COUNT][Y_TILE_COUNT])
{
    for (uint8_t i = 0; i < X_TILE_COUNT; i++)
    {
        for (uint8_t j = 0; j < Y_TILE_COUNT; j++)
        {
            if (((i+j)%2==0))
            {
                mine_field[i][j]=1;
            }
                else 
                {
                    mine_field[i][j]=0;
                }
        }
        
    }
    
}

void calculate_how_many_mines_around
(uint8_t  mine_field[X_TILE_COUNT][Y_TILE_COUNT],uint8_t  how_many_mines_around[X_TILE_COUNT][Y_TILE_COUNT])
{
    uint8_t current_mine_count;
    for (uint8_t i = 0; i < (X_TILE_COUNT); i++)
    {
        for (uint8_t j = 0; j < (Y_TILE_COUNT); j++)
        {
            current_mine_count = 0;
            if (mine_field[i][j]==0) // Tile does not need to know how many mines around it if there is a mine inside it
            {
                bool do_not_check_top = false;      // Bool flags are not necessary, but they are used to
                bool do_not_check_left = false;     // simplify code understanding
                bool do_not_check_bottom = false;   //
                bool do_not_check_right = false;    //
                
                if (i == 0)
                {
                    do_not_check_left = true;
                }

                if (i == (X_TILE_COUNT-1))
                {
                    do_not_check_right = true;
                }

                if (j==0)
                {
                    do_not_check_top = true;
                }

                if (j==(Y_TILE_COUNT-1))
                {
                    do_not_check_bottom = true;
                }
                
                if (do_not_check_left!=true)
                {
                    if (do_not_check_top != true ) 
                    {
                        current_mine_count += mine_field[i-1][j-1];
                    }

                    current_mine_count += mine_field[i-1][j];

                    if (do_not_check_bottom != true) 
                    {
                        current_mine_count += mine_field[i-1][j+1];
                    }
                }
                
                if (do_not_check_top!=true)
                {
                    current_mine_count += mine_field[i][j-1];
                }    
                if (do_not_check_bottom != true) 
                {
                    current_mine_count += mine_field[i][j+1];
                }

                if (do_not_check_right!=true)
                {
                    if (do_not_check_top != true ) 
                    {
                        current_mine_count += mine_field[i+1][j-1];
                    }

                    current_mine_count += mine_field[i+1][j];

                    if (do_not_check_bottom != true ) 
                    {
                        current_mine_count += mine_field[i+1][j+1];
                    }
                }            
            }
            else
            {
                current_mine_count = 9; // Marking tile as mined
            }
            how_many_mines_around[i][j] = current_mine_count; 
        }
        
    }
    
}

void game_over(void)
{
    //display_fill(0XFF);
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