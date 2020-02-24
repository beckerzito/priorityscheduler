/*
 * scheduler.h
 *
 *  Created on: Jul 10, 2019
 *      Author: lucasbecker
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

typedef void (*func)(void);

typedef enum
{
	PRIORITY_HIGH = 0,
	PRIORITY_MID = 1,
	PRIORITY_LOW = 2
} Task_Priority;

typedef struct
{
	Task_Priority priority;
	int period;
	int last_event;
	func function;
}Task_TypeDef;

void scheduler_Init();
void scheduler_AddTask(Task_TypeDef * task);
void scheduler_Mgr();
void shceduler_UpCurrentTime();

#ifdef __cplusplus
}
#endif
#endif /* INC_SCHEDULER_H_ */
