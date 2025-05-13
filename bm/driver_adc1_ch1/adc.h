/*
 * adc.h
 *
 *  Created on: May 10, 2025
 *      Author: gabri
 */

#ifndef ADC_H_
#define ADC_H_

#include <stm32l4xx.h>
#include <stdint.h>

void pc0_adc_init(void);
void pc0_start_conv(void);
uint32_t pc0_adc_rd(void);

#endif /* ADC_H_ */
