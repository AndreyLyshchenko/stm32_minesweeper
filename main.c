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