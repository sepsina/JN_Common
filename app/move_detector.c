/*
 * move_detector.c
 *
 *  Created on: 18. lis 2022.
 *      Author: Sep
 */

#include "stm32_regs.h"
#include "stm32f1xx_ll_system.h"
#include "appTasks.h"
#include "stdbool.h"
#include "global.h"
#include "move_detector.h"

static uint32_t led;

static void cfg_led(void);
static void rst_led(void);


void EXTI1_IRQHandler(void){

	uint32_t exti;

	led = (uint32_t)1 << 8;
	REG_Write(GPIOA__BRR, led);

	addAppTask(rst_led, 500);

	exti = (uint32_t)1 << 1;
	REG_Write(EXTI__PR, exti);
}

/****************************************************************************
 * cfg_led
 *
 * DESCRIPTION:
 *
 */
static void cfg_led(void) {

	gpio_reg_t gpio;

	// PA8   ------> md led
	gpio.crh.all = REG_Read(GPIOA__CRH);
	gpio.crh.b.cnf_8   = 1; // 01: General purpose output Open-drain
	gpio.crh.b.mode_8  = 2; // 10: Output mode, max speed 2 MHz
	REG_Write(GPIOA__CRH, gpio.crh.all);

	led = (uint32_t)1 << 8;
	REG_Write(GPIOA__BSRR, led);

}

/****************************************************************************
 * cfg_led
 *
 * DESCRIPTION:
 *
 */
static void rst_led(void) {
	led = (uint32_t)1 << 8;
	REG_Write(GPIOA__BSRR, led);
}

/****************************************************************************
 * initMD
 *
 * DESCRIPTION:
 *
 */
void initMD(void) {

	afio_reg_t afio;
	exti_reg_t exti;

	// MOVE GPIO Configuration
	// PIN  ---> PB1

	afio.exticr1.all = REG_Read(AFIO__EXTICR1);
	afio.exticr1.b.exti1 = 1; // 0001: PB[1] pin
	REG_Write(AFIO__EXTICR1, afio.exticr1.all);

	exti.rtsr.all = REG_Read(EXTI__RTSR);
	exti.rtsr.b.tr_1 = 1; // 1: Rising trigger enabled for input line.
	REG_Write(EXTI__RTSR, exti.rtsr.all);

	exti.imr.all = REG_Read(EXTI__IMR);
	exti.imr.b.mr_1 = 1; // 1: Interrupt request from Line 1 is not masked
	REG_Write(EXTI__IMR, exti.imr.all);

	cfg_led();

}
