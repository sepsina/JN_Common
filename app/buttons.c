/*
 * buttons.c
 *
 *  Created on: 18. lis 2022.
 *      Author: Sep
 */

#include "stm32_regs.h"
#include "stm32f1xx_ll_system.h"
#include "appTasks.h"
#include "stdbool.h"
#include "global.h"
#include "buttons.h"

static void cfg_buttons_led(void);
static void toggle_buttons_led(void);


void EXTI15_10_IRQHandler(void){

	exti_reg_t exti;
	uint32_t clear = 0;

	exti.pr.all = REG_Read(EXTI__PR);

	if(exti.pr.b.pr_12 == 1){
		clear |= (uint32_t)1 << 12;
		insertAppTask(toggle_buttons_led, 5);
		//toggle_buttons_led();
	}
	if(exti.pr.b.pr_13 == 1){
		clear |= (uint32_t)1 << 13;
		insertAppTask(toggle_buttons_led, 5);
		//toggle_buttons_led();
	}
	if(exti.pr.b.pr_14 == 1){
		clear |= (uint32_t)1 << 14;
		insertAppTask(toggle_buttons_led, 5);
		//toggle_buttons_led();
	}

	REG_Write(EXTI__PR, clear);
}

/****************************************************************************
 * initButtons
 *
 * DESCRIPTION:
 *
 */
void initButtons(void) {

	afio_reg_t afio;
	exti_reg_t exti;

	// Buttons GPIO Configuration
	// SW1  ---> PB12
	// SW2  ---> PB13
	// SW3  ---> PB14

	afio.exticr4.all = REG_Read(AFIO__EXTICR4);
	afio.exticr4.b.exti12 = 1; // 0001: PB[12] pin
	afio.exticr4.b.exti13 = 1; // 0001: PB[13] pin
	afio.exticr4.b.exti14 = 1; // 0001: PB[14] pin
	REG_Write(AFIO__EXTICR4, afio.exticr4.all);

	exti.rtsr.all = REG_Read(EXTI__RTSR);
	exti.rtsr.b.tr_12 = 1; // 1: Rising trigger enabled for input line.
	exti.rtsr.b.tr_13 = 1; // 1: Rising trigger enabled for input line.
	exti.rtsr.b.tr_14 = 1; // 1: Rising trigger enabled for input line.
	REG_Write(EXTI__RTSR, exti.rtsr.all);

	exti.imr.all = REG_Read(EXTI__IMR);
	exti.imr.b.mr_12 = 1; // 1: Interrupt request from Line 1 is not masked
	exti.imr.b.mr_13 = 1; // 1: Interrupt request from Line 1 is not masked
	exti.imr.b.mr_14 = 1; // 1: Interrupt request from Line 1 is not masked
	REG_Write(EXTI__IMR, exti.imr.all);

	cfg_buttons_led();
}

/****************************************************************************
 * cfg_led
 *
 * DESCRIPTION:
 *
 */
static void cfg_buttons_led(void) {

	gpio_reg_t gpio;

	// PB15   ------> buttons led
	gpio.crh.all = REG_Read(GPIOB__CRH);
	gpio.crh.b.cnf_15   = 1; // 01: General purpose output Open-drain
	gpio.crh.b.mode_15  = 2; // 10: Output mode, max speed 2 MHz
	REG_Write(GPIOB__CRH, gpio.crh.all);

	gpio.bsrr.all = 0;
	gpio.bsrr.b.bs_15 = 1;
	REG_Write(GPIOB__BSRR, gpio.bsrr.all);
}

/****************************************************************************
 * toggleLED
 *
 * DESCRIPTION:
 *
 */
static void toggle_buttons_led(void) {

	gpio_reg_t gpio;

    gpio.odr.all = REG_Read(GPIOB__ODR);
    if(gpio.odr.b.odr_15 == 1){
    	gpio.bsrr.all = 0;
		gpio.bsrr.b.br_15 = 1;
    }
    else {
    	gpio.bsrr.all = 0;
    	gpio.bsrr.b.bs_15 = 1;
    }
    REG_Write(GPIOB__BSRR, gpio.bsrr.all);
}
