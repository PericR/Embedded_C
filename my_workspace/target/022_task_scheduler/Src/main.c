/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include<stdio.h>
#include<stdint.h>

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);

void init_systick_timer(uint32_t tick_hz);

#define SIZE_TASK_STACK			1024U
#define SIZE_SCHEDULER_STACK	1024U

#define SRAM_START				0x20000000u
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

int main(void)
{
	init_systick_timer(TICK_HZ);

	for(;;);
}

void task1_handler(void){
	while(1){
		printf("This is task1\n");
	}
}

void task2_handler(void){
	while(1){
		printf("This is task2\n");
	}
}

void task3_handler(void){
	while(1){
		printf("This is task3\n");
	}
}

void task4_handler(void){
	while(1){
		printf("This is task4\n");
	}
}

void init_systick_timer(uint32_t tick_hz){
	uint32_t *pST_RVR = (uint32_t*)0xE000E014;
	uint32_t *pST_CSR = (uint32_t*)0xE000E010;

	uint32_t count_value = (SYSTICK_TIM_CLK / tick_hz) - 1;

	//clear ST_RVR
	*pST_RVR &= ~(0x00FFFFFF);
	//load ST_RVR
	*pST_RVR |= count_value;

	//Do some settings
	*pST_CSR |= (1 << 2);//select processor clock source
	*pST_CSR |= (1 << 1);//Enables SysTick exception request

	//enable SYS_TICK
	*pST_CSR |= (1 << 0);//enables the counter
}

void SysTick_Handler(void){

}

