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





