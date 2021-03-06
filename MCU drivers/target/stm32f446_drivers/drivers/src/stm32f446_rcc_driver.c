/*
 * stm32f446_rcc_driver.c
 *
 *  Created on: Jan 23, 2021
 *      Author: robert
 */

#include "stm32f446_rcc_driver.h"


/*****************************************************************
 * @fn					- RCC_GetPCLK1Value
 *
 * @brief				- This function calculate peripheral clock speed for APB1
 *
 * @return				- peripheral clock speed for I2C peripherals
 *
 * @note				- none
 *
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

/*****************************************************************
 * @fn					- RCC_GetPCLK2Value
 *
 * @brief				- This function calculate peripheral clock speed for APB2
 *
 * @return				- peripheral clock speed for I2C peripherals
 *
 * @note				- none
 *
 */
uint32_t RCC_GetPCLK2Value(void){
	uint32_t pclk1;
	uint8_t clksrc, ahbprescaler, apb2prescaler;

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

	apb2prescaler = (RCC->CFGR >> 13) & 0x7;
	if(apb2prescaler < 4){
		//clk not divided
	} else if(apb2prescaler == 4){
		pclk1 /= 2;
	} else if(apb2prescaler == 5){
		pclk1 /= 4;
	} else if(apb2prescaler == 6){
		pclk1 /= 8;
	} else if(apb2prescaler == 7){
		pclk1 /= 16;
	}

	return pclk1;
}
