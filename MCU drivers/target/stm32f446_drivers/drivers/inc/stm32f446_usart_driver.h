/*
 * stm32f446_usart_driver.h
 *
 *  Created on: Jan 21, 2021
 *      Author: robert
 */

#ifndef INC_STM32F446_USART_DRIVER_H_
#define INC_STM32F446_USART_DRIVER_H_

#include "stm32f446.h"

/*
 * Configuration structure for USART peripheral
 */
typedef struct{
	uint8_t USART_Mode;										/*Posible values from*/
	uint32_t USART_Baud;									/*Posible values from*/
	uint8_t USART_NoOfStopBits;								/*Posible values from*/
	uint8_t USART_WordLength;								/*Posible values from*/
	uint8_t USART_ParityControl;							/*Posible values from*/
	uint8_t USART_HWFlowControl;							/*Posible values from*/
}USART_Config_t;

/*
 * Handle structure for USART peripheral
 */
typedef struct{
	USART_RegDef_t *pUSARTx;								/*This holds the base address of the USART/UART port to which the pin belongs*/
	USART_Config_t USART_Config								/*This holds USART/UART configuration settings*/
}USART_Handle_t;

#endif /* INC_STM32F446_USART_DRIVER_H_ */
