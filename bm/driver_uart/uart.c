/*
 *************************************************************************************
 * @file           : uart.c
 * @author         : Gabriel Vasquez
 * @brief          : Src file for UART driver (USART2)
 *************************************************************************************
 */

#include "uart.h"

/* RCC */
#define GPIOAEN				(1U<<0)
#define USART2EN			(1U<<17)

/* USART */
#define CR1_UE				(1U<<0)
#define CR1_TE				(1U<<3)
#define ISR_TXE				(1U<<7)

/* Other */
#define DBG_UART_BAUDRATE		115200
#define SYS_FREQ			4000000
#define APB1_CLK			SYS_FREQ


static uint16_t compute_uart_baudr(uint32_t periph_clk, uint32_t br);
static void uart_set_baudr(uint32_t periph_clk, uint32_t br);
static void uart_wr(int c);


int __io_putchar(int c) {
	uart_wr(c);
	return c;
}

void uart_init(void) {
	/* Enable clock for GPIOA (has PA2) */
	RCC->AHB2ENR |= GPIOAEN;

  	/* Set PA2 as alternate function */
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

  	/* Set alternate function to USART2 */
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/* Enable clock for USART2 registers */
	RCC->APB1ENR1 |= USART2EN;

  	/* Config baud rate */
	uart_set_baudr(APB1_CLK, DBG_UART_BAUDRATE);

	/* Enable transmitter */
	USART2->CR1 = CR1_TE;
	/* Enable USART */
	USART2->CR1 |= CR1_UE;
}

static void uart_wr(int c) {
	/* Wait until tx is empty */
	while(!(USART2->ISR & ISR_TXE)) {}
	USART2->TDR = (c & 0xFF);
}

static uint16_t compute_uart_baudr(uint32_t periph_clk, uint32_t br) {
	/* Add half of divisor to numerator to apply round-to-nearest */
	/* Formula valid when OVER8 = 0 */
	return (uint16_t) ((periph_clk + (br / 2U)) / br);
}

static void uart_set_baudr(uint32_t periph_clk, uint32_t br) {
	USART2->BRR = compute_uart_baudr(periph_clk, br);
}
