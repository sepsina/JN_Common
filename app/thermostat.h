/*
 * thermostat.h
 *
 *  Created on: Nov 26, 2022
 *      Author: sep
 */

#ifndef APP_THERMOSTAT_H_
#define APP_THERMOSTAT_H_

#include "stdint.h"
#include "serial_handler.h"
#include "global.h"

#pragma pack(push, 1)

typedef struct {
    uint32_t ip;
    uint16_t port;
    uint16_t pktFunc;
    uint16_t cmdID;
    uint8_t cmd[CMD_PARAMS_LEN];
} tsCmd_t;

typedef struct {
    uint16_t pktFunc;
    uint16_t cmdID;
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

extern void regTemp(void);
extern void initThermostat(ts_t *ts);
extern void getThermostat(tsCmd_t *tsCmd);
extern void setThermostat(tsCmd_t *tsCmd);
extern void tsData(tsSet_t *tsSet);

#endif /* APP_THERMOSTAT_H_ */
