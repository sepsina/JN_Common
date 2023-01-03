/*
 * tc.c
 *
 *  Created on: 17. lis 2022.
 *      Author: Sep
 */

#include "stm32_regs.h"
#include "stm32f1xx_ll_system.h"
#include "stdbool.h"
#include "serial_handler.h"
#include "global.h"
#include "tc.h"
#include "appTasks.h"

static uint8_t spi_tx_buf[16];
static uint8_t spi_rx_buf[16];

/****************************************************************************
 * runDMA
 *
 * DESCRIPTION:
 *
 */
void getTC(tcCmd_t *tcCmd) {

	spi_reg_t spi;
	dma_reg_t dma;

	uint16_t tc;
	txPkt_t *txPkt;
	tcRsp_t *rsp;
	/*
	spi.cr1.all = REG_Read(SPI1__CR1);
	spi.cr1.b.clk_pol = 0;   // 0: CK to 0 when idle
	spi.cr1.b.clk_pha = 0;   // 0: The first clock transition is the first data capture edge
	REG_Write(SPI1__CR1, spi.cr1.all);
	*/
	dma.mem_addr.b.ma = (uint32_t)&spi_rx_buf[0];
	REG_Write(DMA__CMAR2, dma.mem_addr.all);
	dma.mem_addr.b.ma = (uint32_t)&spi_tx_buf[0];
	REG_Write(DMA__CMAR3, dma.mem_addr.all);

	spi_rx_buf[0] = 0x00;
	spi_rx_buf[1] = 0x00;

	spi_tx_buf[0] = 0xAC;
	spi_tx_buf[1] = 0xDC;

	dma.data_len.b.ndt = 2;
	REG_Write(DMA__CNDTR2, dma.data_len.all);
	REG_Write(DMA__CNDTR3, dma.data_len.all);

	REG_Write(GPIOB__BRR, (uint32_t)1 << 5); // PB5 -> 0

	// SPI enable
	spi.cr1.all = REG_Read(SPI1__CR1);
	spi.cr1.b.spi_en = 1;
	REG_Write(SPI1__CR1, spi.cr1.all);

	// DMA Rx enable
	dma.ch_cfg.all = REG_Read(DMA__CCR2);
	dma.ch_cfg.b.en = 1;
	REG_Write(DMA__CCR2, dma.ch_cfg.all);

	// DMA Tx enable
	dma.ch_cfg.all = REG_Read(DMA__CCR3);
	dma.ch_cfg.b.en = 1;
	REG_Write(DMA__CCR3, dma.ch_cfg.all);

	spiFlag = false;
	while(spiFlag == false)

	// DMA Rx disable
	dma.ch_cfg.all = REG_Read(DMA__CCR2);
	dma.ch_cfg.b.en = 0;
	REG_Write(DMA__CCR2, dma.ch_cfg.all);

	// DMA Tx disable
	dma.ch_cfg.all = REG_Read(DMA__CCR3);
	dma.ch_cfg.b.en = 0;
	REG_Write(DMA__CCR3, dma.ch_cfg.all);

	// SPI disable
	spi.cr1.all = REG_Read(SPI1__CR1);
	spi.cr1.b.spi_en = 0;
	REG_Write(SPI1__CR1, spi.cr1.all);

	REG_Write(GPIOB__BSRR, (uint32_t)1 << 5); // PB5 -> 1
	/*
	spi.cr1.all = REG_Read(SPI1__CR1);
	spi.cr1.b.clk_pol = 1;   // 1: CK to 1 when idle
	spi.cr1.b.clk_pha = 1;   // 1: The second clock transition is the first data capture edge
	REG_Write(SPI1__CR1, spi.cr1.all);
	*/
	if(spiFlag == true){
	    tc = spi_rx_buf[0];
        tc <<= 8;
        tc |= spi_rx_buf[1];
        tc >>= 3;
        //tc /= 4;
	}
	else {
	    tc = 1000 * 4;
	}
	txPkt = (txPkt_t *)&slTxBuf[0];
	txPkt->clientIP = tcCmd->ip;
	txPkt->clientPort = tcCmd->port;
	txPkt->len = sizeof(tcRsp_t);

	rsp = (tcRsp_t *)&txPkt->data[0];
	rsp->pktFunc = tcCmd->pktFunc;
	rsp->cmdID = tcCmd->cmdID;
	rsp->tc = tc;

	slWriteMsg(MSG_STM_REQ,
			   sizeof(txPkt_t) + sizeof(tcRsp_t),
			   &slTxBuf[0]);

}

