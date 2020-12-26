/*
 * stm32f446_i2c_driver.h
 *
 *  Created on: Dec 26, 2020
 *      Author: robert
 */

#ifndef INC_STM32F446_I2C_DRIVER_H_
#define INC_STM32F446_I2C_DRIVER_H_

#include "stm32f446.h"

/*
 * Configuration structure for I2C peripheral
 */
typedef struct {
	uint32_t I2C_SCLSpeed;						/*Possible values from @I2C_SCLSPEED*/
	uint8_t I2C_DeviceAddress;					/*Provided by user*/
	uint32_t I2C_ACKControl;					/*Possible values from @I2C_ACKCONTROL*/
	uint32_t I2C_FMDutyCycle;					/*Possible values from @I2C_FMDUTYCYCLE*/
}I2C_Config_t;

/*
 * Handle structure for I2C peripheral
 */
typedef struct{
	I2C_RegDef_t *pI2Cx;						/*This holds the base address of the I2C port to which the pin belongs*/
	I2C_Config_t I2C_Config;					/*This holds I2C configuration settings*/
}I2C_Handle_t;


/*
 * @I2C_SCLSPEED Expressed in Hz
 */
#define I2C_SCL_SPEED_SM						100000
#define I2C_SCL_SPEED_FM2K						200000
#define I2C_SCL_SPEED_FM4K						400000

/*
 * @I2C_ACKCONTROL
 */
#define I2C_ACK_ENABLE							1
#define I2C_ACK_DISABLE							0

/*
 * @I2C_FMDUTYCYCLE
 */
#define I2C_FM_DUTY_2							0
#define I2C_FM_DUTY_16_9						1

#endif /* INC_STM32F446_I2C_DRIVER_H_ */
