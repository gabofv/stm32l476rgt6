/**
 ******************************************************************************
 * @file           : cmsis_LD2.c
 * @author         : Gabriel Vasquez
 * @brief          : LD2 blinking using CMSIS uC-specific library
 ******************************************************************************
 */

#include <stdint.h>
#include <stm32l4xx.h>

#define GPIOAEN		(1U<<0)
#define LEDPIN5		(1U<<5)

#define DELAY_COUNT 50000

int main(void) {

	/* Enable clock */
	RCC->AHB2ENR |= GPIOAEN;

	/* Set GPIOA to only output mode */
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	while(1) {
		GPIOA->BSRR |= (1U<<5);
		for (uint32_t i = 0; i < DELAY_COUNT; i++) {}
		GPIOA->BSRR |= (1U<<(5+16));
		for (uint32_t i = 0; i < DELAY_COUNT; i++) {}
	}

	return 0;
}
