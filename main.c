#include <stdint.h>
#include <stm32f10x.h>
#include "StaticLib/delay.h"
#include "StaticLib/buttons.h"
#include <stdbool.h>
#include "StaticLib/spi.h"
#include "StaticLib/display.h"
#include "StaticLib/configuration.h"


//void cmd(uint8_t data);
//void dat(uint8_t data);
extern uint8_t Bit_map[128][8];
void toggle_led(void);



bool ToggleLED; // Adding global variable, which control LED light toggling

int __attribute((noreturn)) main(void)
{
	enabling_clocks();
	configuring_ports();
	configuring_timers();


	ToggleLED = false;
	GPIOC->ODR |= 1 << 13; // Disabling LED by default
	bool Mid_state, Up_state, Down_state;
	uint16_t Current_PSC_value;

	while (true)
	{
		SPI1_Init();
		SPI1_Preset();
		// 132x(8*8+1) declared
		// but 128x64 real
		
		display_fill(0x00);
		put_pixel(0,0,1,VIRTUAL);
		put_pixel(0,63,1,VIRTUAL);
		put_pixel(127,0,1,VIRTUAL);
		put_pixel(127,63,1,VIRTUAL);
		draw_changes();

		// All "button press" events organized in hierarchial order because of their mutual exclusiveness

		// Function BtnCLick is triggering Click event, according to its input data:
		// Port, Pin, ClickMode(OnPress -"D", OnRelease - "U", While holding -"H"), 
		// Defalut delay (for "D" and "U" mode) and Hold delay (for "H" mode).
		// Integer, returned by function, provides information about internal errors.
		// ErrCodes 7,8,9 are indicating successfull event generatin after corresponding button was pressed,
		// 0 - corresponding button was not pressed.

		while (1)
		{
			if (BtnClick('A',8,'D',333,10000)==7){} // MID BUTTON	
			else if (BtnClick('B',12,'D',333,10000)==7){} // UP BUTTON
				else if (BtnClick('B',13,'D',333,10000)==7){} // DOWN BUTTON
					else if (BtnClick('B',14,'D',333,10000)==7){} // LEFT BUTTON
						else if (BtnClick('B',15,'D',333,10000)==7){} // RIGHT BUTTON
							else
							{
								delay_us(333); // NOTHING
							}
		}			
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM2->SR & TIM_SR_UIF) // True if Update Interrupt Flag is set
	{
		if (ToggleLED)
		{
			uint32_t _gpios = GPIOC->ODR;
			GPIOC->BSRR = (~_gpios & (1 << 13)); // Toggling LED light
		}
		TIM2->SR &= ~TIM_SR_UIF; // Clearing UIF flag
	}
	if (TIM2->SR & TIM_SR_CC1IF)
	{
		if (ToggleLED) 
		{
			uint32_t _gpios = GPIOC->ODR;
			GPIOC->BSRR = ((_gpios & (1 << 13)) << 16); // Toggling LED light
		}
		TIM2->SR &= ~TIM_SR_CC1IF; //Clearing Count compare interrupt flag
	}
}

void ButtonClick_A_8_Down()
{
	toggle_led();
}

void ButtonClick_B_12_Down()
{	
	toggle_led();
}

void ButtonClick_B_13_Down()
{	
	toggle_led();
}
void ButtonClick_B_14_Down()
{	
	toggle_led();
}
void ButtonClick_B_15_Down()
{	
	toggle_led();
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