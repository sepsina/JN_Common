/*
 * fram.c
 *
 *  Created on: Sep 17, 2022
 *      Author: Serfa
 */

#include "stm32_regs.h"
#include "stdbool.h"
#include "global.h"

static void runDMA(uint16_t len);

uint8_t spiTxBuff[16];
uint8_t spiRxBuff[16];

/****************************************************************************
 * framWrite
 *
 * DESCRIPTION:
 *
 */
void framWrite(uint16_t addr,
               uint8_t *data,
               uint16_t len) {

    uint16_t idx = 0;
    uint16_t i;
    uint16_t dma_len;

    spiTxBuff[0] = 0x06; // WREN: Set write enable latch -> 0000 0110b
    runDMA(1);

    spiTxBuff[idx++] = 0x02; // 0000 0010b: Write memory data
    spiTxBuff[idx++] = (uint8_t)(addr >> 8);
    spiTxBuff[idx++] = (uint8_t)addr;
    for(i = 0; i < len; i++){
        spiTxBuff[idx++] = data[i];
    }
    dma_len = idx;

    runDMA(dma_len);
}

/****************************************************************************
 * framRead
 *
 * DESCRIPTION:
 *
 */
void framRead(uint16_t addr,
              uint8_t *data,
              uint16_t len) {

    uint16_t idx = 0;
    uint16_t i, j;
    uint16_t dma_len;

    spiTxBuff[idx++] = 0x03; // 0000 0011b: Read memory data
    spiTxBuff[idx++] = (uint8_t)(addr >> 8);
    spiTxBuff[idx++] = (uint8_t)addr;
    for(i = 0; i < len; i++){
        spiTxBuff[idx++] = 0x67;
    }
    dma_len = idx;

    runDMA(dma_len);

    for(i = 0, j = 3; i < len; i++, j++){
        data[i] = spiRxBuff[j];
    }
}

/****************************************************************************
 * runDMA
 *
 * DESCRIPTION:
 *
 */
static void runDMA(uint16_t len) {

    spi_reg_t spi;
    dma_reg_t dma;

    spiFlag = false;

    dma.data_len.b.ndt = len;
    REG_Write(DMA__CNDTR2, dma.data_len.all);
    REG_Write(DMA__CNDTR3, dma.data_len.all);

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

    while(spiFlag == false);

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
}





