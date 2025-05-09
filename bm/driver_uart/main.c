/*
 *************************************************************************************
 * @file           : main.c
 * @author         : Gabriel Vasquez
 * @brief          : Main function to test uart comm w/ Realterm
 *************************************************************************************
 */

#include <stdio.h>
#include "uart.h"


int main(void) {

	uart_init();
	while(1)
		printf("hello from stm32\r\n");

	return 0;
}
