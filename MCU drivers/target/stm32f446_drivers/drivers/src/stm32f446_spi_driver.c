/*
 * stm32f446_spi_driver.c
 *
 *  Created on: Dec 1, 2020
 *      Author: Robert
 */

#include "stm32f446_spi_driver.h"


/*
 * Helper functions for SPI_IRQHandling
 */

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_interrupt_handle(SPI_Handle_t *pSPIHandle);

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
	uint32_t spi_cr1 = 0;

	//configure device mode
	spi_cr1 |= pSPIHandle->SPI_Config.SPI_DeviceMode << 2;

	//Bus Configuration
	if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD){
		//bidi mode should be cleared
		spi_cr1 &= ~(1 << SPI_CR1_BIDIMODE);
	} else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		//bidi mode should be set
		spi_cr1 |= (1 << SPI_CR1_BIDIMODE);
	} else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		//bidi mode should be cleared
		spi_cr1 &= ~(1 << SPI_CR1_BIDIMODE);
		//rxonly bit must be set
		spi_cr1 |= (1 << SPI_CR1_RXONLY);
	}

	//Serial clk Configuration
	spi_cr1 |= (pSPIHandle->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR);

	//Data Frame Format Configuration
	spi_cr1 |= (pSPIHandle->SPI_Config.SPI_DFF << SPI_CR1_DFF);

	//CPOL Configuration
	spi_cr1 |= (pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL);

	//CPHA Configuration
	spi_cr1 |= (pSPIHandle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA);

	//Software Slave Select Configuration
	spi_cr1 |= (pSPIHandle->SPI_Config.SPI_SSM << SPI_CR1_SSM);

	pSPIHandle->pSPIx->CR1 = spi_cr1;
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
		while(SPI_GetFlagStatus(pSPIx, SPI_FLAG_TXE) == FLAG_RESET);
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
			while(SPI_GetFlagStatus(pSPIx, SPI_FLAG_RXNE) == FLAG_RESET);
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

/*****************************************************************
 * @fn					- SPI_IRQInterruptConfig
 *
 * @brief				- This function configures interrupt registers
 *
 * @param[in]			- IRQ number
 * @param[in]			- ENABLE or DISABLE value
 *
 * @return				- none
 *
 * @note				- none
 *
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

/*****************************************************************
 * @fn					- SPI_IRQPriorityConfig
 *
 * @brief				- This function configures priority registers
 *
 ** @param[in]			- IRQ  number
 * @param[in]			- IRQ priority number
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_value = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_value);
}

/*****************************************************************
 * @fn					- SPI_IRQHandling
 *
 * @brief				- This function handles interrupts
 *
* @param[in]			- SPI handle with base address and initialization values
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle){
	//check TXE status
	uint8_t txe_flag = pSPIHandle->pSPIx->SR & (1 << SPI_SR_TXE);
	uint8_t txeie_flag = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);

	if(txe_flag && txeie_flag){
		//handle TXE
		spi_txe_interrupt_handle(pSPIHandle);
	}

	//check RXNE status
	uint8_t rxne_flag = pSPIHandle->pSPIx->SR & (1 << SPI_SR_RXNE);
	uint8_t rxneie_flag = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);

	if(rxne_flag && rxneie_flag){
		//handle RXNE
		spi_rxne_interrupt_handle(pSPIHandle);
	}

	//check OVR status
	uint8_t ovr_flag = pSPIHandle->pSPIx->SR & (1 << SPI_SR_OVR);
	uint8_t errie_flag = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);

	if(ovr_flag && errie_flag){
		//handle OVR
		spi_ovr_interrupt_handle(pSPIHandle);
	}
}

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

/*
 * Data send and receive in interupt mode
 */

/*****************************************************************
 * @fn					- SPI_SendData_IT
 *
 * @brief				- This function sends data trough SPI peripheral
 *
 * @param[in]			- SPI handle with base address and initialization values
 * @param[in]			- Transmiter buffer data
 * @param[in]			- Lenght of send data
 *
 * @return				- none
 *
 * @note				- This is Interrupt mode
 *
 */
uint8_t SPI_SendData_IT(SPI_Handle_t *pHandle, uint8_t *pTxBuffer, uint32_t Len){
	uint8_t SPI_state = pHandle->TxState;

	if(SPI_state != SPI_BSY_IN_TX){
		//Save TxBuffer address and length in global variable
		pHandle->pTxBuffer = pTxBuffer;
		pHandle->TxLen = Len;

		//Mark the SPI state as busy in transmission so no other code can use same SPI peripheral until transmission is over
		pHandle->TxState = SPI_BSY_IN_TX;

		//Enable TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);

		//Data transmission will be handled by ISR code
	}

	return SPI_state;
}

/*****************************************************************
 * @fn					- SPI_ReceiveData_IT
 *
 * @brief				- This function sends data trough SPI peripheral
 *
 * @param[in]			- SPI handle with base address and initialization values
 * @param[in]			- Transmiter buffer data
 * @param[in]			- Lenght of send data
 *
 * @return				- none
 *
 * @note				- This is Interrupt mode
 *
 */
uint8_t SPI_ReceiveData_IT(SPI_Handle_t *pHandle, uint8_t *pRxBuffer, uint32_t Len){
	uint8_t SPI_state = pHandle->RxState;

	if(SPI_state != SPI_BSY_IN_RX){
		//Save TxBuffer address and length in global variable
		pHandle->pRxBuffer = pRxBuffer;
		pHandle->RxLen = Len;

		//Mark the SPI state as busy in transmission so no other code can use same SPI peripheral until transmission is over
		pHandle->RxState = SPI_BSY_IN_RX;

		//Enable TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);

		//Data transmission will be handled by ISR code
	}

	return SPI_state;
}

/*
 * Helper functions implementations for SPI_IRQHandling
 */

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle){
	//check DFF
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF)){
		//16 bit dff
		//load data in SPI DR
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	} else {
		//8 bit dff
		//load data in SPI DR
		pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->pTxBuffer++;
	}

	if(!pSPIHandle->TxLen){
		//when TxLen is zero, close the SPI transmission and inform application that Tx is over
		//this will stop interrupts from TXE flag
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);

		pSPIHandle->pTxBuffer = NULL;
		pSPIHandle->TxLen = 0;
		pSPIHandle->TxState = SPI_READY;

		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}
}

static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle){
	//check DFF
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF)){
		//16 bit dff
		//load data from SPI DR
		*((uint16_t*)pSPIHandle->pRxBuffer) = (uint16_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->RxLen--;
		(uint16_t*)pSPIHandle->pRxBuffer--;
	} else {
		//8 bit dff
		//load data in SPI DR
		*(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer--;
	}

	if(!pSPIHandle->RxLen){
		//when TxLen is zero, close the SPI transmission and inform application that Rx is over
		//this will stop interrupts from RXNE flag
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}
}

static void spi_ovr_interrupt_handle(SPI_Handle_t *pSPIHandle){
	//Clear OVR error by reading DR, then SR
	if(pSPIHandle->TxState != SPI_BSY_IN_TX){
		SPI_ClearOVRFlag(pSPIHandle->pSPIx);
	}

	//inform the application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);
}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx){
	uint8_t dummy_read;
	dummy_read = pSPIx->DR;
	dummy_read = pSPIx->SR;
	(void)dummy_read;
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);

	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;
}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);

	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;
}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv){
	//weak function, user is expected to implement it in application
}
