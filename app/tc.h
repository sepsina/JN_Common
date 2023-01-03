/*
 * tc.h
 *
 *  Created on: 17. lis 2022.
 *      Author: Sep
 */

#ifndef APP_TC_H_
#define APP_TC_H_


#pragma pack(push, 1)

typedef struct {
    uint32_t ip;
    uint16_t port;
    uint16_t pktFunc;
	uint16_t cmdID;
	uint8_t cmd[CMD_PARAMS_LEN];
} tcCmd_t;

typedef struct {
    uint16_t pktFunc;
    uint16_t cmdID;
    uint16_t tc;
} tcRsp_t;


#pragma pack(pop)

extern void getTC(tcCmd_t *tcCmd);

#endif /* APP_TC_H_ */
