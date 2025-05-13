/*
 *************************************************************************************
 * @file           : systick.c
 * @author         : Gabriel Vasquez
 * @brief          : Src file for SysTick (Timer in Arm Cortex-M processor)
 *************************************************************************************
 */

#include "systick.h"


#define CTRL_ENABLE			(1U<<0)
#define CTRL_CLKSOURCE		(1U<<2)
#define CTRL_COUNTFLAG		(1U<<16)

/* 1ms x 4MHz = 4000 ticks */
#define MS_LOAD			4000
/* 1us x 4MHz = 4 ticks    */
#define US_LOAD			4


static void systick_config();
static void systick_run(uint32_t delay);


void systick_ms_delay(uint32_t delay) {
	SysTick->LOAD = MS_LOAD - 1;
	systick_config();
	systick_run(delay);
}

void systick_us_delay(uint32_t delay) {
	SysTick->LOAD = US_LOAD - 1;
	systick_config();
	systick_run(delay);
}

static void systick_config() {
	SysTick->VAL = 0;

	/* Use processor's clock */
	SysTick->CTRL = CTRL_CLKSOURCE;
}

static void systick_run(uint32_t delay) {
	SysTick->CTRL |= CTRL_ENABLE;

	for (uint32_t i = 0; i < delay; i++) {
			while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {}
	}

	SysTick->CTRL = 0;
}
