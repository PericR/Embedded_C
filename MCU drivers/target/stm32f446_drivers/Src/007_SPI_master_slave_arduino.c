/*
 * 007_SPI_master_slave_arduino.c
 *
 *  Created on: Dec 5, 2020
 *      Author: robert
 */


/*
 *
 * 	PB 12 as SPI2 NSS
 * 	PB 13 as SPI2 SCLK
 * 	PB 14 as SPI2 MISO
 * 	PB 15 as SPI2 MOSI
 *
 *	ALT Function mode = 5
 */

#include "string.h"
#include "stm32f446.h"

void delay(void){
	for(uint32_t i = 0; i < 500000; i++);
}

void SPI2_GPIO_Inits(void){
	GPIO_Handle_t SPI_Pins;
	SPI_Pins.pGPIOx = GPIOB;

	SPI_Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_ALTFN;
	SPI_Pins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI_Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;
	SPI_Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	SPI_Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_OP_SPEED_FAST;

	//GPIOB PCLK enable
	GPIO_PeriClockControl(SPI_Pins.pGPIOx, ENABLE);

	//SCLK
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPI_Pins);

	//MISO
	//SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPI_Pins);

	//MOSI
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPI_Pins);

	//NSS
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPI_Pins);
}

void SPI2_Inits(void){
	SPI_Handle_t SPI2_Handle;
	SPI2_Handle.pSPIx = SPI2;

	SPI2_Handle.SPI_Config.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2_Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2_Handle.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;			//Generate SCLK of 2MHz
	SPI2_Handle.SPI_Config.SPI_DFF = SPI_DFF_8BITS;
	SPI2_Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2_Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2_Handle.SPI_Config.SPI_SSM = SPI_SSM_DI;						//Hardware slave management enabled

	SPI_PeriClockControl(SPI2_Handle.pSPIx, ENABLE);

	SPI_Init(&SPI2_Handle);
}

void GPIO_Button_Init(){
	GPIO_Handle_t gpioc_button;
	gpioc_button.pGPIOx = GPIOC;

	gpioc_button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	gpioc_button.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_IN;

	GPIO_PeriClockControl(gpioc_button.pGPIOx, ENABLE);
	GPIO_Init(&gpioc_button);
}

int main(void)
{
	char userData[] = "Hello Debeli Kume :P";

	//Initialize GPIO pins to behave as SPI pins
	SPI2_GPIO_Inits();

	GPIO_Button_Init();

	SPI2_Inits();

	/*
	 * Enabling SSOE makes NSS automatically managed by hardware
	 * Which means that enabling SPI peripheral will make NSS 0, and disabling will make it 1
	 */
	SPI_SSOE_Config(SPI2, ENABLE);

	while(1){
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){};
			//Enable SPI peripheral
			SPI_PeripheralControl(SPI2, ENABLE);

			//first send length of data
			uint8_t data_length = strlen(userData);
			SPI_SendData(SPI2, &data_length, 1);

			SPI_SendData(SPI2, (uint8_t*)userData, strlen(userData));

			//check till SPI is finished with transmission
			while(SPI_GetFlagStatus(SPI2, SPI_FLAG_BSY)){};

			SPI_PeripheralControl(SPI2, DISABLE);
			delay();
	}
}
