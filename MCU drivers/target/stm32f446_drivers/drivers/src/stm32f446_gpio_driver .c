/*
 * stm32f446_gpio_driver .c
 *
 *  Created on: Nov 10, 2020
 *      Author: robert
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
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		reset_value = (0x3 << ((2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)));
		pGPIOHandle->pGPIOx->MODER &= ~(reset_value);
		reset_value = 0;

		uint32_t moder_value = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER |= moder_value;
	} else{
		//interrupt mode
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
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode == GPIO_MODE_ALTFN){
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
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 *	IRQ configuration and ISR handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);
