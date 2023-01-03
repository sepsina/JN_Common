/*
 * appTasks.c
 *
 *  Created on: 22. pro 2021.
 *      Author: Sep
 */
#include "stdbool.h"
#include "stm32_regs.h"
#include "stm32f1xx_ll_system.h"
#include "appTasks.h"
#include "global.h"

appTask_t appTasks[TIMER_TASKS_NUM];

/****************************************************************************
 * appTasksHandler
 *
 * DESCRIPTION:
 *
 */
uint16_t appTasksHandler(void) {

    int8_t i;
    uint32_t sleepTime = (uint32_t)-1;

    for(i = 0; i < TIMER_TASKS_NUM; i++) {
        if(appTasks[i].used == true) {
            if(appTasks[i].timeout == 0) {
                appTasks[i].used = false;
                appTasks[i].taskCB();
            }
        }
    }
    for(i = 0; i < TIMER_TASKS_NUM; i++) {
        if(appTasks[i].used == true) {
            if(appTasks[i].timeout > 0) {
                if(appTasks[i].timeout < sleepTime) {
                    sleepTime = appTasks[i].timeout;
                }
            }
        }
    }
    for(i = 0; i < TIMER_TASKS_NUM; i++) {
        if(appTasks[i].used == true) {
            appTasks[i].timeout -= sleepTime;
            if(appTasks[i].timeout < MIN_SLEEP_TIME) {
                appTasks[i].timeout = 0;
            }
        }
    }

#ifdef ZED_DEVICE
    if(sleepTime > (nodeData.reportInterval * 1000 * 5)){
        sleepTime = nodeData.reportInterval * 1000;
        addAppTask(appEvent, 0);
    }
#endif

    return sleepTime;
}

/****************************************************************************
 * initAppTask
 *
 * DESCRIPTION:
 *
 */
void initAppTask(void) {

    uint8_t i;

    for(i = 0; i < TIMER_TASKS_NUM; i++){
        appTasks[i].used = false;
    }
}

/****************************************************************************
 * addAppTask
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
int8_t addAppTask(taskCB_t cb,
                  uint32_t timeout) {
    int8_t timerIdx;
    int8_t i;

    delAppTask(cb);

    timerIdx = -1;
    for(i = 0; i < TIMER_TASKS_NUM; i++){
        if(appTasks[i].used == false){
            appTasks[i].used = true;
            appTasks[i].timeout = timeout;
            appTasks[i].taskCB = cb;
            timerIdx = i;
            break;
        }
    }

    return timerIdx;
}

/****************************************************************************
 * delAppTask
 *
 * DESCRIPTION:
 *
 */
void delAppTask(taskCB_t cb) {

    uint8_t i;

    for(i = 0; i < TIMER_TASKS_NUM; i++){
        if(appTasks[i].used == true){
            if(appTasks[i].taskCB == cb){
                appTasks[i].used = false;
            }
        }
    }
}

/****************************************************************************
 * getTaskTMO
 *
 * DESCRIPTION:
 *
 */
uint32_t getTaskTMO(taskCB_t cb) {

    uint8_t i;
    uint32_t tmo = 0;

    for(i = 0; i < TIMER_TASKS_NUM; i++){
        if(appTasks[i].used == true){
            if(appTasks[i].taskCB == cb){
                tmo = appTasks[i].timeout;
            }
        }
    }

    return tmo;
}

/****************************************************************************
 * insertAppTask
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 *
void insertAppTask(taskCB_t cb, uint32_t taskTMO) {

    rtc_cntl_t cnt;
    rtc_alrl_t alr;
    rtc_crl_t crl;

    int32_t remain;
    uint32_t diff;
    uint8_t i;

    alr.all = REG_Read(RTC__ALRL);
    cnt.all = REG_Read(RTC__CNTL);

    if(cnt.b.cnt >= alr.b.alr){
        addAppTask(cb, taskTMO);
    }
    else {
        remain = (alr.b.alr - cnt.b.cnt) / 3;
        if(remain > taskTMO){
            diff = remain - taskTMO;
            for(i = 0; i < TIMER_TASKS_NUM; i++){
                if(appTasks[i].used == true){
                    appTasks[i].timeout += diff;
                }
            }
            addAppTask(cb, 0);

            crl.all = REG_Read(RTC__CRL);
            crl.b.cnf = 1; // 1: Enter configuration mode
            REG_Write(RTC__CRL, crl.all);
            REG_Write(RTC__CNTH, 0);
            REG_Write(RTC__CNTL, 0);
            REG_Write(RTC__ALRH, 0);
            REG_Write(RTC__ALRL, (taskTMO * 3));
            crl.b.cnf = 1; // 0: Exit configuration mode
            REG_Write(RTC__CRL, crl.all);
        }
        else {
            addAppTask(cb, (taskTMO - remain));
        }
    }
 }
*/
/****************************************************************************
 * insertAppTask
 *
 * DESCRIPTION:
 *
 * RETURNS:
 *
 */
void insertAppTask(taskCB_t cb, uint32_t taskTMO) {

    uint32_t diff;
    uint8_t i;

    if(sleepTime > 0){
        if(sleepTime > taskTMO){
            diff = sleepTime - taskTMO;
            for(i = 0; i < TIMER_TASKS_NUM; i++){
                if(appTasks[i].used == true){
                    appTasks[i].timeout += diff;
                }
            }
            sleepTime = taskTMO;
            addAppTask(cb, 0);
        }
        else {
            addAppTask(cb, (taskTMO - sleepTime));
        }
    }
    else {
        addAppTask(cb, taskTMO);
    }
}




