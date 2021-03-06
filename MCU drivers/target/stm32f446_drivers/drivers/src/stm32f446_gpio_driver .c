/*
 * stm32f446_gpio_driver .c
 *
 *  Created on: Nov 10, 2020
 *      Author: Robert
 */

#include "stm32f446_gpio_driver.h"


/*
 *	 Peripheral clock setup
 */

/*****************************************************************
 * @fn					- GPIO_PeriClockControl
 *
 * @brief				- This function enables or disables peripheral clock for the given GPIO peripheral
 *
 * @param[in]			- Base address of the GPIO peripheral
 * @param[in]			- ENABLE or DISABLE macros
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		} else if(pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		} else if(pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		} else if(pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		} else if(pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
		} else if(pGPIOx == GPIOF){
			GPIOF_PCLK_EN();
		} else if(pGPIOx == GPIOG){
			GPIOG_PCLK_EN();
		} else if(pGPIOx == GPIOH){
			GPIOH_PCLK_EN();
		}

	} else if(EnorDi == DISABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_DI();
		} else if(pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		} else if(pGPIOx == GPIOC){
			GPIOC_PCLK_DI();
		} else if(pGPIOx == GPIOD){
			GPIOD_PCLK_DI();
		} else if(pGPIOx == GPIOE){
			GPIOE_PCLK_DI();
		} else if(pGPIOx == GPIOF){
			GPIOF_PCLK_DI();
		} else if(pGPIOx == GPIOG){
			GPIOG_PCLK_DI();
		} else if(pGPIOx == GPIOH){
			GPIOH_PCLK_DI();
		}
	}
}

/*
 *	Init and De-init
 */

/*****************************************************************
 * @fn					- GPIO_Init
 *
 * @brief				- This function initialize given GPIO peripheral with user values
 *
 * @param[in]			- GPIO handle with base address and initialization values
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t reset_value = 0;

	//reset, then set mode register
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_PIN_MODE_ANALOG){
		reset_value = (0x3 << ((2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)));
		pGPIOHandle->pGPIOx->MODER &= ~(reset_value);
		reset_value = 0;

		uint32_t moder_value = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER |= moder_value;
	} else{
		//interrupt mode
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_MODE_IT_FT){
			//reset RTSR
			reset_value = (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(reset_value);
			reset_value = 0;

			//configure FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		} else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_MODE_IT_RT){
			//reset FTSR
			reset_value = (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR &= ~(reset_value);
			reset_value = 0;

			//configure RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		} else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_MODE_IT_RFT){
			//configure RTSR and FTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		//configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t index = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4);
		uint8_t position = ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4) * 4);
		uint8_t port_code = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

		SYSCFG_PCLK_EN();

		reset_value = (0xF << position);
		SYSCFG->EXTICR[index] &= ~(reset_value);
		reset_value = 0;

		SYSCFG->EXTICR[index] |= (port_code << position);

		//enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	// reset, then set speed register
	reset_value = (0x3 << ((2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)));
	pGPIOHandle->pGPIOx->OSPEEDER &= ~(reset_value);
	reset_value = 0;
	uint32_t ospeedr_value = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDER |= ospeedr_value;

	//reset, then set pupd register
	reset_value = (0x3 << ((2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)));
	pGPIOHandle->pGPIOx->PUPDR &= ~(reset_value);
	reset_value = 0;
	uint32_t pupdr_value = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= pupdr_value;

	//reset, then set output type register
	reset_value = (0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(reset_value);
	reset_value = 0;
	uint32_t optyper_value = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= optyper_value;

	//reset, then set altfn register
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_MODE_ALTFN){
		uint8_t index = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8);
		uint8_t position = ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8) * 4);

		//reset
		reset_value = (0xF << position);
		pGPIOHandle->pGPIOx->AFR[index] &= ~(reset_value);
		reset_value = 0;

		//set
		uint32_t afr_value = (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << position);
		pGPIOHandle->pGPIOx->AFR[index] |= afr_value;
	}
}

/*****************************************************************
 * @fn					- GPIO_DeInit
 *
 * @brief				- This function resets given GPIO peripheral
 *
 * @param[in]			- GPIO register definition with base address
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
	if(pGPIOx == GPIOA){
		GPIOA_REG_RESET();
	} else if(pGPIOx == GPIOB){
		GPIOB_REG_RESET();
	} else if(pGPIOx == GPIOC){
		GPIOC_REG_RESET();
	} else if(pGPIOx == GPIOD){
		GPIOD_REG_RESET();
	} else if(pGPIOx == GPIOE){
		GPIOE_REG_RESET();
	} else if(pGPIOx == GPIOF){
		GPIOF_REG_RESET();
	} else if(pGPIOx == GPIOG){
		GPIOG_REG_RESET();
	} else if(pGPIOx == GPIOH){
		GPIOH_REG_RESET();
	}
}

/*
 *	Data read and write
 */

/*****************************************************************
 * @fn					- GPIO_ReadFromInputPin
 *
 * @brief				- This function returns value from input pin
 *
 * @param[in]			- GPIO register definition with base address
 * @param[in]			- GPIO pin number
 *
 * @return				- 0 or 1
 *
 * @note				- none
 *
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	uint8_t value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}

/*****************************************************************
 * @fn					- GPIO_ReadFromInputPort
 *
 * @brief				- This function returns value from input port
 *
 * @param[in]			- GPIO register definition with base address
 *
 * @return				- 16 bit unsigned integer
 *
 * @note				- none
 *
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
	uint16_t value = (uint16_t)pGPIOx->IDR;
	return value;
}

/*****************************************************************
 * @fn					- GPIO_WriteToOutputPin
 *
 * @brief				- This function writes value to output pin
 *
 * @param[in]			- GPIO register definition with base address
 * @param[in]			- GPIO pin number
 * @param[in]			- value to write, can be 1 or 0
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){
	if(Value == GPIO_PIN_SET){
		pGPIOx->ODR |= (1 << PinNumber);
	} else if(Value == GPIO_PIN_RESET){
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

/*****************************************************************
 * @fn					- GPIO_WriteToOutputPort
 *
 * @brief				- This function writes value to output port
 *
 * @param[in]			- GPIO register definition with base address
 * @param[in]			- value to write
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value){
	pGPIOx->ODR = Value;
}

/*****************************************************************
 * @fn					- GPIO_ToggleOutputPin
 *
 * @brief				- This function toggles output pin value
 *
 * @param[in]			- GPIO register definition with base address
 * @param[in]			- GPIO pin number
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR = pGPIOx->ODR ^ (1 << PinNumber);
}


/*
 *	IRQ configuration and ISR handling
 */

/*****************************************************************
 * @fn					- GPIO_IRQInterruptConfig
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
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
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
 * @fn					- GPIO_IRQPriorityConfig
 *
 * @brief				- This function configures priority registers
 *
 * @param[in]			- IRQ priority number
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_value = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + iprx) |=  ( IRQPriority << shift_value );
}

/*****************************************************************
 * @fn					- GPIO_IRQHandling
 *
 * @brief				- This function handles interrupts
 *
 * @param[in]			- pin number
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_IRQHandling(uint8_t PinNumber){
	// clear the EXTI PR register corresponding to the pin number
	if(EXTI->PR & (1 << PinNumber)){
		EXTI->PR |= (1 << PinNumber);
	}
}
