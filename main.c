#include <stdint.h>
#include <stm32f10x.h>
#include "StaticLib/delay.h"
#include <stdbool.h>

bool ToggleLED; // Adding global variable, which control LED light toggling

int __attribute((noreturn)) main(void) {
	//ENABLING CLOCKS
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 	// Enabling clock for AFIO
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		// Enabling clock for GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 	// Enabling clock for GPIOC
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 	// Enabling clock for TIM2
	
	//CONFIGURING IO PORTS
	GPIOC->CRH &= ~GPIO_CRH_CNF13; 			// Setting up port C13 in push-pull output mode
	GPIOC->CRH |= GPIO_CRH_MODE13_0; 		//
	
	GPIOC->CRH &= ~GPIO_CRH_CNF14;			// Setting up port C14 in input pull-up mode 
	GPIOC->CRH |= GPIO_CRH_CNF14_1;			//
	GPIOC->CRH &= ~GPIO_CRH_MODE14;			//
	GPIOC->ODR |= GPIO_ODR_ODR14;			//

	GPIOA->CRL &= ~GPIO_CRL_CNF1;			// Setting up port A1 in input pull-up mode
	GPIOA->CRL |= GPIO_CRL_CNF1_1;			//
	GPIOA->CRL &= ~GPIO_CRL_MODE1;			//
	GPIOA->ODR |= GPIO_ODR_ODR1;			//

	GPIOA->CRL &= ~GPIO_CRL_CNF2;			// Setting up port A2 in input pull-up mode
	GPIOA->CRL |= GPIO_CRL_CNF2_1;			//	
	GPIOA->CRL &= ~GPIO_CRL_MODE2;			//
	GPIOA->ODR |= GPIO_ODR_ODR2;			//

	//CONFIGURING TIMER TIM2
	RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST; 	// Reseting TIM2
	RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST; //
	TIM2->PSC = 35999; 						// Editing prescaler value (1-65536) to configure timer frequency
	TIM2->ARR = 1000;						// Editing TIM2 reload value (count to X number)
	TIM2->DIER |=TIM_DIER_UIE;				// Enabling "Update" interrupt
	NVIC_ClearPendingIRQ(TIM2_IRQn);		// Clearing pending interuptions for TIM2 ???
	NVIC_EnableIRQ(TIM2_IRQn);				// Enabling interuptions from TIM2 
	TIM2->CR1 |= TIM_CR1_CEN;				// Enabling counter

	//BODY

	ToggleLED = false;
	GPIOC->ODR |= 1<<13;

	while (true)
	{

		bool Mid_state = GPIOC->IDR & (1<<14);
		if(!Mid_state){
			ToggleLED = !ToggleLED;
			while (!Mid_state)
			{
				Mid_state = GPIOC->IDR & (1<<14);
				delay_us(333);
			}
			
		}
		bool Up_state = GPIOA->IDR & (1<<1);
		if (!Up_state)
		{
			ToggleLED = !ToggleLED;
			while (!Up_state)
			{
				Up_state = GPIOA->IDR & (1<<1);
				delay_us(333);
			}
			
		}

		bool Down_state = GPIOA->IDR & (1<<2);
		if (!Down_state)
		{
			ToggleLED = !ToggleLED;
			while (!Down_state)
			{
				Down_state = GPIOA->IDR & (1<<2);
				delay_us(333);
			}
			
		}
		
		
		#if 0
		if (~_IC & GPIO_IDR_IDR14)
		{
			ToggleLED = !ToggleLED; // Enabling or disabling LED light toggling 
		} 
			else if (~_IA & GPIO_IDR_IDR1)
			{
				if (TIM2->ARR < 64000) {
					TIM2->ARR += 1000;
				}
			} 
				else if (~_IA & GPIO_IDR_IDR2)
				{
					if (TIM2->ARR > 2000) {
					TIM2->ARR -= 1000;
				}
				}
		#endif		
		delay_us(333);
	}

}
void TIM2_IRQHandler(void) {
	if (TIM2->SR & TIM_SR_UIF) 	// True if Update Interrupt Flag is set
	{
		if (ToggleLED)
		{
			uint32_t _gpios = GPIOC -> ODR;
			GPIOC -> BSRR = ((_gpios & (1<<13))<<16) | (~_gpios & (1<<13)); // Toggling LED light
		}
		TIM2->SR &= ~TIM_SR_UIF; // Clearing UIF flag	
	}
	
}