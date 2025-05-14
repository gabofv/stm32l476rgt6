/*
 *************************************************************************************
 * @file           : adc.c
 * @author         : Gabriel Vasquez
 * @brief          : Src file for ADC driver (ADC1, Ch1, continuous) for PC0/A5
 *************************************************************************************
 */

#include "adc.h"
#include "systick.h"
#include <stdio.h>


/* RCC */
#define GPIOCEN        		(1U<<2)
#define ADCEN          		(1U<<13)

/* ADC */
#define ISR_EOC        		(1U<<2)
#define ISR_ADRDY      		(1U<<0)
#define CR_ADCAL       		(1U<<31)
#define CR_ADCALDIF		(1U<<30)
#define CR_DEEPPWD		(1U<<29)
#define CR_ADVREGEN		(1U<<28)
#define CR_ADSTP		(1U<<4)
#define CR_ADSTART		(1U<<2)
#define CR_ADEN			(1U<<0)
#define CFGR_CONT		(1U<<13)
#define SQR1_SQ1_CH1	 	(1U<<6)
#define SQR1_L			(0x00)

#define tADCVREG_STUP	 	20


void pc0_adc_init(void) {
	/* Enable clock for GPIOC peripheral */
	RCC->AHB2ENR |= GPIOCEN;

	/* Config PC0 for analog mode */
	GPIOC->MODER |= (1U<<0);
	GPIOC->MODER |= (1U<<1);
	GPIOC->ASCR |= (1U<<0);

	/* Use SYSCLK for ADC clock */
	RCC->CCIPR |= (1U<<28);
	RCC->CCIPR |= (1U<<29);

	/* Enable clock for ADC peripheral */
	RCC->AHB2ENR |= ADCEN;

	/* Exit deep-power-down mode */
	ADC1->CR &= ~CR_DEEPPWD;
	/* Enable voltage regulator */
	ADC1->CR |= CR_ADVREGEN;
	systick_us_delay(tADCVREG_STUP);

	/* --------- Calibration -------- */
	ADC1->CR &= ~CR_ADCALDIF;
	ADC1->CR |= CR_ADCAL;

	while (ADC1->CR & CR_ADCAL) {}
	/* ------------------------------ */

	/* ---------- Enable ADC ----------*/
	ADC1->ISR = ISR_ADRDY;
	ADC1->CR |= CR_ADEN;

	while (!(ADC1->ISR & ISR_ADRDY)) {}

	/* ACK */
	ADC1->ISR = ISR_ADRDY;
	/* --------------------------------*/

	/* Set conversion sequence */
	ADC1->SQR1 |= SQR1_SQ1_CH1;
	ADC1->SQR1 |= SQR1_L;

	ADC1->SMPR1 |= (1U<<3);
	ADC1->SMPR1 |= (1U<<4);
	ADC1->SMPR1 |= (1U<<5);

	/* Consult 18.4.6 - rm0351 for additional power saving strategies */
}

void pc0_start_conv(void) {
	ADC1->CFGR |= CFGR_CONT;

	/* Enables overwrite-on-overrun - DMA coming soon */
	ADC1->CFGR |= CFGR_OVRMOD;
	
	ADC1->CR |= CR_ADSTART;
}

uint32_t pc0_adc_rd(void) {
	while (!(ADC1->ISR & ISR_EOC)) {}
	return (ADC1->DR);
}
