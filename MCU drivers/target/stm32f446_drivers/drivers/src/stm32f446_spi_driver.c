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
void SPI_Init(SPI_Handle_t *pSPIHandle);

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
