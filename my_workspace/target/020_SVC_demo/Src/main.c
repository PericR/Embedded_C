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

int main(void)
{
	__asm volatile("SVC #8");

	uint32_t data;
	__asm("MOV %0, r0": "=r"(data) ::);

	printf("Value of SVC + 4: %ld\n", data);

	for(;;);
}

__attribute__((naked)) void SVC_Handler(void)
{
	__asm ("MRS r0, MSP");
	__asm ("B SVC_Handler_c");
}

void SVC_Handler_c(uint32_t *pBase_stack_frame)
{
	printf("In SVC handler!\n");

	uint8_t *pRetturn_address = (uint8_t*)pBase_stack_frame[6];
	pRetturn_address -= 2;

	uint8_t svc_number = *pRetturn_address;
	printf("SVC number: %d\n", svc_number);

	svc_number += 4;

	pBase_stack_frame[0] = svc_number;
}