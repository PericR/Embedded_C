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
	uint8_t SPI_DeviceMode;					/*Possible values from @SPI_DeviceMode*/
	uint8_t SPI_BusConfig;					/*Possible values from @SPI_BusConfig*/
	uint8_t SPI_SclkSpeed;					/*Possible values from @SPI_SclkSpeed*/
	uint8_t SPI_DFF;						/*Possible values from @SPI_DFF*/
	uint8_t SPI_CPOL;						/*Possible values from @SPI_CPOL*/
	uint8_t SPI_CPHA;						/*Possible values from @SPI_CPHA*/
	uint8_t SPI_SSM;						/*Possible values from @SPI_SSM*/
} SPI_Config_t;

/*
 *	 This is the handle for SPIx peripheral
 */
typedef struct{
	SPI_RegDef_t *pSPIx;					/*This holds the base address of the SPI port*/
	SPI_Config_t SPI_Config;				/*This holds SPI peripheral configuration settings*/
} SPI_Handle_t;


/*
 * 	@SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER				1
#define SPI_DEVICE_MODE_SLAVE				0

/*
 * 	@SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD					1
#define SPI_BUS_CONFIG_HD					2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY		3

/*
 * 	@SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2					0
#define SPI_SCLK_SPEED_DIV4					1
#define SPI_SCLK_SPEED_DIV8					2
#define SPI_SCLK_SPEED_DIV16				3
#define SPI_SCLK_SPEED_DIV32				4
#define SPI_SCLK_SPEED_DIV64				5
#define SPI_SCLK_SPEED_DIV128				6
#define SPI_SCLK_SPEED_DIV256				7

/*
 * 	@SPI_DFF
 */
#define SPI_DFF_8BITS						0
#define SPI_DFF_16BITS						1

/*
 * 	@SPI_CPOL
 */
#define SPI_CPOL_LOW						0
#define SPI_CPOL_HIGH						1

/*
 * 	@SPI_CPHA
 */
#define SPI_CPHA_FIRST						0
#define SPI_CPHA_SECOND						1

/*
 * 	@SPI_SSM
 */
#define SPI_SSM_DI							0
#define SPI_SSM_EN							1

/*
 * SPI Related Flag Definitions
 */
#define SPI_RXNE_FLAG						(1 << SPI_SR_RXEN)
#define SPI_TXE_FLAG						(1 << SPI_SR_TXE)
#define SPI_CHSIDE_FLAG						(1 << SPI_SR_CHSIDE)
#define SPI_UDR_FLAG						(1 << SPI_SR_UDR)
#define SPI_CRCERR_FLAG						(1 << SPI_SR_CRCERR)
#define SPI_MODF_FLAG						(1 << SPI_SR_MODF)
#define SPI_OVR_FLAG						(1 << SPI_SR_OVR)
#define SPI_BSY_FLAG						(1 << SPI_SR_BSY)
#define SPI_FRE_FLAG						(1 << SPI_SR_FRE)

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
