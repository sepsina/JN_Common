/*
 * appTasks.h
 *
 *  Created on: 22. pro 2021.
 *      Author: Sep
 */

#ifndef APPTASKS_H_
#define APPTASKS_H_

//#include "jendefs.h"
#include "stdbool.h"
#include "stdint.h"

#define TIMER_TASKS_NUM    16

#define SLEEP_TIME      20
#define MIN_SLEEP_TIME  5

typedef void (*taskCB_t)(void);

typedef struct {
    bool used;
    uint32_t timeout;
    taskCB_t taskCB;
} appTask_t;


extern appTask_t appTasks[TIMER_TASKS_NUM];

extern uint16_t appTasksHandler(void);
extern void initAppTask(void);
extern int8_t addAppTask(taskCB_t cb,
                         uint32_t timeout);
extern void delAppTask(taskCB_t cb);
extern uint32_t getTaskTMO(taskCB_t cb);
extern void insertAppTask(taskCB_t cb, uint32_t taskTMO);

#endif /* APPTASKS_H_ */
