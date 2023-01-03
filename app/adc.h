/*
 * adc.h
 *
 *  Created on: 15. lis 2022.
 *      Author: Sep
 */

#ifndef APP_ADC_H_
#define APP_ADC_H_


#pragma pack(push, 1)

typedef struct {
    uint16_t pktFunc;
    uint16_t cmdID;
    uint8_t valid;
    uint32_t adc;
} adcRsp_t;

#pragma pack(pop)


extern void testADC(void);

#endif /* APP_ADC_H_ */
