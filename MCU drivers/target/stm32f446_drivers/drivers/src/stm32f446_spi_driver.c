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

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/*****************************************************************
 * @fn					- SPI_SendData
 *
 * @brief				- This function sends data trough SPI peripheral
 *
 * @param[in]			- Base address of the SPI peripheral
 * @param[in]			- Transmiter buffer data
 * @param[in]			- Lenght of send data
 *
 * @return				- none
 *
 * @note				- This is blocking call
 *
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){
	while(Len > 0){
		//Wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);
		//Check DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF)){
			//16 bit data frame format
			pSPIx->DR = *((uint16_t*) pTxBuffer);
			Len--;
			Len--;
			(uint16_t*) pTxBuffer++;
		} else{
			//8 bit data frame format
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){
	while(Len > 0){
			//Wait until RXNE is set
			while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);
			//Check DFF bit in CR1
			if(pSPIx->CR1 & (1 << SPI_CR1_DFF)){
				//16 bit data frame format
				*((uint16_t*) pRxBuffer) = pSPIx->DR;
				Len--;
				Len--;
				(uint16_t*) pRxBuffer++;
			} else{
				//8 bit data frame format
				*pRxBuffer = pSPIx->DR;
				Len--;
				pRxBuffer++;
			}
		}
}

/*
 * 	IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(IRQNumber <= 31){
			*NVIC_ISER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber <= 63){
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber > 63 && IRQNumber < 96){
			*NVIC_ISER2 |= (1 << (IRQNumber % 32));
		}
	}else{
		if(IRQNumber <= 31){
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber <= 63){
			*NVIC_ICER1 |= (1 << IRQNumber % 32);
		}else if(IRQNumber > 63 && IRQNumber < 96){
			*NVIC_ICER2 |= (1 << IRQNumber % 32);
		}
	}
}
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

/*
 * 	Other Peripheral Control APIs
 */

/*****************************************************************
 * @fn					- SPI_PeripheralControl
 *
 * @brief				- This function configures SPI Peripheral
 *
 * @param[in]			- Base address of the SPI peripheral
 * @param[in]			- Enable or disable
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	} else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

/*****************************************************************
 * @fn					- SPI_SSI_Config
 *
 * @brief				- This function configures SPI SSI bit
 *
 * @param[in]			- Base address of the SPI peripheral
 * @param[in]			- Enable or disable
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void SPI_SSI_Config(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	} else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

/*****************************************************************
 * @fn					- SPI_SSOE_Config
 *
 * @brief				- This function configures SPI SSOE bit
 *
 * @param[in]			- Base address of the SPI peripheral
 * @param[in]			- Enable or disable
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void SPI_SSOE_Config(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	} else{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}
