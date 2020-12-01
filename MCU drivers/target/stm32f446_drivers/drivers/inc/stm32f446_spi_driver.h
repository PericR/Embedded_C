/*
 * stm32f446_spi_driver.h
 *
 *  Created on: Dec 1, 2020
 *      Author: Robert
 */

#ifndef INC_STM32F446_SPI_DRIVER_H_
#define INC_STM32F446_SPI_DRIVER_H_

#include "stm32f446.h"
#include <stdint.h>
/*
 *	Configuration structure for SPIx peripheral
 */
typedef struct{
	uint8_t SPI_DeviceMode;					/**/
	uint8_t SPI_BusConfig;					/**/
	uint8_t SPI_SclkSpeed;					/**/
	uint8_t SPI_DFF;						/**/
	uint8_t SPI_CPOL;						/**/
	uint8_t SPI_CPHA;						/**/
	uint8_t SPI_SSM;						/**/
} SPI_PinConfig_t;

/*
 *	 This is the handle for SPIx peripheral
 */
typedef struct{
	SPI_RegDef_t *pSPIx;					/*This holds the base address of the SPI port*/
	SPI_PinConfig_t SPI_PinConfig;			/*This holds SPI peripheral configuration settings*/
} SPI_Handle_t;


/**************************************************************************************************************
 * 										APIs supported by this driver
 *
 * ***********************************************************************************************************/

/*
 *	 Peripheral clock setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 *	Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * 	Data Send and Receive
 */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/*
 * 	IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

/*
 * 	Other Peripheral Control APIs
 */

#endif /* INC_STM32F446_SPI_DRIVER_H_ */
