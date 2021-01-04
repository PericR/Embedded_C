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
	uint8_t *pTxBuffer;							/*To store application Tx Buffer address*/
	uint8_t *pRxBuffer;							/*To store application Rx Buffer address*/
	uint32_t TxLen;								/*Length of Tx*/
	uint32_t RxLen;								/*Length of Rx*/
	uint8_t TxRxState;							/*To store communication state*/
	uint8_t DevAddress;							/*To store slave/device address*/
	uint32_t RxSize;							/*To store Rx size*/
	uint32_t Sr;								/*Repeated start value*/
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

/*
 * I2C related status flags definition
 */
#define I2C_FLAG_SB								(1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR							(1 << I2C_SR1_ADDR)
#define I2C_FLAG_BTF							(1 << I2C_SR1_BTF)
#define I2C_FLAG_ADD10							(1 << I2C_SR1_ADD10)
#define I2C_FLAG_STOPF							(1 << I2C_SR1_STOPF)
#define I2C_FLAG_RXNE							(1 << I2C_SR1_RxNE)
#define I2C_FLAG_TXE							(1 << I2C_SR1_TxNE)
#define I2C_FLAG_BERR							(1 << I2C_SR1_BERR)
#define I2C_FLAG_ARLO							(1 << I2C_SR1_ARLO)
#define I2C_FLAG_AF								(1 << I2C_SR1_AF)
#define I2C_FLAG_OVR							(1 << I2C_SR1_OVR)
#define I2C_FLAG_PECERR							(1 << I2C_SR1_PECERR)
#define I2C_FLAG_TIMEOUT						(1 << I2C_SR1_TIMEOUT)
#define I2C_FLAG_SMBALERT						(1 << I2C_SR1_SMBALERT)

/*
 * I2C application states
 */
#define I2C_READY								0
#define I2C_BUSY_IN_RX							1
#define I2C_BUSY_IN_TX							2

/*
 * Some other macros
 */
#define I2C_ENABLE_SR							SET
#define I2C_DISABLE_SR							RESET

/**************************************************************************************************************
 * 										APIs supported by this driver
 *
 * ***********************************************************************************************************/

/*
 *	 Peripheral clock setup
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/*
 *	Init and De-init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * 	Data Send and Receive
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

uint8_t I2C_MasterSendData_IT(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
uint8_t I2C_MasterReceiveData_IT(I2C_Handle_t *pI2CHandle, uint8_t *pRxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

/*
 * 	IRQ Configuration and ISR handling
 */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

/*
 * 	Other Peripheral Control APIs
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);
void I2C_ManageAcking(I2C_RegDef_t *pI2CX, uint8_t EnOrDi);

/*
 * Application callback
 */
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv);

#endif /* INC_STM32F446_I2C_DRIVER_H_ */
