/*****************************************************************************
 *
 * MODULE:             JN-AN-1217
 *
 * COMPONENT:          app_serial_commands.c
 *
 * DESCRIPTION:
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "stm32_regs.h"
#include "appTasks.h"
#include "serial_handler.h"
#include "stdbool.h"
#include "stddef.h"
#include "pwm.h"
#include "tc.h"
#include "thermostat.h"
#include "global.h"

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
static void setWrIdx(void);
static void getRxChar(uint8_t rxByte);

static void txByte(bool specChar,
                   uint8_t data);

static void txData(void);

//static void processMsg(uint16_t msgType);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
processCmd_t processCmd = NULL;

uint8_t slTxBuf[100];

rxBuf_t rxBuf = {
    .rdIdx = 0,
    .wrIdx = 0
};
txBuf_t txBuf = {
    .rdIdx = 0,
    .wrIdx = 0
};

uint8_t rxMsg[MAX_MSG_LEN];

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

static uint8_t txSend[TX_SEND_SIZE];

/****************************************************************************
 * uartGetRx
 *
 * DESCRIPTION:
 *
 */
void uartGetRx(void) {

    int8_t cnt = 20;
    uint8_t rxChr;

    setWrIdx();

    while((rxBuf.rdIdx != rxBuf.wrIdx) && cnt--){
        rxChr = rxBuf.data[rxBuf.rdIdx++];
        getRxChar(rxChr);
        if(rxBuf.rdIdx >= RX_BUF_SIZE) {
            rxBuf.rdIdx = 0;
        }
    }
}

/****************************************************************************
 * setWrIdx
 *
 * DESCRIPTION:
 *
 */
static void setWrIdx(void) {

    dma_reg_t dma;
    uint32_t remainCnt;

    dma.data_len.all = REG_Read(DMA__CNDTR6);
    remainCnt = dma.data_len.b.ndt;
    rxBuf.wrIdx = RX_BUF_SIZE - remainCnt;

}

/******************************************************************************
 * getRxChar
 *
 * DESCRIPTION: Processes the received character
 *
 * RETURNS:
 *
 */
static void getRxChar(uint8_t rxByte) {

    static uint16_t idx;
    static bool isEsc = false;
    static bool errFlag = true;
    static uint16_t msgType;
    static uint16_t msgLen;
    static uint8_t msgCRC;
    static uint8_t calcCRC;
    static msgState_t msgState = MSG_WAIT_START;

    switch(rxByte) {
        case START_CHAR: {
            idx = 0;
            isEsc = false;
            errFlag = false;
            msgState = MSG_WAIT_TYPE_LSB;
            break;
        }
        case ESC_CHAR: {
            isEsc = true;
            break;
        }
        case END_CHAR: {
            if(errFlag == false){
                if(calcCRC == msgCRC){
                    if(processCmd){
                        processCmd(msgType);
                    }
                    //processMsg(msgType);
                }
            }
            msgState = MSG_WAIT_START;
            break;
        }
        default: {
            if(isEsc) {
                rxByte ^= 0x10;
                isEsc = false;
            }
            switch(msgState) {
                case MSG_WAIT_START: {
                    // ---
                    break;
                }
                case MSG_WAIT_TYPE_LSB: {
                    calcCRC = rxByte;
                    msgType = rxByte;
                    msgState++;
                    break;
                }
                case MSG_WAIT_TYPE_MSB: {
                    calcCRC ^= rxByte;
                    msgType |= (uint16_t)rxByte << 8;
                    msgState++;
                    break;
                }
                case MSG_WAIT_LEN_LSB: {
                    calcCRC ^= rxByte;
                    msgLen = rxByte;
                    msgState++;
                    break;
                }
                case MSG_WAIT_LEN_MSB: {
                    calcCRC ^= rxByte;
                    msgLen |= (uint16_t)rxByte << 8;
                    msgState++;
                    if(msgLen > MAX_MSG_LEN){
                        errFlag = true;
                        msgState = MSG_WAIT_START;
                    }
                    break;
                }
                case MSG_WAIT_CRC: {
                    msgCRC = rxByte;
                    msgState++;
                    break;
                }
                case MSG_WAIT_DATA: {
                    if(idx < msgLen) {
                        calcCRC ^= rxByte;
                        rxMsg[idx++] = rxByte;
                    }
                    else {
                        errFlag = true;
                        msgState = MSG_WAIT_START;
                    }
                    break;
                }
            }
            break;
        }
    }
}

/****************************************************************************
 * slWriteMsg
 *
 * DESCRIPTION: Write message to the serial link
 *
 * RETURNS:
 *
 */
void slWriteMsg(uint16_t type,
                uint16_t len,
                uint8_t *data) {
    uint16_t n;
    uint8_t crc;

    crc  = (uint8_t)type;
    crc ^= (uint8_t)(type >> 8);
    crc ^= (uint8_t)len;
    crc ^= (uint8_t)(len >> 8);
    for(n = 0; n < len; n++) {
        crc ^= data[n];
    }

    // Send start character
    txByte(true, START_CHAR);

    // Send message type
    txByte(false, (uint8_t)type);
    txByte(false, (uint8_t)(type >> 8));

    // Send message length
    txByte(false, (uint8_t)len);
    txByte(false, (uint8_t)(len >> 8));

    // Send message checksum
    txByte(false, crc);

    // Send message payload
    for(n = 0; n < len; n++) {
        txByte(false, data[n]);
    }

    // Send end character
    txByte(true, END_CHAR);

    addAppTask(txData, SLEEP_TIME);
}

/****************************************************************************
 * txData
 *
 * DESCRIPTION:
 *
 */
static void txData(void) {

    int32_t idx = 0;
    int32_t cnt = 50;
    dma_reg_t dma;
    dma_ccr_t chCfg;
    usart_reg_t usart;

    chCfg.all = REG_Read(DMA__CCR7);
    usart.sr.all = REG_Read(USART2__SR);
    if(usart.sr.b.tc == 0){ // 0: No transfer complete event on usart tx
        if(chCfg.b.en == 1){
            addAppTask(txData, SLEEP_TIME);
            return;
        }
    }
    chCfg.b.en = 0; // 0: Channel disabled
    REG_Write(DMA__CCR7, chCfg.all);

    usart.sr.b.tc = 0;
    REG_Write(USART2__SR, usart.sr.all);

    if(txBuf.rdIdx == txBuf.wrIdx){
        return;
    }

    while((txBuf.rdIdx != txBuf.wrIdx) && (cnt--)){
        txSend[idx++] = txBuf.data[txBuf.rdIdx++];
        if(txBuf.rdIdx >= TX_BUF_SIZE){
            txBuf.rdIdx = 0;
        }
    }
    if(idx > 0){
        dma.mem_addr.b.ma = (uint32_t)&txSend[0];
        REG_Write(DMA__CMAR7, dma.mem_addr.all);
        dma.per_addr.b.pa = USART2__DR;
        REG_Write(DMA__CPAR7, dma.per_addr.all);

        dma.data_len.b.ndt = idx;
        REG_Write(DMA__CNDTR7, dma.data_len.all);

        chCfg.b.en = 1; // 1: Channel enabled
        REG_Write(DMA__CCR7, chCfg.all);
    }

    addAppTask(txData, SLEEP_TIME);
}

/****************************************************************************
 * txByte
 *
 * DESCRIPTION:
 * Send, escaping if required, a byte to the serial link
 *
 * PARAMETERS:  Name       RW  Usage
 *              specChar   R   true if this byte should not be escaped
 *              data       R   Character to send
 *
 * RETURNS:
 * void
 *
 */
static void txByte(bool specChar,
                   uint8_t data) {

    if(!specChar && data < 0x10) {
        /* Send escape character and escape byte */
        data ^= 0x10;
        txBuf.data[txBuf.wrIdx++] = ESC_CHAR;
        if(txBuf.wrIdx >= TX_BUF_SIZE){
            txBuf.wrIdx = 0;
        }
    }
    txBuf.data[txBuf.wrIdx++] = data;
    if(txBuf.wrIdx >= TX_BUF_SIZE) {
        txBuf.wrIdx = 0;
    }
}

/******************************************************************************
 * processMsg
 *
 * DESCRIPTION: Processes the received message
 *
 * RETURNS:
 *
 *
static void processMsg(uint16_t msgType) {

    switch(msgType) {
    	case MSG_STM_REQ: {
    		uartRx_t *req = (uartRx_t *)&rxMsg[0];
    		remCmd_t *cmd = (remCmd_t *)&req->data[0];
    		switch(cmd->cmdID){
    			case STM_GET_TEMP: {
    				for(uint8_t i = 0; i < CMD_QUEUE_SIZE; i++){
    					if(cmdQueue[i].used == 0){
    						cmdQueue[i].used = 1;
    						cmdQueue[i].state = CMD_WAIT;
    						cmdQueue[i].ip = req->clientIP;
    						cmdQueue[i].port = req->clientPort;
    						cmdQueue[i].pktFunc = cmd->pktFunc;
    						cmdQueue[i].cmdID = cmd->cmdID;
    						for(uint8_t j = 0; j < CMD_PARAMS_LEN; j++){
    							cmdQueue[i].cmd[i] = cmd->cmd[i];
    						}
    						break; // exit for-loop
    					}
    				}
    				break;
    			}
    			case STM_GET_RH: {
    				for(uint8_t i = 0; i < CMD_QUEUE_SIZE; i++){
						if(cmdQueue[i].used == 0){
							cmdQueue[i].used = 1;
							cmdQueue[i].state = CMD_WAIT;
							cmdQueue[i].ip = req->clientIP;
							cmdQueue[i].port = req->clientPort;
							cmdQueue[i].pktFunc = cmd->pktFunc;
							cmdQueue[i].cmdID = cmd->cmdID;
							for(uint8_t j = 0; j < CMD_PARAMS_LEN; j++){
								cmdQueue[i].cmd[i] = cmd->cmd[i];
							}
							break; // exit for-loop
						}
					}
    				break;
    			}
    			case STM_GET_ADC: {
					for(uint8_t i = 0; i < CMD_QUEUE_SIZE; i++){
						if(cmdQueue[i].used == 0){
							cmdQueue[i].used = 1;
							cmdQueue[i].state = CMD_WAIT;
							cmdQueue[i].ip = req->clientIP;
							cmdQueue[i].port = req->clientPort;
							cmdQueue[i].pktFunc = cmd->pktFunc;
							cmdQueue[i].cmdID = cmd->cmdID;
							for(uint8_t j = 0; j < CMD_PARAMS_LEN; j++){
								cmdQueue[i].cmd[i] = cmd->cmd[i];
							}
							break; // exit for-loop
						}
					}
					break;
				}
    			case STM_GET_PWM: {
    				pwmCmd_t pwmCmd;

    				pwmCmd.ip = req->clientIP;
    				pwmCmd.port = req->clientPort;
    				pwmCmd.pktFunc = cmd->pktFunc;
    				pwmCmd.cmdID = cmd->cmdID;

    				getPWM(pwmCmd);

    				break;
    			}
    			case STM_SET_PWM: {
					pwmCmd_t pwmCmd;

					pwmCmd.ip = req->clientIP;
					pwmCmd.port = req->clientPort;
					pwmCmd.pktFunc = cmd->pktFunc;
					pwmCmd.cmdID = cmd->cmdID;
					for(uint8_t i = 0; i < CMD_PARAMS_LEN; i++){
						pwmCmd.cmd[i] = cmd->cmd[i];
					}

					setPWM(pwmCmd);

					break;
				}
    			case STM_GET_TC: {
					tcCmd_t tcCmd;

					tcCmd.ip = req->clientIP;
					tcCmd.port = req->clientPort;
					tcCmd.pktFunc = cmd->pktFunc;
					tcCmd.cmdID = cmd->cmdID;

					getTC(tcCmd);

					break;
				}
    			case STM_GET_THERMOSTAT: {
                    tsCmd_t tsCmd;

                    tsCmd.ip = req->clientIP;
                    tsCmd.port = req->clientPort;
                    tsCmd.pktFunc = cmd->pktFunc;
                    tsCmd.cmdID = cmd->cmdID;

                    getThermostat(&tsCmd);

                    break;
                }
    			case STM_SET_THERMOSTAT: {
                    tsCmd_t tsCmd;

                    tsCmd.ip = req->clientIP;
                    tsCmd.port = req->clientPort;
                    tsCmd.pktFunc = cmd->pktFunc;
                    tsCmd.cmdID = cmd->cmdID;
                    for(uint8_t i = 0; i < CMD_PARAMS_LEN; i++){
                        tsCmd.cmd[i] = cmd->cmd[i];
                    }

                    setThermostat(&tsCmd);

                    break;
                }
    		}
    		break;
    	}
    }
}
*/
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
