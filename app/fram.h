/*
 * fram.h
 *
 *  Created on: Sep 17, 2022
 *      Author: Serfa
 */

#ifndef APP_FRAM_H_
#define APP_FRAM_H_



extern uint8_t spiTxBuff[16];
extern uint8_t spiRxBuff[16];

extern void framWrite(uint16_t addr, uint8_t *data, uint16_t len);
extern void framRead(uint16_t addr, uint8_t *data, uint16_t len);


#endif /* APP_FRAM_H_ */
