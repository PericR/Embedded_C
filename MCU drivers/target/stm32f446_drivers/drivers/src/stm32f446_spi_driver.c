/*
 * stm32f446_spi_driver.c
 *
 *  Created on: Dec 1, 2020
 *      Author: Robert
 */

#include "stm32f446_spi_driver.h"

/*
 *	 Peripheral clock setup
 */

/*****************************************************************
 * @fn					- SPI_PeriClockControl
 *
 * @brief				- This function enables or disables peripheral clock for the given SPI peripheral
 *
 * @param[in]			- Base address of the SPI peripheral
 * @param[in]			- ENABLE or DISABLE macros
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pSPIx == SPI1){
			SPI1_PCLK_EN();
		} else if(pSPIx == SPI2){
			SPI2_PCLK_EN();
		} else if(pSPIx == SPI3){
			SPI3_PCLK_EN();
		} else if(pSPIx == SPI4){
			SPI4_PCLK_EN();
		}
	} else if(EnorDi == DISABLE){
		if(pSPIx == SPI1){
			SPI1_PCLK_DI();
		} else if(pSPIx == SPI2){
			SPI2_PCLK_DI();
		} else if(pSPIx == SPI3){
			SPI3_PCLK_DI();
		} else if(pSPIx == SPI4){
			SPI4_PCLK_DI();
		}
	}
}

/*
 *	Init and De-init
 */

/*****************************************************************
 * @fn					- SPI_Init
 *
 * @brief				- This function initialize given SPI peripheral with user values
 *
 * @param[in]			- SPI handle with base address and initialization values
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void SPI_Init(SPI_Handle_t *pSPIHandle){
	uint32_t ControlReg1 = 0;

	//configure device mode
	ControlReg1 |= pSPIHandle->SPI_Config.SPI_DeviceMode << 2;

	//Bus Configuration
	if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD){
		//bidi mode should be cleared
		ControlReg1 &= ~(1 << SPI_CR1_BIDIMODE);
	} else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		//bidi mode should be set
		ControlReg1 |= (1 << SPI_CR1_BIDIMODE);
	} else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		//bidi mode should be cleared
		ControlReg1 &= ~(1 << SPI_CR1_BIDIMODE);
		//rxonly bit must be set
		ControlReg1 |= (1 << SPI_CR1_RXONLY);
	}

	//Serial clk Configuration
	ControlReg1 |= (pSPIHandle->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR);

	//Data Frame Format Configuration
	ControlReg1 |= (pSPIHandle->SPI_Config.SPI_DFF << SPI_CR1_DFF);

	//CPOL Configuration
	ControlReg1 |= (pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL);

	//CPHA Configuration
	ControlReg1 |= (pSPIHandle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA);

	//Software Slave Select Configuration
	ControlReg1 |= (pSPIHandle->SPI_Config.SPI_SSM << SPI_CR1_SSM);

	pSPIHandle->pSPIx->CR1 = ControlReg1;
}

/*****************************************************************
 * @fn					- SPI_DeInit
 *
 * @brief				- This function resets given SPI peripheral
 *
 * @param[in]			- Base address of the SPI peripheral
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx){
	if(pSPIx == SPI1){
		SPI1_REG_RESET();
	} else if(pSPIx == SPI2){
		SPI2_REG_RESET();
	} else if(pSPIx == SPI3){
		SPI3_REG_RESET();
	} else if(pSPIx == SPI4){
		SPI4_REG_RESET();
	}
}

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
