/*
 * htu21d.h
 *
 *  Created on: 28. pro 2021.
 *      Author: Sep
 */

#ifndef HTU21D_H_
#define HTU21D_H_


#define HTU21D_ADDR    0x40
#define RH_NO_HOLD     0xF5
#define TEMP_NO_HOLD   0xF3

#define I2C_WRITE   0x00
#define I2C_READ    0x01

#define STATE_IDLE       0x00
#define STATE_RX_RDY     0x01
#define STATE_TX_RDY     0x02
#define STATE_NACK_ADDR  0x03
#define STATE_NACK_DATA  0x04

typedef enum {
    HTU_RH_START=0,
    HTU_RH_READ,
} rhState_t;

typedef enum {
    HTU_TEMP_START=100,
    HTU_TEMP_READ,
} tempState_t;

typedef enum {
    GET_TEMP,
    READ_TEMP,
    GET_RH,
    READ_RH,
    HTU_IDLE
} htuState_t;

typedef void (*onTempStart_t)(void);
typedef void (*onTempDone_t)(void);
typedef void (*onRhStart_t)(void);
typedef void (*onRhDone_t)(void);

typedef struct {
    onTempStart_t onTempStart;
    onTempDone_t onTempDone;
    onRhStart_t onRhStart;
    onRhDone_t onRhDone;
} htu_cfg_t;

#pragma pack(push, 1)

typedef struct {
    uint16_t pktFunc;
    uint16_t cmdID;
    uint8_t valid;
    int32_t temp;
} tempRsp_t;

typedef struct {
    uint16_t pktFunc;
    uint16_t cmdID;
    uint8_t valid;
    uint32_t rh;
} rhRsp_t;

#pragma pack(pop)

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
extern void cfgHTU(htu_cfg_t *cfg);
extern void getRH(void);
extern void getTemp(void);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#endif /* HTU21D_H_ */
