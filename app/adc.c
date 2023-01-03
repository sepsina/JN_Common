/*
 * adc.c
 *
 *  Created on: 15. lis 2022.
 *      Author: Sep
 */

#include "stdbool.h"
#include "stm32_regs.h"
#include "appTasks.h"
#include "serial_handler.h"
#include "global.h"
#include "adc.h"

static bool calFlag = false;
static uint16_t adcData[16];
static bool adcFlag = false;

static uint32_t adcVolt;

static void adcDone(void);
static void adcRsp(void);

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void) {

    dma_reg_t dma;
    dma_isr_t isr_sts;

    isr_sts.all = REG_Read(DMA__ISR);
    if(isr_sts.ch_1.tc == 1){
        dma.int_clr.all = 0;
        dma.int_clr.ch_1.tc = 1;
        REG_Write(DMA__IFCR, dma.int_clr.all);

        addAppTask(adcDone, 20);

        dma.ch_cfg.all = REG_Read(DMA__CCR1);
        dma.ch_cfg.b.en = 0;     // 0: Channel disabled
        REG_Write(DMA__CCR1, dma.ch_cfg.all);
    }
}

/****************************************************************************
 * testADC
 *
 * DESCRIPTION:
 *
 */
void testADC(void) {

    adc_reg_t adc;
    dma_reg_t dma;

    if(calFlag == false){
        calFlag = true;
        adc.cr2.all = REG_Read(ADC__CR2);
        adc.cr2.b.cal = 1;
        REG_Write(ADC__CR2, adc.cr2.all);
        addAppTask(testADC, 20);
    }
    else {
        adcFlag = false;

        dma.mem_addr.b.ma = (uint32_t)&adcData[0];
        REG_Write(DMA__CMAR1, dma.mem_addr.all);

        dma.data_len.all = 0;
        dma.data_len.b.ndt = 1;
        REG_Write(DMA__CNDTR1, dma.data_len.all);

        dma.ch_cfg.all = REG_Read(DMA__CCR1);
        dma.ch_cfg.b.en = 1;     // 1: Channel enabled
        REG_Write(DMA__CCR1, dma.ch_cfg.all);

        adc.cr2.all = REG_Read(ADC__CR2);
        adc.cr2.b.sw_start = 1; // 1: Starts conversion of regular channels
        REG_Write(ADC__CR2, adc.cr2.all);
    }
}

/****************************************************************************
 * adcDone
 *
 * DESCRIPTION:
 *
 */
static void adcDone(void) {

    adcVolt = adcData[0] * 3300;
    adcVolt /= 4096;

    adcRsp();
}

/****************************************************************************
 * tempRsp
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
static void adcRsp(void) {

	uint8_t i;
	txPkt_t *txPkt;
	adcRsp_t *rsp;

	for(i = 0; i < CMD_QUEUE_SIZE; i++){
		if(cmdQueue[i].used == 1){
			if(cmdQueue[i].state == CMD_RUN){
				if(cmdQueue[i].cmdID == STM_GET_ADC){
					cmdQueue[i].used = 0;
					txPkt = (txPkt_t *)&slTxBuf[0];
					txPkt->clientIP = cmdQueue[i].ip;
					txPkt->clientPort = cmdQueue[i].port;
					txPkt->len = sizeof(adcRsp_t);

					rsp = (adcRsp_t *)&txPkt->data[0];
					rsp->pktFunc = cmdQueue[i].pktFunc;
					rsp->cmdID = cmdQueue[i].cmdID;
					rsp->valid = 1;
					rsp->adc = adcVolt;

					slWriteMsg(MSG_STM_REQ,
							   sizeof(txPkt_t) + sizeof(adcRsp_t),
							   &slTxBuf[0]);
					break; // exit for-loop
				}
			}
		}
	}
	usedFlags.b.adc = 0;
}

