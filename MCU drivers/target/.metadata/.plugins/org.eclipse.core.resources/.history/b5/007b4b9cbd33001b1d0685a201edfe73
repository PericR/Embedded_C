/*
 * stm32f446_spi_driver.h
 *
 *  Created on: Dec 1, 2020
 *      Author: robert
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
	GPIO_RegDef_t *pSPIx;					/*This holds the base address of the SPI port*/
	GPIO_PinConfig_t SPI_PinConfig;			/*This holds SPI peripheral configuration settings*/
} SPI_Handle_t;



#endif /* INC_STM32F446_SPI_DRIVER_H_ */
