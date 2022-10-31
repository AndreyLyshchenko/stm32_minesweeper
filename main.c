#include <stdint.h>
#include <stm32f10x.h>
#include "StaticLib/delay.h"

int __attribute((noreturn)) main(void) {
	// Enable clock for AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	// Enable clock for GPIOC
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	// Enable PC13 push-pull mode
	GPIOC->CRH &= ~GPIO_CRH_CNF13; //clear cnf bits
	GPIOC->CRH |= GPIO_CRH_MODE13_0; //Max speed = 10Mhz

	//Setting up Port 14 into input pull-up mode 
	GPIOC->CRH &= ~GPIO_CRH_CNF14;
	GPIOC->CRH |= GPIO_CRH_CNF14_1;
	GPIOC->CRH &= ~GPIO_CRH_MODE14;
	//GPIOC->ODR &= ~GPIO_ODR_ODR14;
	GPIOC->ODR |= GPIO_ODR_ODR14;

	#define MIN(a,b) ((a)<(b)) ? (a):(b)
	#include <stdbool.h>

	uint32_t btnPeriod = 10000, ledPeriod = 1000000;
	uint32_t btnPhase = btnPeriod, ledPhase = ledPeriod;

	bool ledEnabled = true, buttonPrevState = GPIOC ->IDR & (1<<14);
	
	while(1){
		uint32_t tau = MIN(btnPhase,ledPhase);
		delay_us(tau);
		ledPhase -=tau;
		btnPhase -=tau;
		if (btnPhase == 0) {
			btnPhase = btnPeriod;
			bool buttonNewState = GPIOC -> IDR & (1<<14);
			if (!buttonNewState && buttonPrevState) {
				ledEnabled = !ledEnabled;
			}
			buttonPrevState = buttonNewState;
		}
		if (ledPhase == 0) {
			ledPhase = ledPeriod;
			if (ledEnabled) {
				uint32_t _gpios = GPIOC -> ODR;
				GPIOC -> BSRR = ((_gpios & (1<<13))<<16) | (~_gpios & (1<<13)); 
				ledEnabled;
			}
		}
	}
}
