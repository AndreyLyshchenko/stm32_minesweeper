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
void toggle_led(void);
static int  posx;
static int posy;
bool select_mode_enabled; 

void dummy(uint8_t x_number, uint8_t y_number);


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

		display_fill(0x00);
		draw_board();
		copy_map(Board,Bit_map);
		//draw_question_mark(0,0);
		//draw_flag(0,0);
		select_tile(0,0);
		draw_changes();


		posx=0;
		posy=0;
		


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
		draw_changes();
		copy_map(Board,Bit_map);
		select_tile(posx,posy);
		
	} else
	{
		draw_flag(posx,posy);
	}
	select_mode_enabled = !select_mode_enabled;


}

void ButtonClick_B_12_Down() //up
{	
	if (!select_mode_enabled)
	{
		posy--;
		select_tile(posx,posy);
	}
}

void ButtonClick_B_13_Down() //down
{	
	if (!select_mode_enabled)
	{
		posy++;
		select_tile(posx,posy);
	}	
}
void ButtonClick_B_14_Down() //left
{	
	if (!select_mode_enabled)
	{
		posx--;
		select_tile(posx,posy);
	}	
	else
	{
		draw_empty_tile(posx,posy);
		draw_changes();
	}
}
void ButtonClick_B_15_Down() //right
{	
	if (!select_mode_enabled)
	{
		posx++;
		select_tile(posx,posy);
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

void dummy(uint8_t x_number, uint8_t y_number)
{
	static int color =0;
    rectangle(
        BOARD_START_X + (TILE_SIDE * x_number),
        BOARD_START_Y + (TILE_SIDE * y_number),
        BOARD_START_X + (TILE_SIDE * (x_number+1)-1),
        BOARD_START_Y + (TILE_SIDE * (y_number+1)-1),
    !color,3,VIRTUAL);

    rectangle(
        BOARD_START_X+(TILE_SIDE * x_number)+1,
        BOARD_START_Y+(TILE_SIDE * y_number)+1,
        BOARD_START_X+(TILE_SIDE * (x_number+1)-2),
        BOARD_START_Y+(TILE_SIDE * (y_number+1)-2),
    color,3,VIRTUAL);
	color = !color;
	//delay_us(10000);
}
