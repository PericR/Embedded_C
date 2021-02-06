/*
 * delay.c
 *
 *  Created on: Feb 6, 2021
 *      Author: robert
 */

#include "delay.h"


/*********************************************************************
 * @fn      		  - MX_TIM1_Init
 *
 * @brief             - This function setup TIM1 to be used as microseconds delay timer
 *
 * @param[in]         - TIM_HandleTypeDef *htim1
 * 						Handle structure to TIM1 global variable
 *
 * @return            -  Error, 1 if successful, 0 if failed
 *
 * @Note              -  this is generated with MX cube and modified to meet requirements

 */
uint8_t MX_TIM1_Init(TIM_HandleTypeDef *htim1)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1->Instance = TIM1;
  htim1->Init.Prescaler = 84-1;
  htim1->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1->Init.Period = 0xffff-1;
  htim1->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1->Init.RepetitionCounter = 0;
  htim1->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(htim1) != HAL_OK)
  {
    return 0;
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(htim1, &sClockSourceConfig) != HAL_OK)
  {
	  return 0;
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(htim1, &sMasterConfig) != HAL_OK)
  {
	  return 0;
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  return 1;
}

/*********************************************************************
 * @fn      		  - delay_us
 *
 * @brief             - This function delays program by given number of microseconds using TIM1
 *
 * @param[in]         - uint32_t u_seconds
 * 						number of microseconds program will wait before continuing execution
 *
 * @return            -  none
 *
 * @Note              -  tested with salea logic analyzer, works good enough (1-3 microseconds variability)

 */
void delay_us (uint32_t u_seconds)
{
	TIM_HandleTypeDef htim1;
	htim1.Instance = TIM1;

	__HAL_TIM_SET_COUNTER(&htim1, 0);			//this func starts counter at 0 and waits until its greater than u_seconds parameter
	while(__HAL_TIM_GET_COUNTER(&htim1) < u_seconds);
}
