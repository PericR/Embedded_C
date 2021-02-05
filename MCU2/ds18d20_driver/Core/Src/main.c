/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

//Initialization functions
void sd18b20_gpio_init(void);
uint8_t ds18b20_init_phase(void);

//microseconds timer
void delay_us (uint32_t u_second);

//helper functions for GPIO I/O
void set_pin_as_out(GPIO_TypeDef *gpio_port, uint8_t gpio_pin);
void set_pin_as_in(GPIO_TypeDef *gpio_port, uint8_t gpio_pin);
void write_pin(GPIO_TypeDef *gpio_port, uint8_t gpio_pin, uint8_t value);
uint8_t read_pin(GPIO_TypeDef *gpio_port, uint8_t gpio_pin);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();


  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);
  sd18b20_gpio_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  ds18b20_init_phase();

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 84-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/*********************************************************************************************************/
//My functions will be kept here


/*********************************************************************
 * @fn      		  - delay_us
 *
 * @brief             - This function delays program by given number of microseconds
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
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while(__HAL_TIM_GET_COUNTER(&htim1) < u_seconds);
}

/*********************************************************************
 * @fn      		  - sd18b20_gpio_init
 *
 * @brief             - This function sets gpio pin used for OneWire communication
 *
 * @param[in]         - none
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void sd18b20_gpio_init(void)
{
	GPIO_InitTypeDef ds_gpio;

	ds_gpio.Pin = DS18B20_PIN;
	ds_gpio.Mode = GPIO_MODE_OUTPUT_OD;
	ds_gpio.Pull = GPIO_NOPULL;
	ds_gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(DS18B20_PORT, &ds_gpio);

}

/*********************************************************************
 * @fn      		  - ds18b20_init_phase
 *
 * @brief             - This function serves as Initialization phase
 * 						It scans for device on data line
 *
 * @param[in]         - none
 *
 * @return            -  1 if device is found, 0 if not
 *
 * @Note              -  none

 */
uint8_t ds18b20_init_phase(void)
{
	uint8_t response = 0;

	set_pin_as_out(DS18B20_PORT, DS18B20_PIN);

	write_pin(DS18B20_PORT, DS18B20_PIN, 0);	//pull data line to LOW for 480-950 microseconds (RESET signal)
	delay_us(550);

	set_pin_as_in(DS18B20_PORT, DS18B20_PIN);
	delay_us(80);

	if(!read_pin(DS18B20_PORT, DS18B20_PIN))	//scan for PRESENCE signal (LOW data line)
	{
		response = 1;
	}

	delay_us(200);
	return response;
}

/*********************************************************************
 * @fn      		  - set_pin_as_out
 *
 * @brief             - This function sets gpio moder to output
 *
 * @param[in]         - GPIO_TypeDef *gpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void set_pin_as_out(GPIO_TypeDef *gpio_port, uint8_t gpio_pin)
{
	//reset then set mode as output
	gpio_port->MODER &= ~(0x3 << (2 * gpio_pin));
	gpio_port->MODER |= (1 << (2 * gpio_pin));
}

/*********************************************************************
 * @fn      		  - set_pin_as_in
 *
 * @brief             - This function sets gpio moder to input
 *
 * @param[in]         - GPIO_TypeDef *gpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void set_pin_as_in(GPIO_TypeDef *gpio_port, uint8_t gpio_pin)
{
	//set pin as in
	gpio_port->MODER &= ~(0x3 << (2 * gpio_pin));
}

/*********************************************************************
 * @fn      		  - write_pin
 *
 * @brief             - This function sets gpio ODR to HIGH or LOW
 *
 * @param[in]         - GPIO_TypeDef *gpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 * 						uint8_t value 1 or 0 signal to be set
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void write_pin(GPIO_TypeDef *gpio_port, uint8_t gpio_pin, uint8_t value)
{
	if(value == 1)
	{
		gpio_port->ODR |= (1 << gpio_pin);
	}
	else
	{
		gpio_port->ODR &= ~(1 << gpio_pin);
	}
}

/*********************************************************************
 * @fn      		  - read_pin
 *
 * @brief             - This function read gpio IDR
 *
 * @param[in]         - GPIO_TypeDef *gpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  returns value from IDR, 1 or 0
 *
 * @Note              -  none

 */
uint8_t read_pin(GPIO_TypeDef *gpio_port, uint8_t gpio_pin)
{
	uint8_t value = (uint8_t)((gpio_port->IDR >> gpio_pin) & 0x00000001);
	return value;
}

/* USER CODE END 4 */
/*********************************************************************************************************/



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	while(1);
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
