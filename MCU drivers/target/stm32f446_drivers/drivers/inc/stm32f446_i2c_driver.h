/*
 * stm32f446_i2c_driver.h
 *
 *  Created on: Dec 26, 2020
 *      Author: robert
 */

#ifndef INC_STM32F446_I2C_DRIVER_H_
#define INC_STM32F446_I2C_DRIVER_H_

#include "stm32f446.h"


typedef struct {
	uint32_t I2C_SCLSpeed;						/*Possible values from @GPIO_PIN_NUMBERS*/
	uint8_t I2C_DeviceAddress;					/*Possible values from @GPIO_PIN_NUMBERS*/
	uint32_t I2C_ACKControl;					/*Possible values from @GPIO_PIN_NUMBERS*/
	uint32_t I2C_FMDutyCycle;					/*Possible values from @GPIO_PIN_NUMBERS*/
}I2C_Config_t;

typedef struct{
	I2C_RegDef_t *pI2Cx;						/*This holds the base address of the I2C port to which the pin belongs*/
	I2C_Config_t I2C_Config;					/*This holds I2C configuration settings*/
}I2C_Handle_t;


#endif /* INC_STM32F446_I2C_DRIVER_H_ */
