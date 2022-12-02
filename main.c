#include <stdint.h>
#include <stm32f10x.h>
#include "StaticLib/delay.h"
#include "StaticLib/buttons.h"
#include <stdbool.h>
#include "StaticLib/spi.h"
#include "StaticLib/display.h"
#include "StaticLib/configuration.h"
#include "StaticLib/game.h"




extern uint8_t Bit_map[128][8];
extern uint8_t Board[128][8];
extern uint8_t tile_check_flag;
int posx;
int posy;
uint8_t selector;
bool select_mode_enabled; 
extern bool game_started;
extern void (*piktograms[5])(uint8_t,uint8_t);
extern uint8_t mine_field[X_TILE_COUNT][Y_TILE_COUNT];
extern uint8_t how_many_mines_around[X_TILE_COUNT][Y_TILE_COUNT];
extern uint8_t tile_memory[X_TILE_COUNT][Y_TILE_COUNT];
extern uint8_t menu_title_map[128*8];


int __attribute((noreturn)) main(void)
{
	preconfigure_microcontroller();
	preconfigure_SPI();
	select_mode_enabled = false;


	
	//run_main_menu();
	start_game();
			
	while (1)
	{
		/* code */
	}
}

/// @brief Update interrupt handler
void TIM2_IRQHandler(void)
{
	if (TIM2->SR & TIM_SR_UIF) // True if Update Interrupt Flag is set
	{
		if (select_mode_enabled) 
		{
			select_mode(posx,posy); 
		}
		TIM2->SR &= ~TIM_SR_UIF; // Clearing UIF flag
	}

}

void ButtonClick_A_8_Down() //mid
{
	if (game_started)
	{
		ingame_click_mid();
	}
	else
	{
		menu_click_mid();
	}	
}

void ButtonClick_B_12_Down() //up
{	
	if (game_started)
	{
		ingame_click_up();
	}
	else
	{
		menu_click_up();
	}	
}

void ButtonClick_B_13_Down() //down
{	
	if (game_started)
	{
		ingame_click_down();
	}
	else
	{
		menu_click_down();
	}	
}
void ButtonClick_B_14_Down() //left
{	
	if (game_started)
	{
		ingame_click_left();
	}
	else
	{
		menu_click_left();
	}	
}
void ButtonClick_B_15_Down() //right
{	
	if (game_started)
	{
		ingame_click_right();
	}
	else
	{
		menu_click_right();
	}
}

