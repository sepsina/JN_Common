/*
 * thermostat.h
 *
 *  Created on: Nov 26, 2022
 *      Author: sep
 */

#ifndef APP_T_STAT_H_
#define APP_T_STAT_H_

#include "stdint.h"

#pragma pack(push, 1)

typedef struct {
    uint16_t pktFunc;
    uint16_t cmdID;
    uint8_t cmd[CMD_PARAMS_LEN];
} tsCmd_t;

typedef struct {
    uint8_t runFlag;
    uint16_t tcTemp;
    uint16_t setPoint;
    uint8_t hist;
    uint8_t duty;
} tsRsp_t;

typedef struct {
    uint8_t runFlag;
    uint16_t setPoint;
    uint8_t hist;
    uint8_t duty;
} tsSet_t;

#pragma pack(pop)

extern void getThermostat(void);
extern void setThermostat(void);

#endif /* APP_THERMOSTAT_H_ */
