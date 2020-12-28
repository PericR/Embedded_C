/*
 * stm32f446_i2c_driver.c
 *
 *  Created on: Dec 26, 2020
 *      Author: robert
 */


#include "stm32f446_i2c_driver.h"

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





