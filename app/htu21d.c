/*
 * htu21d.c
 *
 *  Created on: 28. pro 2021.
 *      Author: Sep
 */
#include "stm32_regs.h"
#include "htu21d.h"
#include "stdbool.h"
#include "appTasks.h"
#include "serial_handler.h"
#include "global.h"

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
static int32_t htuTemp;
static uint32_t htuRH;

static bool tempValid = false;
static bool rhValid = false;

static uint8_t rx_buf[10];
static uint8_t rxIdx;

static htu_cfg_t dev_cfg;
static bool validCfg = false;

static rhState_t rhState = HTU_RH_START;
static tempState_t tempState = HTU_TEMP_START;
static htuState_t htuState = HTU_IDLE;

static void rhTMO(void);
static void tempTMO(void);

static void tempRsp(void);
static void rhRsp(void);

/****************************************************************************
 * cfgHTU
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
void cfgHTU(htu_cfg_t *cfg) {

    dev_cfg.onTempStart = cfg->onTempStart;
    dev_cfg.onTempDone = cfg->onTempDone;
    dev_cfg.onRhStart = cfg->onRhStart;
    dev_cfg.onRhDone = cfg->onRhDone;

    rhState = HTU_RH_START;
    tempState = HTU_TEMP_START;

    validCfg = true;
}

/****************************************************************************
 * getRH
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
void getRH(void) {

    i2c_cr1_t cr1;
    i2c_cr2_t cr2;

    rhValid = false;

    if(validCfg == false){
        return;
    }
    if(dev_cfg.onRhStart){
        dev_cfg.onRhStart();
    }

    switch(rhState){
        case HTU_RH_START: {
			cr2.all = REG_Read(I2C1__CR2);
			cr2.b.evt_en = 1;
			REG_Write(I2C1__CR2, cr2.all);

			htuState = GET_RH;
			addAppTask(rhTMO, 250);

			cr1.all = 0;
			cr1.b.pe = 1;
			cr1.b.start = 1;
			REG_Write(I2C1__CR1, cr1.all);
            break;
        }
        case HTU_RH_READ: {
        	cr2.all = REG_Read(I2C1__CR2);
			cr2.b.evt_en = 1;
			REG_Write(I2C1__CR2, cr2.all);

			rxIdx = 0;
			htuState = READ_RH;
			addAppTask(rhTMO, 250);

			cr1.all = 0;
			cr1.b.pe = 1;
			cr1.b.start = 1;
			cr1.b.ack = 1;
			REG_Write(I2C1__CR1, cr1.all);
            break;
        }
    }
}

/****************************************************************************
 * getTemp
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
void getTemp(void) {

    i2c_cr1_t cr1;
    i2c_cr2_t cr2;

    tempValid = false;

    if(validCfg == false){
        return;
    }
    if(dev_cfg.onTempStart){
        dev_cfg.onTempStart();
    }

    switch(tempState){
        case HTU_TEMP_START: {
            cr2.all = REG_Read(I2C1__CR2);
            cr2.b.evt_en = 1;
            REG_Write(I2C1__CR2, cr2.all);

            htuState = GET_TEMP;
            addAppTask(tempTMO, 250);

            cr1.all = 0;
            cr1.b.pe = 1;
            cr1.b.start = 1;
            REG_Write(I2C1__CR1, cr1.all);
            break;
        }
        case HTU_TEMP_READ: {
            cr2.all = REG_Read(I2C1__CR2);
            cr2.b.evt_en = 1;
            REG_Write(I2C1__CR2, cr2.all);

            rxIdx = 0;
            htuState = READ_TEMP;
            addAppTask(tempTMO, 250);

            cr1.all = 0;
            cr1.b.pe = 1;
            cr1.b.start = 1;
            cr1.b.ack = 1;
            REG_Write(I2C1__CR1, cr1.all);
            break;
        }
    }
}

/****************************************************************************
 * I2C1_EV_IRQHandler
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
void I2C1_EV_IRQHandler(void) {

    i2c_sr1_t sr1;
    i2c_sr2_t sr2;
    i2c_dr_t dr;
    i2c_cr1_t cr1;
    i2c_cr2_t cr2;

    if(htuState == GET_TEMP || htuState == GET_RH){
        sr1.all = REG_Read(I2C1__SR1);
        if(sr1.b.sb == 1){
            dr.all = 0;
            dr.b.dr = (HTU21D_ADDR << 1) | I2C_WRITE;
            REG_Write(I2C1__DR, dr.all);
        }
        else if(sr1.b.addr == 1){
            sr1.all = REG_Read(I2C1__SR1);
            sr2.all = REG_Read(I2C1__SR2);
            (void)sr2;
            dr.all = 0;
            if(htuState == GET_TEMP){
                dr.b.dr = TEMP_NO_HOLD;
            }
            else {
                dr.b.dr = RH_NO_HOLD;
            }
            REG_Write(I2C1__DR, dr.all);
        }
        else if(sr1.b.btf == 1){
            cr1.all = REG_Read(I2C1__CR1);
            cr1.b.stop = 1;
            REG_Write(I2C1__CR1, cr1.all);

            cr2.all = REG_Read(I2C1__CR2);
            cr2.b.evt_en = 0;
            REG_Write(I2C1__CR2, cr2.all);
            if(htuState == GET_TEMP){
                delAppTask(tempTMO);
                tempState = HTU_TEMP_READ;
                addAppTask(getTemp, 250);
            }
            else {
                delAppTask(rhTMO);
                rhState = HTU_RH_READ;
                addAppTask(getRH, 250);
            }
        }
    }
    if(htuState == READ_TEMP || htuState == READ_RH){
        sr1.all = REG_Read(I2C1__SR1);
        if(sr1.b.sb == 1){
            dr.all = 0;
            dr.b.dr = (HTU21D_ADDR << 1) | I2C_READ;
            REG_Write(I2C1__DR, dr.all);
        }
        else if(sr1.b.addr == 1){
            sr1.all = REG_Read(I2C1__SR1);
            sr2.all = REG_Read(I2C1__SR2);
            (void)sr2;
            cr2.all = REG_Read(I2C1__CR2);
            cr2.b.buff_en = 1;
            REG_Write(I2C1__CR2, cr2.all);
        }
        else if(sr1.b.rxne == 1){
            if(rxIdx == 0){
                rx_buf[rxIdx] = REG_Read(I2C1__DR);
                cr1.all = REG_Read(I2C1__CR1);
                cr1.b.ack = 0;
                cr1.b.stop = 1;
                REG_Write(I2C1__CR1, cr1.all);
                rxIdx++;
            }
            else {
                rx_buf[rxIdx++] = REG_Read(I2C1__DR);
                if(htuState == READ_TEMP){
                	tempValid = true;
                    htuTemp = rx_buf[0];
                    htuTemp <<= 8;
                    rx_buf[1] &= ~0x03;
                    htuTemp |= rx_buf[1];
                    htuTemp *= 17572;
                    htuTemp >>= 16;
                    htuTemp -= 4685;
                    htuTemp /= 10;

                    tempRsp();

                    delAppTask(tempTMO);
                    tempState = HTU_TEMP_START;
                }
                else {
                	rhValid = true;
                    htuRH = rx_buf[0];
                    htuRH <<= 8;
                    htuRH |= rx_buf[1];
                    htuRH *= 125;
                    htuRH >>= 16;
                    htuRH -= 6;
                    if(htuRH < 0) {
                    	htuRH = 0;
                    }
                    if(htuRH > 100) {
                    	htuRH = 100;
                    }

                    rhRsp();

                    delAppTask(rhTMO);
                    rhState = HTU_RH_START;
                }
                htuState = HTU_IDLE;
                cr2.all = REG_Read(I2C1__CR2);
                cr2.b.evt_en = 0;
                cr2.b.buff_en = 0;
                REG_Write(I2C1__CR2, cr2.all);
            }
        }
    }
}

/****************************************************************************
 * rhTMO
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
static void rhTMO(void) {

    i2c_cr1_t cr1;
    i2c_cr2_t cr2;

    cr2.all = REG_Read(I2C1__CR2);
    cr2.b.evt_en = 0;
    cr2.b.buff_en = 0;
    REG_Write(I2C1__CR2, cr2.all);

    cr1.all = REG_Read(I2C1__CR1);
    cr1.b.stop = 1;
    REG_Write(I2C1__CR1, cr1.all);

    htuState = HTU_IDLE;
    rhState = HTU_RH_START;
}

/****************************************************************************
 * rhTMO
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
static void tempTMO(void) {

    i2c_cr1_t cr1;
    i2c_cr2_t cr2;

    cr2.all = REG_Read(I2C1__CR2);
    cr2.b.evt_en = 0;
    cr2.b.buff_en = 0;
    REG_Write(I2C1__CR2, cr2.all);

    cr1.all = REG_Read(I2C1__CR1);
    cr1.b.stop = 1;
    REG_Write(I2C1__CR1, cr1.all);

    htuState = HTU_IDLE;
    tempState = HTU_TEMP_START;
}

/****************************************************************************
 * tempRsp
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
static void tempRsp(void) {

	uint8_t i;
	txPkt_t *txPkt;
	tempRsp_t *rsp;

	for(i = 0; i < CMD_QUEUE_SIZE; i++){
		if(cmdQueue[i].used == 1){
			if(cmdQueue[i].state == CMD_RUN){
				if(cmdQueue[i].cmdID == STM_GET_TEMP){
					cmdQueue[i].used = 0;
					txPkt = (txPkt_t *)&slTxBuf[0];
					txPkt->clientIP = cmdQueue[i].ip;
					txPkt->clientPort = cmdQueue[i].port;
					txPkt->len = sizeof(tempRsp_t);

					rsp = (tempRsp_t *)&txPkt->data[0];
					rsp->pktFunc = cmdQueue[i].pktFunc;
					rsp->cmdID = cmdQueue[i].cmdID;
					rsp->valid = tempValid;
					rsp->temp = htuTemp;

					slWriteMsg(MSG_STM_REQ,
							   sizeof(txPkt_t) + sizeof(tempRsp_t),
							   &slTxBuf[0]);
					break; // exit for-loop
				}
			}
		}
	}
	usedFlags.b.i2c_1 = 0;
}

/****************************************************************************
 * rhRsp
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
static void rhRsp(void) {

	uint8_t i;
	txPkt_t *txPkt;
	rhRsp_t *rsp;

	for(i = 0; i < CMD_QUEUE_SIZE; i++){
		if(cmdQueue[i].used == 1){
			if(cmdQueue[i].state == CMD_RUN){
				if(cmdQueue[i].cmdID == STM_GET_RH){
					cmdQueue[i].used = 0;
					txPkt = (txPkt_t *)&slTxBuf[0];
					txPkt->clientIP = cmdQueue[i].ip;
					txPkt->clientPort = cmdQueue[i].port;
					txPkt->len = sizeof(rhRsp_t);

					rsp = (rhRsp_t *)&txPkt->data[0];
					rsp->pktFunc = cmdQueue[i].pktFunc;
					rsp->cmdID = cmdQueue[i].cmdID;
					rsp->valid = rhValid;
					rsp->rh = htuRH;

					slWriteMsg(MSG_STM_REQ,
							   sizeof(txPkt_t) + sizeof(rhRsp_t),
							   &slTxBuf[0]);
					break; // exit for-loop
				}
			}
		}
	}
	usedFlags.b.i2c_1 = 0;
}


