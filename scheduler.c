/*
 * scheduler.c
 *
 *  Created on: Jul 10, 2019
 *      Author: lucasbecker
 */

#include "vector.h"
#include "scheduler.h"

static uint32_t current_time = 0;
static vector tasks;
static vector candidates;

Task_TypeDef * scheduler_SelectFunction();

void scheduler_Init()
{
	vector_init(&tasks);
}


void scheduler_AddTask(Task_TypeDef * task)
{
	vector_add(&tasks, task);
}

void scheduler_Mgr()
{
	vector_init(&candidates);
	for(uint32_t i = 0; i < vector_total(&tasks); i++)
	{
		Task_TypeDef * task = (Task_TypeDef *)vector_get(&tasks, i);
		if((current_time - task->last_event) >= task->period)
		{
			vector_add(&candidates, task);
		}
	}
	if(candidates.total > 0)
	{
		Task_TypeDef * selectedTask = (Task_TypeDef *)scheduler_SelectFunction();
		selectedTask->last_event = current_time;
		selectedTask->function();
	}

	vector_free(&candidates);
}

Task_TypeDef * scheduler_SelectFunction()
{
	Task_TypeDef * task_tmp = (Task_TypeDef *)vector_get(&candidates, 0);
	for(uint32_t i = 0; i < vector_total(&candidates); i++)
	{
		Task_TypeDef * task = (Task_TypeDef *)vector_get(&candidates, i);
		if((current_time - task->last_event) > task->period)
		{
			task_tmp = task;
			break;
		}
		else if(task->priority < task_tmp->priority)
		{
			task_tmp = task;
		}
	}
	return task_tmp;
}

void shceduler_UpCurrentTime()
{
	if(current_time == UINT32_MAX)
	{
		current_time = 0;
	}
	else
	{
		current_time++;
	}
}
