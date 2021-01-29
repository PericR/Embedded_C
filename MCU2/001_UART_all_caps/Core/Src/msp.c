/*
 * msp.c
 *
 *  Created on: Jan 29, 2021
 *      Author: robert
 */

#include "stm32f4xx.h"

void HAL_MspInit(void)
{
	//Here we will keep low level processor specific inits
	//1. Configure priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= (0X7 << 16);		//usage fault, memory fault, bus fault

	//3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}
