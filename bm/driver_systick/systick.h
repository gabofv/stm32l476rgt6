/*
 *************************************************************************************
 * @file           : uart.h
 * @author         : Gabriel Vasquez
 * @brief          : Header file for SysTick driver
 *************************************************************************************
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include <stm32l4xx.h>

void systick_ms_delay(uint32_t delay);
void systick_us_delay(uint32_t delay);

#endif /* SYSTICK_H_ */
