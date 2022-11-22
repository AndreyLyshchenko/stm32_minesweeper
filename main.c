#include <stdint.h>
#include <stm32f10x.h>
#include "StaticLib/delay.h"
#include "StaticLib/buttons.h"
#include <stdbool.h>
#include "StaticLib/spi.h"
#include "StaticLib/display.h"

void cmd(uint8_t data);
void dat(uint8_t data);
extern uint8_t Bit_map[128][8];



bool ToggleLED; // Adding global variable, which control LED light toggling

int __attribute((noreturn)) main(void)
{
	// ENABLING CLOCKS
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // Enabling clock for AFIO
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enabling clock for GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enabling clock for GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enabling clock for GPIOC
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enabling clock for TIM2

	// CONFIGURING IO PORTS
	GPIOC->CRH &= ~GPIO_CRH_CNF13;	 // Setting up port C13 in push-pull output mode
	GPIOC->CRH |= GPIO_CRH_MODE13_0; //

	GPIOC->CRH &= ~GPIO_CRH_CNF14;	// Setting up port C14 in input pull-up mode
	GPIOC->CRH |= GPIO_CRH_CNF14_1; //
	GPIOC->CRH &= ~GPIO_CRH_MODE14; //
	GPIOC->ODR |= GPIO_ODR_ODR14;	//

	GPIOB->CRH &= ~GPIO_CRH_CNF10;  // Setting up port B10 in input pull-up mode
	GPIOB->CRH |= GPIO_CRH_CNF10_1; //	
	GPIOB->CRH &= ~GPIO_CRH_MODE10; //
	GPIOB->ODR |= GPIO_ODR_ODR10;   //

	GPIOB->CRH &= ~GPIO_CRH_CNF11;  // Setting up port B11 in input pull-up mode
	GPIOB->CRH |= GPIO_CRH_CNF11_1; //	
	GPIOB->CRH &= ~GPIO_CRH_MODE11; //
	GPIOB->ODR |= GPIO_ODR_ODR11;   //

	// CONFIGURING TIMER TIM2
	RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;	// Reseting TIM2
	RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST; //
	TIM2->PSC = 999U;							// Editing prescaler value (1-65536) to configure timer frequency
	TIM2->ARR = 1000;						// Editing TIM2 reload value (count to X number)
	TIM2->CCR1 = 500U;
	TIM2->DIER |= TIM_DIER_UIE | TIM_DIER_CC1IE; // Enabling "Update" interrupt
	NVIC_ClearPendingIRQ(TIM2_IRQn);			 // Clearing pending interuptions for TIM2 ???
	NVIC_EnableIRQ(TIM2_IRQn);					 // Enabling interuptions from TIM2
	TIM2->CR1 |= TIM_CR1_CEN;					 // Enabling counter

	// BODY

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
		//display_fill(0b11111111);
		put_pixel(0,0,1);
		put_pixel(0,63,1);
		put_pixel(127,0,1);
		put_pixel(127,63,1);


#if 0
		GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
		for (uint8_t i = 0; i < 1; i++)
		{
			GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

			SPI1_Write(0xB0|i);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

			SPI1_Write(0x10|0b0000);				// Seting column upper bit
			SPI1_Write(0x00|0b0000);			// Seting column lower bit 
			while (SPI1->SR & SPI_SR_BSY);

		//	for(uint8_t j = 0; j < 132; j++)
			{
				GPIOA->BSRR = GPIO_ODR_ODR3; // Selecting sending of data
				SPI1_Write(0b00000001);			 // Turning off pixels
				while (SPI1->SR & SPI_SR_BSY);
			}
		}
		GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection
#endif
		// All "button press" events organized in hierarchial order because of their mutual exclusiveness
		// MID BUTTON - first priority - toggling LED light

		// Function BtnCLick is triggering Click event, according to its input data:
		// Port, Pin, ClickMode(OnPress -"D", OnRelease - "U", While holding -"H"), 
		// Defalut delay (for "D" and "U" mode) and Hold delay (for "H" mode).
		// Integer, returned by function, provides information about internal errors.
		// ErrCodes 7,8,9 are indicating successfull event generatin after corresponding button was pressed,
		// 0 - corresponding button was not pressed.

		while (1)
		{
			if (BtnClick('C',14,'D',333,10000)==7)
			{

			}
			// UP BUTTON - second priority - increasing LED brightness
			else if (BtnClick('B',10,'D',333,10000)==7)
				{

				}
				// DOWN BUTTON - third priority - decreacing LED brightness
				else if (BtnClick('B',11,'D',333,10000)==7)
					{

					}
					// NOTHING HAPPEND
					else
					{
						delay_us(333);
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

void ButtonClick_C_14_Down()
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

void ButtonClick_B_10_Down()
{	
	// Increacing LED brightness
	if (TIM2 -> CCR1 < 1000) 
	{
		TIM2->CCR1 +=100;
	}

}

void ButtonClick_B_11_Down()
{	
	// Decreacing LED brightness
	if (TIM2 -> CCR1 > 100) 
	{
		TIM2->CCR1 -=100;
	}

}