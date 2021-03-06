/*
 * 006_spi_tx_test.c
 *
 *  Created on: Dec 3, 2020
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

void SPI2_GPIO_Inits(void){
	GPIO_Handle_t SPI_Pins;
	SPI_Pins.pGPIOx = GPIOB;

	SPI_Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_ALTFN;
	SPI_Pins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI_Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;
	SPI_Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;
	SPI_Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_OP_SPEED_FAST;

	//GPIOB PCLK enable
	GPIO_PeriClockControl(SPI_Pins.pGPIOx, ENABLE);

	//NSS
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPI_Pins);

	//SCLK
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPI_Pins);

	//MISO
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPI_Pins);

	//MOSI
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPI_Pins);
}

void SPI2_Inits(void){
	SPI_Handle_t SPI2_Handle;

	SPI2_Handle.pSPIx = SPI2;

	SPI2_Handle.SPI_Config.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2_Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2_Handle.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;			//Generate SCLK of 8MHz
	SPI2_Handle.SPI_Config.SPI_DFF = SPI_DFF_8BITS;
	SPI2_Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2_Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2_Handle.SPI_Config.SPI_SSM = SPI_SSM_EN;						//Software slave management enabled

	SPI_PeriClockControl(SPI2_Handle.pSPIx, ENABLE);

	SPI_Init(&SPI2_Handle);
}

int main(void)
{
	char userData[] = "Hello Pepsy";

	//Initialize GPIO pins to behave as SPI pins
	SPI2_GPIO_Inits();

	SPI2_Inits();

	//Enable SSI bit and avoid MODF error
	SPI_SSI_Config(SPI2, ENABLE);

	//Enable SPI peripheral
	SPI_PeripheralControl(SPI2, ENABLE);

	SPI_SendData(SPI2, (uint8_t*)userData, strlen(userData));

	//check till SPI is finished with transmission
	while(SPI_GetFlagStatus(SPI2, SPI_FLAG_BSY)){};

	SPI_PeripheralControl(SPI2, DISABLE);

	for(;;);
}
