/*
 * pwm.h
 *
 *  Created on: 16. lis 2022.
 *      Author: Sep
 */

#ifndef APP_PWM_H_
#define APP_PWM_H_

#include "global.h"

#pragma pack(push, 1)

typedef struct {
    uint32_t ip;
    uint16_t port;
    uint16_t pktFunc;
	uint16_t cmdID;
	uint8_t cmd[CMD_PARAMS_LEN];
} pwmCmd_t;

typedef struct {
    uint16_t pktFunc;
    uint16_t cmdID;
    uint8_t pwm;
} pwmRsp_t;

typedef struct {
    uint16_t pwm;
} setPwm_t;

#pragma pack(pop)


extern void getPWM(pwmCmd_t *pwmCmd);
extern void setPWM(pwmCmd_t *pwmCmd);

#endif /* APP_PWM_H_ */
