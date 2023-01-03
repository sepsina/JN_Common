/*****************************************************************************
 *
 * MODULE:             JN-AN-1217
 *
 * COMPONENT:          serial_handler.h
 *
 * DESCRIPTION:
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright NXP B.V. 2016. All rights reserved
 *
 ***************************************************************************/

#ifndef SERIAL_HANDLER_H_
#define SERIAL_HANDLER_H_

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
//#define MAX_PKT_SIZE   256

#define MAX_MSG_LEN   256

#define START_CHAR  0x01
#define ESC_CHAR    0x02
#define END_CHAR    0x03

#define SL_MSG_LOG     0x8001

#define MSG_STM_REQ    0x0A01
#define MSG_STM_RSP    0x0A02

#define RX_BUF_SIZE    256
#define TX_BUF_SIZE    512

#define TX_SEND_SIZE   256

#define STM_GET_TEMP   0x0001
#define STM_GET_RH     0x0002
#define STM_GET_ADC    0x0003
#define STM_GET_PWM    0x0004
#define STM_SET_PWM    0x0005
#define STM_GET_TC     0x0006

#define STM_SET_THERMOSTAT   0x0007
#define STM_GET_THERMOSTAT   0x0008

#define STM_SET_ID   0x0009
#define STM_GET_ID   0x000A

#define STM_RSP        0x8C01

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef void (*processCmd_t)(uint16_t msgType);

typedef enum {
    MSG_WAIT_START,
    MSG_WAIT_TYPE_LSB,
    MSG_WAIT_TYPE_MSB,
    MSG_WAIT_LEN_LSB,
    MSG_WAIT_LEN_MSB,
    MSG_WAIT_CRC,
    MSG_WAIT_DATA,
} msgState_t;

typedef struct {
    uint32_t rdIdx;
    uint32_t wrIdx;
    uint8_t data[RX_BUF_SIZE];
} rxBuf_t;

typedef struct {
    uint32_t rdIdx;
    uint32_t wrIdx;
    uint8_t data[TX_BUF_SIZE];
} txBuf_t;

#pragma pack(push, 1)

typedef struct {
    uint32_t clientIP;
    uint16_t clientPort;
    uint8_t data[];
} uartRx_t;

typedef struct {
    uint32_t clientIP;
    uint16_t clientPort;
    uint8_t len;
    uint8_t data[];
} txPkt_t;

typedef struct {
    uint16_t pktFunc;
    uint16_t cmdID;
    uint8_t cmd[];
} remCmd_t;

typedef struct {
    uint16_t setPoint;
    uint8_t hist;
    uint8_t duty;
} ts_t;

#pragma pack(pop)

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
extern void uartGetRx(void);
extern void slWriteMsg(uint16_t type,
                       uint16_t len,
                       uint8_t *data);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern processCmd_t processCmd;
extern uint8_t rxMsg[];

extern uint8_t slTxBuf[100];

extern rxBuf_t rxBuf;
extern txBuf_t txBuf;

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#endif /*APP_SERIAL_COMMANDS_H_*/
