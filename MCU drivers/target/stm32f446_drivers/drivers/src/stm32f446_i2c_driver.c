/*
 * stm32f446_i2c_driver.c
 *
 *  Created on: Dec 26, 2020
 *      Author: robert
 */


#include "stm32f446_i2c_driver.h"

/*
 * Helper functions
 */

uint32_t RCC_GetPCLK1Value(void){
	uint32_t pclk1;
	uint8_t clksrc, ahbprescaler, apb1prescaler;

	clksrc = (RCC->CFGR >> 2) & 0x3;
	if(clksrc == 0){
		pclk1 = 16000000;
	} else{
		pclk1 = 0; //I wont use other clocks for now (i don't have external clock)
	}

	ahbprescaler = (RCC->CFGR >> 4) & 0xF;
	if(ahbprescaler < 8){
		//clock wont be divided
	}else if(ahbprescaler == 8){
		pclk1 /= 2;
	}else if(ahbprescaler == 9){
		pclk1 /= 4;
	}else if(ahbprescaler == 10){
		pclk1 /= 8;
	}else if(ahbprescaler == 11){
		pclk1 /= 16;
	}else if(ahbprescaler == 12){
		pclk1 /= 64;
	}else if(ahbprescaler == 13){
		pclk1 /= 128;
	}else if(ahbprescaler == 14){
		pclk1 /= 256;
	}else if(ahbprescaler == 15){
		pclk1 /= 512;
	}

	apb1prescaler = (RCC->CFGR >> 10) & 0x7;
	if(apb1prescaler < 4){
		//clk not divided
	} else if(apb1prescaler == 4){
		pclk1 /= 2;
	} else if(apb1prescaler == 5){
		pclk1 /= 4;
	} else if(apb1prescaler == 6){
		pclk1 /= 8;
	} else if(apb1prescaler == 7){
		pclk1 /= 16;
	}

	return pclk1;
}
/*
 *	 Peripheral clock setup
 */

/*****************************************************************
 * @fn					- I2C_PeriClockControl
 *
 * @brief				- This function enables or disables peripheral clock for the given I2C peripheral
 *
 * @param[in]			- Base address of the I2C peripheral
 * @param[in]			- ENABLE or DISABLE macros
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pI2Cx == I2C1){
			I2C1_PCLK_EN();
		} else if (pI2Cx == I2C2){
			I2C2_PCLK_EN();
		} else if (pI2Cx == I2C3){
			I2C3_PCLK_EN();
		}
	} else{
		if(pI2Cx == I2C1){
			I2C1_PCLK_DI();
		} else if (pI2Cx == I2C2){
			I2C2_PCLK_DI();
		} else if (pI2Cx == I2C3){
			I2C3_PCLK_DI();
		}
	}
}
/*
 * init and de-init
 */

/*****************************************************************
 * @fn					- I2C_Init
 *
 * @brief				- This function initialize given I2C peripheral with user values
 *
 * @param[in]			- SPI handle with base address and initialization values
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void I2C_Init(I2C_Handle_t *pI2CHandle){
	uint32_t i2c_cr1 = 0;
	i2c_cr1 |= (pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK);
}

/*****************************************************************
 * @fn					- I2C_DeInit
 *
 * @brief				- This function resets given I2C peripheral
 *
 * @param[in]			- Base address of the I2C peripheral
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void I2C_DeInit(I2C_RegDef_t *pI2Cx){
	if(pI2Cx == I2C1){
		I2C1_REG_RESET();
	} else if(pI2Cx == I2C2){
		I2C2_REG_RESET();
	} else if(pI2Cx == I2C3){
		I2C3_REG_RESET();
	}
}

/*
 * 	IRQ Configuration and ISR handling
 */

/*****************************************************************
 * @fn					- I2C_IRQInterruptConfig
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
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
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
 * @fn					- I2C_IRQPriorityConfig
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
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_value = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_value);
}

/*
 * 	Other Peripheral Control APIs
 */

/*****************************************************************
 * @fn					- I2C_PeripheralControl
 *
 * @brief				- This function configures I2C Peripheral
 *
 * @param[in]			- Base address of the I2C peripheral
 * @param[in]			- Enable or disable
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	} else{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}
}



