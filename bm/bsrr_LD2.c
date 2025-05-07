/**
 ******************************************************************************
 * @file           : bsrr_LD2.c
 * @author         : Gabriel Vasquez
 * @brief          : Improved version of basic_LD2.c (uses GPIOx_BSRR)
 ******************************************************************************
 */

#include <stdint.h>


#define PERIPH_BASE		(0x40000000UL)

/* -- Common offsets for GPIO ports --------- */
#define MODER_OFFSET  		(0x0UL)
#define RCC_OFFSET		(0x21000UL)
// #define ODR_OFFSET 		(0x14UL)
#define BSRR_OFFSET 		(0x18UL)
/* ------------------------------------- */

#define AHB2_OFFSET 		(0x8000000UL)
#define AHB2_BASE 		(PERIPH_BASE + AHB2_OFFSET)		/* 1kB */

#define GPIOA_OFFSET		(0x0UL)
#define GPIOA_BASE		(AHB2_BASE + GPIOA_OFFSET)
#define GPIOA_MODE_R 		(*(volatile uint32_t *) (GPIOA_BASE + MODER_OFFSET))
// #define GPIOA_OD_R 		(*(volatile uint32_t *) (GPIOA_BASE + ODR_OFFSET))
#define GPIOA_BSR_R		(*(volatile uint32_t *) (GPIOA_BASE + BSRR_OFFSET))

#define RCC_BASE 		(PERIPH_BASE + RCC_OFFSET)		/* 1kB */
#define RCC_AHB2ENR_OFFSET 	(0x4CUL)
#define RCC_AHB2ENR_R		( *(volatile uint32_t *) (RCC_BASE + RCC_AHB2ENR_OFFSET))

#define GPIOAEN			(1U<<0)
#define LED_PIN5		(1U<<5)


int main(void) {

	/* Enable Reset & Control Clock for Port A */
	RCC_AHB2ENR_R |= GPIOAEN;

	/* Set pin 5 to output mode */
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &= ~(1U<<11);

	/* Set Output Data bit pin 5 (for LED) */
	while (1) {

		/* Less-efficient way */
		// GPIOA_OD_R ^= LED_PIN5;

		/* Efficient, atomic version */
		GPIOA_BSR_R |= (1U<<5);

		for(uint32_t i = 0; i < 50000; i++) {}

		GPIOA_BSR_R |= (1U<<(5+16));

		for(uint32_t i = 0; i < 50000; i++) {}
	}

	return 0;
}
