/*
 * main.h
 *
 *  Created on: Jun 25, 2020
 *      Author: robert
 */

#ifndef MAIN_H_
#define MAIN_H_

#define MAX_TASKS				4

#define SIZE_TASK_STACK			1024U
#define SIZE_SCHEDULER_STACK	1024U

#define SRAM_START				0x20000000U
#define SRAM_SIZE				((128) * (1024))
#define SRAM_END				((SRAM_START) + (SRAM_SIZE))

#define T1_STACK_START			SRAM_END
#define T2_STACK_START			((SRAM_END) - (1 * SIZE_TASK_STACK))
#define T3_STACK_START			((SRAM_END) - (2 * SIZE_TASK_STACK))
#define T4_STACK_START			((SRAM_END) - (3 * SIZE_TASK_STACK))
#define SCHEDULER_STACK_START	((SRAM_END) - (4 * SIZE_TASK_STACK))

#define TICK_HZ 				1000U
#define HSI_CLOCK				16000000U
#define SYSTICK_TIM_CLK			HSI_CLOCK

#define DUMMY_XPRS				0x01000000U

#define TASK_RUNNING_STATE 0x00
#define TASK_BLOCKED_STATE 0xFF

#endif /* MAIN_H_ */
