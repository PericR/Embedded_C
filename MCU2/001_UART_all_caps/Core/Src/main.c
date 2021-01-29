/*
 * main.c
 *
 *  Created on: Jan 29, 2021
 *      Author: robert
 */

#include "stm32f4xx.h"
#include "main.h"

void SystemClockConfig(void);
void UART2_Init(void);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void Error_handler(void);

UART_HandleTypeDef huart2;

int main(void)
{
	HAL_Init();
	SystemClockConfig();

	UART2_Init();
}

void SystemClockConfig(void)
{

}

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		//UART2 not initialized
		Error_handler();
	}
}

void Error_handler(void)
{
	while(1);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	//Here we are going to do low level initialization of USART2 peripheral
	GPIO_InitTypeDef gpio_uart2;
	//1. Enable the clock for USART2 peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	//2. Do the pin muxing configurations
	gpio_uart2.Mode = GPIO_MODE_AF_PP;
	gpio_uart2.Pull = GPIO_PULLUP;
	gpio_uart2.Speed = GPIO_SPEED_LOW;
	gpio_uart2.Alternate = GPIO_AF7_USART2;
	gpio_uart2.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOA, &gpio_uart2);	//UART2_TX
	gpio_uart2.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio_uart2);	//UART2_RX

	//3. Enable the IRQ and set up the priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}




