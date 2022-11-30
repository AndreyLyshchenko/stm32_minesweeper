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
void toggle_led(void);
int posx;
int posy;
uint8_t selector;
bool select_mode_enabled; 
extern void (*piktograms[5])(uint8_t,uint8_t);
extern uint8_t mine_field[X_TILE_COUNT][Y_TILE_COUNT];
extern uint8_t how_many_mines_around[X_TILE_COUNT][Y_TILE_COUNT];



bool ToggleLED; // Adding global variable, which control LED light toggling

int __attribute((noreturn)) main(void)
{
	enabling_clocks();
	configuring_ports();
	configuring_timers();


	ToggleLED = false;
	select_mode_enabled = false;
	GPIOC->ODR |= 1 << 13; // Disabling LED by default
	bool Mid_state, Up_state, Down_state;
	uint16_t Current_PSC_value;


	while (true)
	{
		SPI1_Init();
		SPI1_Preset();
		// 132x(8*8+1) declared
		// but 128x64 real
		posx=0;
		posy=0;
		display_fill(0x00);
		draw_board();
		copy_map(Board,Bit_map);
		select_tile(0,0);
		draw_changes();
		inicialise_piktogramm_array();
		selector = 0;

		spawn_mines(mine_field);
		calculate_how_many_mines_around(mine_field,how_many_mines_around);

		// All "button press" events organized in hierarchial order because of their mutual exclusiveness

		// Function BtnCLick is triggering Click event, according to its input data:
		// Port, Pin, ClickMode(OnPress -"D", OnRelease - "U", While holding -"H"), 
		// Defalut delay (for "D" and "U" mode) and Hold delay (for "H" mode).
		// Integer, returned by function, provides information about internal errors.
		// ErrCodes 7,8,9 are indicating successfull event generatin after corresponding button was pressed,
		// 0 - corresponding button was not pressed.

		while (1)
		{
			if (BtnClick('A',8,'D',10000,10000)==7){} // MID BUTTON	
			else if (BtnClick('B',12,'D',10000,10000)==7){} // UP BUTTON
				else if (BtnClick('B',13,'D',10000,10000)==7){} // DOWN BUTTON
					else if (BtnClick('B',14,'D',10000,10000)==7){} // LEFT BUTTON
						else if (BtnClick('B',15,'D',10000,10000)==7){} // RIGHT BUTTON
							else
							{
								delay_us(333); // NOTHING
							}
		}			
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
	if (select_mode_enabled)
	{
		draw_default_tile_borders(posx,posy);
		//draw_changes();
		copy_map(Board,Bit_map);
		load_map(Bit_map,Board);
		select_tile(posx,posy);

		if (tile_check_flag == 1)
		{
			if (how_many_mines_around[posx][posy]==9)
			{
				game_over();
			}
			else 
			{
				draw_empty_tile(posx,posy);
				draw_number(posx,posy,how_many_mines_around[posx][posy]);
				//delay_us(10000);
				//draw_changes();
				copy_map(Board,Bit_map);
				load_map(Bit_map,Board);
				select_tile(posx,posy);
				//draw_changes();
			}
		}
		
		
	} else
	{
		piktograms[selector](posx,posy);
	}
	select_mode_enabled = !select_mode_enabled;

}

void ButtonClick_B_12_Down() //up
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
	}
}

void ButtonClick_B_13_Down() //down
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
	}	
}
void ButtonClick_B_14_Down() //left
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
	}	
	else
	{
		if (selector>0)
		{
			selector--;
		}
		else
		{
			selector = (PIKTOGRAMM_ARRAY_LENGTH-1);
		}
		draw_empty_tile(posx,posy);
		piktograms[selector](posx,posy);
		draw_changes();
	}
}
void ButtonClick_B_15_Down() //right
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
	}	
	else
	{
		if (selector<(PIKTOGRAMM_ARRAY_LENGTH-1))
		{
			selector++;
		}
		else
		{
			selector = 0;
		}
		draw_empty_tile(posx,posy);
		piktograms[selector](posx,posy);
		draw_changes();
	}
}

void toggle_led()
{
	// ON/OFF LED light on MID button click
	ToggleLED = !ToggleLED;
	if (!ToggleLED) 
	{
		GPIOC-> BSRR =~GPIOC->ODR & (1<<13);
	} else
	{
		GPIOC-> BSRR = GPIOC->ODR & (1<<13)<<16;
	}
}
