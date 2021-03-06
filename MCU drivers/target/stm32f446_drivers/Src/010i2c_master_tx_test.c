/*
 * 010i2c_master_tx_test.c
 *
 *  Created on: Dec 30, 2020
 *      Author: robert
 */

/*
 * PB6	I2C1_SCL
 * PB7	I2C1_SDA
 *
 * ALTERNATE FUNCTIONALITY => AF4
 */

#include <stdio.h>
#include <string.h>
#include "stm32f446.h"

extern void initialise_monitor_handles(void);

#define MY_ADDR			0x61
#define SLAVE_ADDR		0x68

I2C_Handle_t I2C1_handle;

void delay(void){
	for(uint32_t i = 0; i < 500000; i++);
}

void GPIO_Button_Init(){
	GPIO_Handle_t gpioc_button;
	gpioc_button.pGPIOx = GPIOC;

	gpioc_button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	gpioc_button.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_IN;

	GPIO_PeriClockControl(gpioc_button.pGPIOx, ENABLE);
	GPIO_Init(&gpioc_button);
}

void I2C1_GPIOInits(void){
	GPIO_Handle_t I2C_pins;
	I2C_pins.pGPIOx = GPIOB;

	I2C_pins.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_ALTFN;
	I2C_pins.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_PIN_ALT_FUN_4;
	I2C_pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_OD;
	I2C_pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	I2C_pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_OP_SPEED_FAST;

	//Start GPIO peripheral clock
	GPIO_PeriClockControl(I2C_pins.pGPIOx, ENABLE);

	//Configure I2C1_SCL
	I2C_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2C_pins);

	//Configure I2C1_SDA
	I2C_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&I2C_pins);
}

void I2C1_Inits(void){
	I2C1_handle.pI2Cx = I2C1;

	I2C1_handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	I2C1_handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1_handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1_handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1_handle);
}

int main(void){
	GPIO_Button_Init();
	I2C1_GPIOInits();
	I2C1_Inits();

	uint8_t some_data[] = "We are test";

	I2C_PeripheralControl(I2C1_handle.pI2Cx, ENABLE);

	while(1){
		//Button press and de-bouncing delay
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){};
		delay();

		//send data
		I2C_MasterSendData(&I2C1_handle, some_data, strlen((char*) some_data), SLAVE_ADDR, I2C_DISABLE_SR);
	}
}


