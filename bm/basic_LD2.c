/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Gabriel Vasquez
 * @brief          : Turn ON LD2 on the board
 ******************************************************************************
 */

#include <stdint.h>


#define PERIPH_BASE			(0x40000000UL)

/* -- Common offsets for ports --------- */
#define MODER_OFFSET  		(0x0UL)
#define RCC_OFFSET			(0x21000UL)
#define GPIOA_ODR_OFFSET 	(0x14UL)
/* ------------------------------------- */

#define AHB2_OFFSET 		(0x8000000UL)
#define AHB2_BASE 			(PERIPH_BASE + AHB2_OFFSET)		// 1kB

#define GPIOA_OFFSET		(0x0UL)
#define GPIOA_BASE			(AHB2_BASE + GPIOA_OFFSET)
#define GPIOA_MODE_R 		(*(volatile unsigned int *) (GPIOA_BASE + MODER_OFFSET))
#define GPIOA_OD_R 			(*(volatile unsigned int *) (GPIOA_BASE + GPIOA_ODR_OFFSET))

#define RCC_BASE 			(PERIPH_BASE + RCC_OFFSET)		// 1kB
#define RCC_AHB2ENR_OFFSET 	(0x4CUL)
#define RCC_AHB2ENR_R		( *(volatile unsigned int *) (RCC_BASE + RCC_AHB2ENR_OFFSET))

#define GPIOAEN				(1U<<0)
#define LED_PIN5			(1U<<5)


int main(void)
{

	// Enable Reset & Control Clock for Port A
	RCC_AHB2ENR_R |= GPIOAEN;

	// Set pin 5 to output mode
	GPIOA_MODE_R |= (1U<<10);		// MODER5 bit 10
	GPIOA_MODE_R &= ~(1U<<11);		// MODER5 bit 11

	while (1)
		GPIOA_OD_R |= LED_PIN5;

	return 0;
}
