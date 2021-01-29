/*
 * main.c
 *
 *  Created on: Jan 29, 2021
 *      Author: robert
 */

#include "stm32f4xx.h"
#include "main.h"

void SystemClockConfig(void);

int main(void)
{
	HAL_Init();
	SystemClockConfig();
}

void SystemClockConfig(void)
{

}



