/*
 * delay.h
 *
 *  Created on: Feb 6, 2021
 *      Author: robert
 */

#include "stm32f4xx_hal.h"

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

uint8_t MX_TIM1_Init(TIM_HandleTypeDef *pHtim1);
void Delay_us (uint32_t u_second);

#endif /* INC_DELAY_H_ */
