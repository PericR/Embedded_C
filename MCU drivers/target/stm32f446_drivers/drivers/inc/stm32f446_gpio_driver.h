/*
 * stm32f446_gpio_driver.h
 *
 *  Created on: Nov 10, 2020
 *      Author: robert
 */

#ifndef INC_STM32F446_GPIO_DRIVER_H_
#define INC_STM32F446_GPIO_DRIVER_H_

#include "stm32f446.h"
#include <stdint.h>

typedef struct{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
} GPIO_PinConfig_t;

/*
 *	 This is the handle for GPIO pin
 */
typedef struct{
	GPIO_RegDef_t *pGPIOx;					/*This holds the base address of the GPIO port to which the pin belongs*/
	GPIO_PinConfig_t GPIO_PinConfig;		/*This holds GPIO pin configuration settings*/
} GPIO_Handle_t;


/**************************************************************************************************************
 * 										APIs supported by this driver
 *
 * ***********************************************************************************************************/

/*
 *	 Peripheral clock setup
 */
void GPIO_PeriClockControl(void);

/*
 *	Init and De-init
 */
void GPIO_Init(void);
void GPIO_DeInit(void);

/*
 *	Data read and write
 */
void GPIO_ReadFromInputPin(void);
void GPIO_ReadFromInputPort(void);
void GPIO_WriteToOutputPin(void);
void GPIO_WriteToOutputPort(void);
void GPIO_ToggleOutputPin(void);

/*
 *	IRQ configuration and ISR handling
 */
void GPIO_IRQConfig(void);
void GPIO_IRQHandling(void);



#endif /* INC_STM32F446_GPIO_DRIVER_H_ */
