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
void inicialize_click_funktions_array();

int __attribute((noreturn)) main(void)
{
	inicialize_click_funktions_array();
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

void (*click_function[15])();

void inicialize_click_funktions_array()
{
	click_function[0] = end_dialog_click_mid;
	click_function[1] = ingame_click_mid;
	click_function[2] = menu_click_mid;

	click_function[3] = end_dialog_click_up;
	click_function[4] = ingame_click_up;
	click_function[5] = menu_click_up;
	
	click_function[6] = end_dialog_click_down;
	click_function[7] = ingame_click_down;
	click_function[8] = menu_click_down;

	click_function[9] = end_dialog_click_left;
	click_function[10] = ingame_click_left;
	click_function[11] = menu_click_left;

	click_function[12] = end_dialog_click_right;
	click_function[13] = ingame_click_right;
	click_function[14] = menu_click_right;
}

void use_click_function(uint8_t pressed_button)
{
	if (game_started)
	{
		if (ending_dialog)
		{
			// End dialog
			click_function[pressed_button]();
		}
		else
		{
			// Ingame
			click_function[pressed_button+1]();
		}
	}
	else
	{
		// Menu
		click_function[pressed_button+2]();
	}
}

void ButtonClick_A_8_Down() //mid
{
	use_click_function(CLICK_MID);
}

void ButtonClick_B_12_Down() //up
{	
	use_click_function(CLICK_UP);
}

void ButtonClick_B_13_Down() //down
{	
	use_click_function(CLICK_DOWN);
}
void ButtonClick_B_14_Down() //left
{	
	use_click_function(CLICK_LEFT);
}
void ButtonClick_B_15_Down() //right
{	
	use_click_function(CLICK_RIGHT);
}

