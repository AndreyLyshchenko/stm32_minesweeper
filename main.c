#include <stdint.h>
#include <stm32f10x.h>

void delay(uint32_t ticks) {
	for (int i=0; i<ticks; i++) {
		__NOP();
	}
}

int __attribute((noreturn)) main(void) {
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	// Enable PC13 push-pull mode
	GPIOB->CRH &= ~GPIO_CRH_CNF10; 
	GPIOB->CRH |= GPIO_CRH_CNF10_1; 

	GPIOB -> CRH &= ~GPIO_CRH_MODE10;
	GPIOB -> CRH |= ~GPIO_CRH_MODE10_0;

	GPIOB->CRH &= ~GPIO_CRH_CNF11; 
	GPIOB->CRH |= GPIO_CRH_CNF11_1; 
	GPIOB -> CRH |= ~GPIO_CRH_MODE11;

	GPIOB->ODR |=GPIO_ODR_ODR11;

	USART3->BRR = (1875<<4);
	USART3->CR1 |= USART_CR1_UE;
	USART3->CR1 |= USART_CR1_TE;
	USART3->CR1 |= USART_CR1_RE;

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~GPIO_CRH_CNF13;
	GPIOC->CRH |= GPIO_CRH_MODE13_0;

	while (1)
	{
		GPIOC->ODR |= (1U<<13U);
		delay(100000);
		GPIOC->ODR &= ~(1U<<13U);
		USART3 ->DR = 'D';
		delay(100000);
	}
}
