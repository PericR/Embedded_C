/*
 * stm32f446_i2c_driver.c
 *
 *  Created on: Dec 26, 2020
 *      Author: robert
 */


#include "stm32f446_i2c_driver.h"

/*
 * Private helper functions
 */
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

/*****************************************************************
 * @fn					- I2C_GenerateStartCondition
 *
 * @brief				- This function sends address to find desired slave
 *
 * @param[in]			- Base address of the I2C peripheral
 *
 * @return				- none
 *
 * @note				- none
 *
 */
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

/*****************************************************************
 * @fn					- I2C_ExecuteAddressPhaseWrite
 *
 * @brief				- This function sends address to find desired slave
 *
 * @param[in]			- Base address of the I2C peripheral
 * @param[in]			- 7 bit slave address
 *
 * @return				- none
 *
 * @note				- none
 *
 */
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr){
	//Make sure there is space for r/w bit
	SlaveAddr = SlaveAddr << 1;
	//Clear 0th bit so r/w is set to write
	SlaveAddr &= ~(1 << 0);
	//Place address into Data Register
	pI2Cx->DR = SlaveAddr;
}

/*****************************************************************
 * @fn					- I2C_ExecuteAddressPhaseRead
 *
 * @brief				- This function sends address to find desired slave
 *
 * @param[in]			- Base address of the I2C peripheral
 * @param[in]			- 7 bit slave address
 *
 * @return				- none
 *
 * @note				- none
 *
 */
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr){
	//Make sure there is space for r/w bit
	SlaveAddr = SlaveAddr << 1;
	//Clear 0th bit so r/w is set to read
	SlaveAddr |= (1 << 0);
	//Place address into Data Register
	pI2Cx->DR = SlaveAddr;
}

/*****************************************************************
 * @fn					- I2C_ClearADDRFlag
 *
 * @brief				- This function clears ADDR flag from Status Register 1
 *
 * @param[in]			- Base address of the I2C peripheral
 *
 * @return				- none
 *
 * @note				- none
 *
 */
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx){
	uint32_t dummy_read = pI2Cx->SR1;
	dummy_read = pI2Cx->SR2;
	(void)dummy_read;
}

/*****************************************************************
 * @fn					- I2C_GenerateStopCondition
 *
 * @brief				- This function sends STOP condition to slave indicating end of transmission
 *
 * @param[in]			- Base address of the I2C peripheral
 *
 * @return				- none
 *
 * @note				- none
 *
 */
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

/*****************************************************************
 * @fn					- RCC_GetPCLK1Value
 *
 * @brief				- This function calculate peripheral clock speed for all 3 I2C peripherals
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
	uint32_t i2c_cr2 = 0;
	uint32_t i2c_oar1 = 0;
	uint32_t i2c_ccr = 0;
	uint32_t i2c_trise = 0;

	//enable the clock for the i2cx peripheral
	I2C_PeriClockControl(pI2CHandle->pI2Cx,ENABLE);
	I2C_PeripheralControl(pI2CHandle->pI2Cx, ENABLE);
	//ack bit configuration
	pI2CHandle->pI2Cx->CR1 |= (pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK);


	//configure the FREQ bits of CR2
	i2c_cr2 |= ((RCC_GetPCLK1Value() /1000000U ) << I2C_CR2_FREQ);
	pI2CHandle->pI2Cx->CR2 = (i2c_cr2 & 0x3F);

	//configure own address for slave mode when using 7 bit address
	i2c_oar1 |= (pI2CHandle->I2C_Config.I2C_DeviceAddress << I2C_OAR1_ADD7_1);
	i2c_oar1 |= (1 << 14);
	pI2CHandle->pI2Cx->OAR1 = i2c_oar1;

	//configure CCR register
	uint16_t ccr_value = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM){
		//mode is standard mode so we don't have to touch 15th and 14th bits
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		i2c_ccr |= (ccr_value << I2C_CCR_CCR);

		pI2CHandle->pI2Cx->CCR = i2c_ccr;
	}else {
		//Fast mode
		i2c_ccr |= (1 << I2C_CCR_FS);
		i2c_ccr |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << I2C_CCR_DUTY);

		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2){
			ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}else {
			ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}
		i2c_ccr |= (ccr_value << I2C_CCR_CCR);

		pI2CHandle->pI2Cx->CCR = i2c_ccr;
	}

	//Configure TRISE register
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM){
		//Standard mode
		i2c_trise = (RCC_GetPCLK1Value() / 1000000U) + 1;
		pI2CHandle->pI2Cx->TRISE = i2c_trise & 0x3F;
	}else{
		//Fast mode
		i2c_trise = ((RCC_GetPCLK1Value() * 300) / 1000000000U) + 1;
		pI2CHandle->pI2Cx->TRISE = i2c_trise & 0x3F;
	}

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
 * 	Data Send and Receive
 */

/*****************************************************************
 * @fn					- I2C_MasterSendData
 *
 * @brief				- This function initiates transmission and sends data from master to slave
 *
 * @param[in]			- SPI handle with base address and initialization values
 * @param[in]			- Pointer to transmission buffer which holds data to be sent
 * @param[in]			- Length of data
 * @param[in]			- 7 bit slave address
 * @param[in]			- Repeated start (I2C_NO_SR or I2C_SR)
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr){
	//Initiate start condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//Confirm that start generation is completed by checking the SB flag in SR1
	//Until SB is cleared. CLK will be stretched (pulled to LOW)
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

	//Send the address of the slave with r/w bit set to write (0)
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, SlaveAddr);

	//Confirm that address phase is completed by checking the ADDR flag in the SR1
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));
	//clear ADDR Flag
	I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

	//Send data until Len == 0
	while(Len > 0){
		//Wait till TXE is SET
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));
		pI2CHandle->pI2Cx->DR = *pTxbuffer;
		pTxbuffer++;
		Len--;
	}

	//After sending data wait until TXE is SET and BTF is SET
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF));

	//After that generate STOP condition
	if(Sr == I2C_DISABLE_SR){
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
	}
}

/*****************************************************************
 * @fn					- I2C_MasterReceiveData
 *
 * @brief				- This function initiates transmission and sends data from master to slave
 *
 * @param[in]			- SPI handle with base address and initialization values
 * @param[in]			- Pointer to buffer which will receive data
 * @param[in]			- Length of data
 * @param[in]			- 7 bit slave address
 * @param[in]			- Repeated start (I2C_NO_SR or I2C_SR)
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr){
	//Generate the start condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//Confirm that start generation is completed by checking the SB flag in the SR1
	//Note: until SB is cleared SCLK will be streched (pulled to LOW)
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

	//Send the address of the slave with r/nw bit set to R(1) (total 8 bits)
	I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx, SlaveAddr);

	//Wait until address phase is completed by checking ADDR flag in the SR1
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));

	//procedure to read only 1 byte from slave
	if(Len == 1){
		//Disable Acking
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);

		//Clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

		//Wait until RXNE is SET
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE));

		//generate STOP condition
		if(Sr == I2C_DISABLE_SR){
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
		}

		//read data in to buffer
		*pRxbuffer = pI2CHandle->pI2Cx->DR;

	}

	//procedure to read data from slave when LEN > 1
	if(Len > 1){
		//Clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

		//read the data until LEN == 0
		for(uint32_t i = Len; i > 0; i--){
			//wait until RXNE becomes 1
			while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE));

			//if last 2 bytes are remaining
			if(i == 2){
				//clear the ACK bit
				I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);

				//generate STOP condition
				if(Sr == I2C_DISABLE_SR){
					I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
				}
			}

			//read the data from data register in to buffer
			*pRxbuffer = pI2CHandle->pI2Cx->DR;

			//increment the buffer address
			pRxbuffer++;
		}
	}
	//re-enable ACKing
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE){
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_ENABLE);
	}
}

/*****************************************************************
 * @fn					- I2C_MasterSendData_IT
 *
 * @brief				- This function initiates transmission and sends data from master to slave
 *
 * @param[in]			- SPI handle with base address and initialization values
 * @param[in]			- Pointer to transmission buffer which holds data to be sent
 * @param[in]			- Length of data
 * @param[in]			- 7 bit slave address
 * @param[in]			- Repeated start (I2C_NO_SR or I2C_SR)

 * @return				- Application state
 *
 * @note				- none
 *
 */
uint8_t I2C_MasterSendData_IT(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr){
	uint8_t busy_state = pI2CHandle->TxRxState;

	if( (busy_state != I2C_BUSY_IN_TX) && (busy_state != I2C_BUSY_IN_RX) ){
		pI2CHandle->pTxBuffer = pTxbuffer;
		pI2CHandle->TxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_TX;
		pI2CHandle->DevAddress = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Generate START condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//Enable ITBUFEN control bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITBUFEN);

		//Enable ITEVFEN control bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);

		//Enable ITERREN control bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);
	}

	return busy_state;
}

/*****************************************************************
 * @fn					- I2C_MasterReceiveData_IT
 *
 * @brief				- This function initiates transmission and sends data from master to slave
 *
 * @param[in]			- SPI handle with base address and initialization values
 * @param[in]			- Pointer to buffer which will receive data
 * @param[in]			- Length of data
 * @param[in]			- 7 bit slave address
 * @param[in]			- Repeated start (I2C_NO_SR or I2C_SR)
 *
 * @return				- Application state
 *
 * @note				- none
 *
 */
uint8_t I2C_MasterReceiveData_IT(I2C_Handle_t *pI2CHandle, uint8_t *pRxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr){
	uint8_t busy_state = pI2CHandle->TxRxState;

	if((busy_state != I2C_BUSY_IN_TX) && (busy_state != I2C_BUSY_IN_RX)){
		pI2CHandle->pRxBuffer = pRxbuffer;
		pI2CHandle->RxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_RX;
		pI2CHandle->RxSize = Len;					//RxSize is used in ISR code to manage data reception
		pI2CHandle->DevAddress = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Generate START condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//Enable ITBUFEN control bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITBUFEN);

		//Enable ITEVFEN control bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);

		//Enable ITERREN control bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);
	}

	return busy_state;
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

/*****************************************************************
 * @fn					- I2C_GetFlagStatus
 *
 * @brief				- This function gets FLAG status
 *
 * @param[in]			- Base address of the I2C peripheral
 * @param[in]			- Flag name
 *
 * @return				- Flag status (1 or 0)
 *
 * @note				- none
 *
 */
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName){
	if(pI2Cx->SR1 & FlagName){
		return FLAG_SET;
	}

	return FLAG_RESET;
}

/*****************************************************************
 * @fn					- I2C_ManageAcking
 *
 * @brief				- This function manages ACK bit in CR1 register
 *
 * @param[in]			- Base address of the I2C peripheral
 * @param[in]			- ENABLE or DISABLE macros
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void I2C_ManageAcking(I2C_RegDef_t *pI2CX, uint8_t EnOrDi){
	if(EnOrDi == I2C_ACK_ENABLE){
		pI2CX->CR1 |= (1 << I2C_CR1_ACK);
	}else{
		pI2CX->CR1 &= ~(1 << I2C_CR1_ACK);
	}
}
