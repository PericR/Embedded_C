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

#include<stdint.h>

int main(void)
{
	uint32_t *pClkCtrlReg = (uint32_t*)0x40023830;
	uint32_t *pPortAModeReg = (uint32_t*)0x40020000;
	uint32_t *pPortAOutReg = (uint32_t*)0x40020014;

	//Enable the clock for GPIOA peripheral in the AHB1ENR
	*pClkCtrlReg = *pClkCtrlReg | 1;

	//configure the mode of the IO pin as output
	*pPortAModeReg = *pPortAModeReg & ~(3 << 10); // set 10th and 11th bit to zero
	*pPortAModeReg = *pPortAModeReg | (1 << 10); // set 10th bit to 1

	//set 10th bit of the output data register to makeI/O pin 5 as HIGH
	*pPortAOutReg = *pPortAOutReg | (1 << 5);

	for(;;);
}
