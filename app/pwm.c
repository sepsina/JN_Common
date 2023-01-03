/*
 * pwm.c
 *
 *  Created on: 16. lis 2022.
 *      Author: Sep
 */
#include "stm32_regs.h"
#include "stm32f1xx_ll_system.h"
#include "serial_handler.h"
#include "pwm.h"
#include "global.h"



/****************************************************************************
 * getPWM
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
void getPWM(pwmCmd_t *pwmCmd) {

	txPkt_t *txPkt;
	pwmRsp_t *rsp;
	tim_reg_t tim;

	txPkt = (txPkt_t *)&slTxBuf[0];
	txPkt->clientIP = pwmCmd->ip;
	txPkt->clientPort = pwmCmd->port;
	txPkt->len = sizeof(pwmRsp_t);

	rsp = (pwmRsp_t *)&txPkt->data[0];
	rsp->pktFunc = pwmCmd->pktFunc;
	rsp->cmdID = pwmCmd->cmdID;
	tim.ccr.all = REG_Read(TIM2__CCR1);
	rsp->pwm = tim.ccr.b.ccr / 100;

	slWriteMsg(MSG_STM_REQ,
			   sizeof(txPkt_t) + sizeof(pwmRsp_t),
			   &slTxBuf[0]);

}

/****************************************************************************
 * rhRsp
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
void setPWM(pwmCmd_t *pwmCmd) {

	tim_reg_t tim;
	setPwm_t *setPwm;

	setPwm = (setPwm_t *)pwmCmd->cmd;
	tim.ccr.all = REG_Read(TIM2__CCR1);
	tim.ccr.b.ccr = setPwm->pwm * 100;
	REG_Write(TIM2__CCR1, tim.ccr.all);

}
