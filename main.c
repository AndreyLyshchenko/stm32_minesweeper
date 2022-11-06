#include <stdint.h>
#include <stm32f10x.h>
#include "StaticLib/delay.h"
#include "StaticLib/buttons.h"
#include <stdbool.h>

bool ToggleLED; // Adding global variable, which control LED light toggling

int __attribute((noreturn)) main(void)
{
	// ENABLING CLOCKS
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // Enabling clock for AFIO
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enabling clock for GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enabling clock for GPIOC
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enabling clock for TIM2

	// CONFIGURING IO PORTS
	GPIOC->CRH &= ~GPIO_CRH_CNF13;	 // Setting up port C13 in push-pull output mode
	GPIOC->CRH |= GPIO_CRH_MODE13_0; //

	GPIOC->CRH &= ~GPIO_CRH_CNF14;	// Setting up port C14 in input pull-up mode
	GPIOC->CRH |= GPIO_CRH_CNF14_1; //
	GPIOC->CRH &= ~GPIO_CRH_MODE14; //
	GPIOC->ODR |= GPIO_ODR_ODR14;	//

	GPIOA->CRL &= ~GPIO_CRL_CNF1;  // Setting up port A1 in input pull-up mode
	GPIOA->CRL |= GPIO_CRL_CNF1_1; //
	GPIOA->CRL &= ~GPIO_CRL_MODE1; //
	GPIOA->ODR |= GPIO_ODR_ODR1;   //

	GPIOA->CRL &= ~GPIO_CRL_CNF2;  // Setting up port A2 in input pull-up mode
	GPIOA->CRL |= GPIO_CRL_CNF2_1; //
	GPIOA->CRL &= ~GPIO_CRL_MODE2; //
	GPIOA->ODR |= GPIO_ODR_ODR2;   //

	// CONFIGURING TIMER TIM2
	RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;	// Reseting TIM2
	RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST; //
	TIM2->PSC = 1U;							// Editing prescaler value (1-65536) to configure timer frequency
	TIM2->ARR = 4000U;						// Editing TIM2 reload value (count to X number)
	TIM2->CCR1 = 1000U;
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
		// All "button press" events organized in hierarchial order because of their mutual exclusiveness
		// MID BUTTON - first priority - enabling/disabling LED light toggling

		Mid_state = GPIOC->IDR & (1 << 14);
		if (!Mid_state)
		{
			ToggleLED = !ToggleLED; // Enabling / disabling LED light toggling
			while (!Mid_state)		// Waiting until button is released to prevent stucking
			{
				Mid_state = GPIOC->IDR & (1 << 14);
				delay_us(333);
			}
		}
		// UP BUTTON - second priority - decreasing frequency
		else
		{
			#if 0
			Current_PSC_value = TIM2->PSC;
			Up_state = GPIOA->IDR & (1 << 1);
			if (!Up_state)
			{
				/*if (Current_PSC_value < 57000U) { //Preventing overstacking
						TIM2->PSC += 8000U;	//Decreasing frequency
					}*/
				// TIM2->CCR1=2000;
				// TIM2->DIER|=0;
				TIM2->CCR1 += 1000;
				while (!Up_state)
				{
					Up_state = GPIOA->IDR & (1 << 1);
					delay_us(333);
				}
				
			}
			#endif
			if (BtnClick('A',1,'D',333,10000)==7)
			{
				/* code */
			}
			
			// DOWN BUTTON - third priority - increacing frequency
			else
			{	
				#if 0
				Down_state = GPIOA->IDR & (1 << 2);
				if (!Down_state)
				{
					/*if (Current_PSC_value > 8000U) {
							TIM2->PSC -= 8000U; //Increasing frequency
						} */
					TIM2->CCR1 -= 1000;
					while (!Down_state)
					{
						Down_state = GPIOA->IDR & (1 << 2);
						delay_us(333);
					}
					
				}
				#endif
				if (BtnClick('A',2,'D',300,10000)==7)
				{
					/* code */
				}
				
				// NOTHING HAPPEND
				else
				{
					delay_us(333);
				}
			}
		}
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM2->SR & TIM_SR_UIF) // True if Update Interrupt Flag is set
	{
		if (1)
		{
			uint32_t _gpios = GPIOC->ODR;
			GPIOC->BSRR = (~_gpios & (1 << 13)); // Toggling LED light
		}
		TIM2->SR &= ~TIM_SR_UIF; // Clearing UIF flag
	}
	if (TIM2->SR & TIM_SR_CC1IF)
	{

		uint32_t _gpios = GPIOC->ODR;
		GPIOC->BSRR = ((_gpios & (1 << 13)) << 16); // Toggling LED light
		TIM2->SR &= ~TIM_SR_CC1IF;
	}
}

void ButtonClick_A_1_Down()
{
	TIM2->CCR1 += 1000;
}

void ButtonClick_A_2_Down()
{
	TIM2->CCR1 -= 1000;
}