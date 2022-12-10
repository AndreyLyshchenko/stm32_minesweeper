#include <stdint.h>
#include <stm32f10x.h>
#include <stdbool.h>
#include "StaticLib/delay.h"
#include "StaticLib/buttons.h"
#include "StaticLib/spi.h"
#include "StaticLib/configuration.h"
#include "StaticLib/logic.h"


int posx;
int posy;
bool select_mode_enabled;
bool terminator; 


int __attribute((noreturn)) main(void)
{
	terminator = false;
	preconfigure_microcontroller();
	preconfigure_SPI();
	select_mode_enabled = false;
	
	while (1)
	{
		run_main_menu();
	}
}

/// @brief Update interrupt handler
void TIM2_IRQHandler(void)
{
	if (TIM2->SR & TIM_SR_UIF) // True if Update Interrupt Flag is set
	{
		if ((select_mode_enabled)&&(!now_drawing)) 
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
		if (ending_dialog)
		{
			end_dialog_click_mid();
		}
		else
		{
			ingame_click_mid();
		}
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
		if (ending_dialog)
		{
			end_dialog_click_up();
		}
		else
		{
			ingame_click_up();
		}
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
		if (ending_dialog)
		{
			end_dialog_click_down();
		}
		else
		{
			ingame_click_down();
		}
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
		if (ending_dialog)
		{
			end_dialog_click_left();
		}
		else
		{
			ingame_click_left();
		}
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
		if (ending_dialog)
		{
			end_dialog_click_right();
		}
		else
		{
			ingame_click_right();
		}
	}
	else
	{
		menu_click_right();
	}
}

