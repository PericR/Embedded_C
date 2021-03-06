/*
 * stm32f446_rcc_driver.h
 *
 *  Created on: Jan 23, 2021
 *      Author: robert
 */

#ifndef INC_STM32F446_RCC_DRIVER_H_
#define INC_STM32F446_RCC_DRIVER_H_

#include "stm32f446.h"

uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);

#endif /* INC_STM32F446_RCC_DRIVER_H_ */
