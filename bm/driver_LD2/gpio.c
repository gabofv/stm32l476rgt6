/**
 ***************************************************************************************
 * @file           : gpio.c
 * @author         : Gabriel Vasquez
 * @brief          : Complete blinking LED driver (LD2) using CMSIS uC-specific library
 ***************************************************************************************
 */

#include "gpio.h"

#define GPIOAEN		(1U<<0)
#define LEDPIN5		(1U<<5)
#define LD2_BS		(1U<<5)
#define LD2_BR		(1U<<(5+16))

#define DELAY_COUNT 50000

int main(void) {

	ld2_init();

	while(1) {
		ld2_on();
		for (uint32_t i = 0; i < DELAY_COUNT; i++) {}
		ld2_off();
		for (uint32_t i = 0; i < DELAY_COUNT; i++) {}
	}

	return 0;
}

void ld2_init(void) {
	/* Enable clock */
	RCC->AHB2ENR |= GPIOAEN;

	/* Set GPIOA to only output mode */
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
}

void ld2_on(void) {
	GPIOA->BSRR |= LD2_BS;
}

void ld2_off(void) {
	GPIOA->BSRR |= LD2_BR;
}
