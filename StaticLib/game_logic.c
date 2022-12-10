#include "logic.h"

uint8_t mine_field[X_TILE_COUNT][Y_TILE_COUNT]; // if 0 - tile containing no mines, 1 - tile containing a mine
uint8_t recursion_marker[X_TILE_COUNT][Y_TILE_COUNT]; // if 1 - tile has been already checked in a recursion cycle
uint8_t how_many_mines_around[X_TILE_COUNT][Y_TILE_COUNT]; // X(0..8) mines placed around tile
uint8_t tile_memory[X_TILE_COUNT][Y_TILE_COUNT]; // Contains info about previously held pictogram 
uint8_t tile_check_flag; // This flag is used to tell the programm that we are going to open a tile
uint8_t open_tiles_counter;
uint8_t board_mine_count;
bool game_started;
bool game_over_flag;
bool win_flag;
bool ending_dialog;
bool first_check;
bool now_drawing;
uint8_t ingame_selector;

void (*piktograms[PIKTOGRAMM_ARRAY_LENGTH])(uint8_t,uint8_t);


void inicialise_tile_memory(void)
{
    for (uint8_t x = 0; x < X_TILE_COUNT; x++)
    {
        for (uint8_t y = 0; y < Y_TILE_COUNT; y++)
        {
            tile_memory[x][y] = 3;
        }
    }
}

/// @brief Initialising array of pointers on functions, wich used for drawing graphical primitives
void inicialise_piktogramm_array(void)
{
    piktograms[0]=draw_flag;
    piktograms[1]=draw_question_mark;
    piktograms[2]=draw_ok;
    piktograms[3]=draw_empty_tile;
}

void reset_recursion_markers(void)
{
	for (uint8_t x = 0; x < X_TILE_COUNT; x++)
	{
		for (uint8_t y = 0; y < Y_TILE_COUNT; y++)
		{
			recursion_marker[x][y] = 0;	
		}	
	}
}

void select_tile(uint8_t x_number, uint8_t y_number)
{
    load_map(Bit_map,Board);
    draw_selection(x_number,y_number);
}

void spawn_mines()
{
	bool bad_seed_flag = false;
	uint8_t mine_count;
	switch (selected_difficulty)
	{
	case 0:
		mine_count  = 8;
		break;
	case 1:
		mine_count  = 12;
		break;
	case 2:
		mine_count  = 16;
		break;		
	default:
		break;
	}
	board_mine_count = mine_count;
	uint16_t mines_coordinates[board_mine_count];
	uint8_t mine_number = 0;

	for (uint8_t i = 0; i < X_TILE_COUNT; i++)
	{
		for (uint8_t j = 0; j < Y_TILE_COUNT; j++)
		{
			mine_field[i][j]=0;
		}
	}	

	uint8_t map = searching_for_tiles_around_selected_one(posx,posy);
	filling_surrounding_tiles(map,posx,posy,3); 		 	

	srand(TIM2 -> CNT);
	while (mine_count>0)
	{
		uint8_t x = (rand())%(X_TILE_COUNT);
		uint8_t y = (rand())%(Y_TILE_COUNT);
		
		if (mine_field[x][y]==0)
		{
			mine_field[x][y]=1;
			mine_count--;

			mines_coordinates[mine_number] = (uint16_t) (x<<8)|(y);
			mine_number++;
		}
	}

	filling_surrounding_tiles(map,posx,posy,0);

	for (uint8_t i = 0; i < board_mine_count; i++) // Checking for mines, surrounded by another mines 
	{
		uint8_t x = mines_coordinates[i] >> 8;
		uint8_t y = mines_coordinates[i] & 0x00FF;
		uint8_t tiles_around_mine_map = searching_for_tiles_around_selected_one(x,y);
		uint8_t tiles_around_mine = 0;
		uint8_t mines_around_mine = 0;
		if (tiles_around_mine_map & 0b10000000)	{if (mine_field[x-1][y-1]==1) {mines_around_mine++;} tiles_around_mine++;} 		
		if (tiles_around_mine_map & 0b01000000) {if (mine_field[x][y-1]==1) {mines_around_mine++;} tiles_around_mine++;}
		if (tiles_around_mine_map & 0b00100000) {if (mine_field[x+1][y-1]==1) {mines_around_mine++;} tiles_around_mine++;} 
		if (tiles_around_mine_map & 0b00010000) {if (mine_field[x+1][y]==1) {mines_around_mine++;} tiles_around_mine++;}
		if (tiles_around_mine_map & 0b00001000) {if (mine_field[x+1][y+1]==1) {mines_around_mine++;} tiles_around_mine++;}
		if (tiles_around_mine_map & 0b00000100) {if (mine_field[x][y+1]==1) {mines_around_mine++;} tiles_around_mine++;}
		if (tiles_around_mine_map & 0b00000010) {if (mine_field[x-1][y+1]==1) {mines_around_mine++;} tiles_around_mine++;}
		if (tiles_around_mine_map & 0b00000001) {if (mine_field[x-1][y]==1) {mines_around_mine++;} tiles_around_mine++;} 
		if (tiles_around_mine == mines_around_mine)
		{
			bad_seed_flag = true;
		}
	}

	if (bad_seed_flag)
	{
		spawn_mines();
	}
	
}

uint8_t searching_for_tiles_around_selected_one(uint8_t x_number, uint8_t y_number)
{
	// 0b 1   1    1	
	//    _   _   _ 	
	//	| _	| _	| _ |
	// 1| _	| X	| _ |1
	//	| _ | _ | _ |1	
	//    1   1 		

	uint8_t result = 0b11111111;

	if (x_number== 0) // Can't go left
	{
		result &= 0b01111100;
	}

	if (x_number== (X_TILE_COUNT-1)) // Can't go right 
	{
		result &= 0b11000111;
	}

	if (y_number==0) // Can't go up
	{
		result &= 0b00011111;
	}
	
	 if (y_number==(Y_TILE_COUNT-1)) // Can't go down
	{
		result &= 0b11110001;
	}

	return result;
}

void filling_surrounding_tiles(uint8_t map, uint8_t x_number, uint8_t y_number, uint8_t filler)
{
	mine_field[x_number][y_number] = filler;

	if (map & 0b10000000) {mine_field[x_number-1][y_number-1]=filler;} 		
	if (map & 0b01000000) {mine_field[x_number][y_number-1]=filler;}
	if (map & 0b00100000) {mine_field[x_number+1][y_number-1]=filler;} 
	if (map & 0b00010000) {mine_field[x_number+1][y_number]=filler;}
	if (map & 0b00001000) {mine_field[x_number+1][y_number+1]=filler;}
	if (map & 0b00000100) {mine_field[x_number][y_number+1]=filler;}
	if (map & 0b00000010) {mine_field[x_number-1][y_number+1]=filler;}
	if (map & 0b00000001) {mine_field[x_number-1][y_number]=filler;} 
}

void calculate_how_many_mines_around()
{
    uint8_t current_mine_count;
    for (uint8_t i = 0; i < (X_TILE_COUNT); i++)
    {
        for (uint8_t j = 0; j < (Y_TILE_COUNT); j++)
        {
            if (mine_field[i][j]==0) // Tile does not need to know how many mines around it if there is a mine inside it
            {
				current_mine_count = 0;
                uint8_t map = searching_for_tiles_around_selected_one(i,j);
				if (map & 0b10000000) {current_mine_count+=mine_field[i-1][j-1];} 		
				if (map & 0b01000000) {current_mine_count+=mine_field[i][j-1];}
				if (map & 0b00100000) {current_mine_count+=mine_field[i+1][j-1];} 
				if (map & 0b00010000) {current_mine_count+=mine_field[i+1][j];}
				if (map & 0b00001000) {current_mine_count+=mine_field[i+1][j+1];}
				if (map & 0b00000100) {current_mine_count+=mine_field[i][j+1];}
				if (map & 0b00000010) {current_mine_count+=mine_field[i-1][j+1];}
				if (map & 0b00000001) {current_mine_count+=mine_field[i-1][j];}          
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
    for (uint8_t x = 0; x < X_TILE_COUNT; x++)
    {
        for (uint8_t y = 0; y < Y_TILE_COUNT; y++)
        {
            draw_empty_tile(x,y);
            if (how_many_mines_around[x][y]==9)
            {
				if (tile_memory[x][y]!=0)
				{
					draw_mine(x,y);
				}
				else
				{
					draw_flag(x,y);
				}
            }
            else
            {
				if (tile_memory[x][y] != PIKTOGRAMM_ARRAY_LENGTH-1)
				{
					if (tile_memory[x][y] == 0)
					{
						draw_mistake(x,y);
					}
					else if(tile_memory[x][y] != 1) // Preventing reveal of '?' marked tiles
					{
						draw_number(x,y,how_many_mines_around[x][y]);
					}
				}
            }
        }
    }
	game_over_flag = true;
    draw_changes();
}


void start_game(void)
{
	open_tiles_counter = 0;
	now_drawing = false;
    game_started = true;
	game_over_flag = false;
	ending_dialog = false;
	win_flag = false;
	first_check = true;
	terminator = false;
	restart_flag = false;
    posx=0;
	posy=0;
	inicialise_piktogramm_array();
	inicialise_tile_memory();
	ingame_selector = 0;

	reset_map(Bit_map);
	draw_board();
	copy_map(Board,Bit_map);
	select_tile(0,0);
	draw_changes();

	transfer_control_to_buttons();
}

void ingame_click_mid(void)
{
	if (game_over_flag != true)
	{
		if (tile_memory[posx][posy]!=PIKTOGRAMM_ARRAY_LENGTH) // Preventing interactions with already opend tile
		{
			if (select_mode_enabled)
			{

				if (tile_check_flag == 1)
				{
					if (first_check)
					{
						spawn_mines();
						calculate_how_many_mines_around();
						first_check = false;
					}	

					if (how_many_mines_around[posx][posy]==9)
					{
						game_over();
					}
					else 
					{
						reset_recursion_markers();
						open_tile(posx,posy);
						select_tile(posx,posy);
						draw_changes();
						now_drawing = false; 
						select_mode_enabled = !select_mode_enabled;
						return;
					}
				}
				draw_default_tile_borders(posx,posy);
				copy_map(Board,Bit_map);
				draw_selection(posx,posy);
				draw_changes();	
				
			} else
			{
				draw_empty_tile(posx,posy);
				ingame_selector=tile_memory[posx][posy];
				piktograms[ingame_selector](posx,posy);
				draw_selection(posx,posy);
				draw_changes();
			}
			select_mode_enabled = !select_mode_enabled;
		}
	}
	else
	{
		ending_dialog = true;
		create_end_dialog_window();
		//terminator = true;
	}	
}

void open_tile(uint8_t x_number, uint8_t y_number)
{
	now_drawing = true;
	open_tiles_counter+=1;
	recursion_marker[x_number][y_number] = 1;
	tile_memory[x_number][y_number] = PIKTOGRAMM_ARRAY_LENGTH; // Marking tile as opend (to prevent modifing manually)
	draw_empty_tile(x_number,y_number);
	draw_default_tile_borders(x_number,y_number);
	draw_number(x_number,y_number,how_many_mines_around[x_number][y_number]);
	copy_map(Board,Bit_map);
	//draw_changes();
	if (how_many_mines_around[x_number][y_number]==0)
	{
		uint8_t map = searching_for_tiles_around_selected_one(x_number,y_number);
		if ((map & 0b10000000) && (recursion_marker[x_number-1][y_number-1]==0) && (tile_memory[x_number-1][y_number-1]!=PIKTOGRAMM_ARRAY_LENGTH)) {open_tile(x_number-1,y_number-1);} 		
		if ((map & 0b01000000) && (recursion_marker[x_number][y_number-1]==0) && (tile_memory[x_number][y_number-1]!=PIKTOGRAMM_ARRAY_LENGTH)) {open_tile(x_number,y_number-1);}
		if ((map & 0b00100000) && (recursion_marker[x_number+1][y_number-1]==0) && (tile_memory[x_number+1][y_number-1]!=PIKTOGRAMM_ARRAY_LENGTH)) {open_tile(x_number+1,y_number-1);} 
		if ((map & 0b00010000) && (recursion_marker[x_number+1][y_number]==0) && (tile_memory[x_number+1][y_number]!=PIKTOGRAMM_ARRAY_LENGTH)) {open_tile(x_number+1,y_number);}
		if ((map & 0b00001000) && (recursion_marker[x_number+1][y_number+1]==0) && (tile_memory[x_number+1][y_number+1]!=PIKTOGRAMM_ARRAY_LENGTH)) {open_tile(x_number+1,y_number+1);}
		if ((map & 0b00000100) && (recursion_marker[x_number][y_number+1]==0) && (tile_memory[x_number][y_number+1]!=PIKTOGRAMM_ARRAY_LENGTH)) {open_tile(x_number,y_number+1);}
		if ((map & 0b00000010) && (recursion_marker[x_number-1][y_number+1]==0) && (tile_memory[x_number-1][y_number+1]!=PIKTOGRAMM_ARRAY_LENGTH)) {open_tile(x_number-1,y_number+1);}
		if ((map & 0b00000001) && (recursion_marker[x_number-1][y_number]==0) && (tile_memory[x_number-1][y_number]!=PIKTOGRAMM_ARRAY_LENGTH)) {open_tile(x_number-1,y_number);}   
	}
	win_check();
}

void ingame_click_up(void)
{
    if (!select_mode_enabled)
	{
		if (posy>0)
		{
			posy--;
		}
		else 
		{
			posy = Y_TILE_COUNT - 1;
		}
		select_tile(posx,posy);
		draw_changes();
	}
}
void ingame_click_down(void)
{
    if (!select_mode_enabled)
	{
		if (posy<(Y_TILE_COUNT-1))
		{
			posy++;
		}
		else 
		{
			posy = 0;
		}
		select_tile(posx,posy);
		draw_changes();
	}	
}
void ingame_click_left(void)
{
    if (!select_mode_enabled)
	{
		if (posx>0)
		{
			posx--;
		}
		else 
		{
			posx = X_TILE_COUNT-1;
		}
		select_tile(posx,posy);
		draw_changes();
	}	
	else
	{
		if (ingame_selector>0)
		{
			ingame_selector--;
		}
		else
		{
			ingame_selector = (PIKTOGRAMM_ARRAY_LENGTH-1);
		}
		draw_empty_tile(posx,posy);
		tile_memory[posx][posy] = ingame_selector;
		piktograms[ingame_selector](posx,posy);
		draw_changes();
	}
}
void ingame_click_right(void)
{
    if (!select_mode_enabled)
	{
		if (posx<(X_TILE_COUNT-1))
		{
			posx++;
		}
		else 
		{
			posx = 0;
		}

		select_tile(posx,posy);
		draw_changes();
	}	
	else
	{
		if (ingame_selector<(PIKTOGRAMM_ARRAY_LENGTH-1))
		{
			ingame_selector++;
		}
		else
		{
			ingame_selector = 0;
		}
		draw_empty_tile(posx,posy);
		tile_memory[posx][posy] = ingame_selector;
		piktograms[ingame_selector](posx,posy);
		draw_changes();
	}
}

void win_check()
{
	if (open_tiles_counter == ((X_TILE_COUNT*Y_TILE_COUNT)-board_mine_count))
	{
		win_flag = true;
		game_over();
	}
}