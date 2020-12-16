/*
 * 008_SPI_cmd_handling.c
 *
 *  Created on: Dec 11, 2020
 *      Author: Robert
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

#include <stdio.h>
#include <string.h>
#include "stm32f446.h"

extern void initialise_monitor_handles(void);

//command codes
#define COMMAND_LED_CTRL			0X50
#define COMMAND_SENSOR_READ			0X51
#define COMMAND_LED_READ			0X52
#define COMMAND_PRINT				0X53
#define COMMAND_ID_READ				0X54

#define LED_ON						1
#define LED_OFF						0

//Arduino analog pins
#define ANALOG_PIN0					0
#define ANALOG_PIN1					1
#define ANALOG_PIN2					2
#define ANALOG_PIN3					3
#define ANALOG_PIN4					4

//Arduino LED
#define LED_PIN						7


void delay(void){
	for(uint32_t i = 0; i < 500000; i++);
}

void SPI2_GPIO_Inits(void){
	GPIO_Handle_t SPI_Pins;
	SPI_Pins.pGPIOx = GPIOB;

	SPI_Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPI_Pins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI_Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI_Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PU;
	SPI_Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_FAST;

	//GPIOB PCLK enable
	GPIO_PeriClockControl(SPI_Pins.pGPIOx, ENABLE);

	//SCLK
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPI_Pins);

	//MISO
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPI_Pins);

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
	gpioc_button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;

	GPIO_PeriClockControl(gpioc_button.pGPIOx, ENABLE);
	GPIO_Init(&gpioc_button);
}

uint8_t SPI_Verify_Response(uint8_t ack_byte){
	if(ack_byte == 0XF5){
		//ack
		return 1;
	}

	return 0;
}

int main(void)
{
	uint8_t dummy_write = 0XFF;
	uint8_t dummy_read;
	uint8_t ack_byte;

	initialise_monitor_handles();
	printf("Application is running\n");

	//Initialize GPIO pins to behave as SPI pins
	SPI2_GPIO_Inits();

	GPIO_Button_Init();

	SPI2_Inits();
	printf("SPI Initialized\n");

	/*
	 * Enabling SSOE makes NSS automatically managed by hardware
	 * Which means that enabling SPI peripheral will make NSS 0, and disabling will make it 1
	 */
	SPI_SSOE_Config(SPI2, ENABLE);

	while(1){
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){};

		delay();
		//Enable SPI peripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		//1. CMD_LED_CNTRL		<pin no>	<value>
		uint8_t command = COMMAND_LED_CTRL;
		SPI_SendData(SPI2, &command, 1);

		//Dummy read to clear off RXEN flag
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//Send some dummy byte to fetch ack or nack response from slave
		SPI_SendData(SPI2, &dummy_write, 1);

		//Receive data from slave
		SPI_ReceiveData(SPI2, &ack_byte, 1);
		if (SPI_Verify_Response(ack_byte)){
			//Send arguments
			uint8_t args[2];
			args[0] = LED_PIN;
			args[1] = LED_ON;

			SPI_SendData(SPI2, args, 2);
		}

		//2. CMD SENSOR READ <analog pin number>
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){};
		delay();

		command = COMMAND_SENSOR_READ;
		SPI_SendData(SPI2, &command, 1);

		//Dummy read to clear off RXEN flag
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//Send some dummy byte to fetch ack or nack response from slave
		SPI_SendData(SPI2, &dummy_write, 1);

		//Receive data from slave
		SPI_ReceiveData(SPI2, &ack_byte, 1);
		if (SPI_Verify_Response(ack_byte)){
			//Send arguments
			uint8_t args;
			args = ANALOG_PIN0;

			SPI_SendData(SPI2, &args, 1);

			//Dummy read to clear off RXEN flag
			SPI_ReceiveData(SPI2, &dummy_read, 1);

			//inset delay to give slave time for response
			delay();

			SPI_SendData(SPI2, &dummy_write, 1);
			uint8_t analog_read;
			SPI_ReceiveData(SPI2, &analog_read, 1);
			printf("Sensor Value: %d\n", analog_read);
		}


		//3. CMD LED READ <analog pin number>
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){};
		delay();

		command = COMMAND_LED_READ;
		SPI_SendData(SPI2, &command, 1);

		//Dummy read to clear off RXEN flag
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//Send some dummy byte to fetch ack or nack response from slave
		SPI_SendData(SPI2, &dummy_write, 1);

		//Receive data from slave
		SPI_ReceiveData(SPI2, &ack_byte, 1);
		if(SPI_Verify_Response(ack_byte)){
			//send arguments
			uint8_t args;
			args = LED_PIN;

			SPI_SendData(SPI2, &args, 1);

			//Dummy read to clear off RXEN flag
			SPI_ReceiveData(SPI2, &dummy_read, 1);

			//inset delay to give slave time for response
			delay();

			uint8_t led_status;
			SPI_SendData(SPI2, &dummy_write, 1);
			SPI_ReceiveData(SPI2, &led_status, 1);
			printf("LED Value: %d\n", led_status);
		}

		//4. CMD PRINT <message as string>
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){};
		delay();

		command = COMMAND_PRINT;
		SPI_SendData(SPI2, &command, 1);

		//Dummy read to clear off RXEN flag
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//Send some dummy byte to fetch ack or nack response from slave
		SPI_SendData(SPI2, &dummy_write, 1);

		//Receive data from slave
		SPI_ReceiveData(SPI2, &ack_byte, 1);
		if (SPI_Verify_Response(ack_byte)){
			//Send arguments
			uint8_t message[] = "Hello from the otter side";
			uint8_t args;
			args = strlen((char*)message);

			//send length
			SPI_SendData(SPI2, &args, 1);

			//send message
			SPI_SendData(SPI2, message, args);

			//Dummy read to clear off RXEN flag
			SPI_ReceiveData(SPI2, &dummy_read, 1);

			printf("Message sent!\n");
		}

		//5. CMD ID READ
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){};
		delay();

		command = COMMAND_ID_READ;
		SPI_SendData(SPI2, &command, 1);

		//Dummy read to clear off RXEN flag
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//Send some dummy byte to fetch ack or nack response from slave
		SPI_SendData(SPI2, &dummy_write, 1);

		//Receive data from slave
		SPI_ReceiveData(SPI2, &ack_byte, 1);
		if (SPI_Verify_Response(ack_byte)){
			uint8_t id[11];

			//read 10 bytes id from the slave
			for( int i = 0 ; i < 10 ; i++)
			{
				//send dummy byte to fetch data from slave
				SPI_SendData(SPI2,&dummy_write,1);
				SPI_ReceiveData(SPI2,&id[i],1);
			}

			id[11] = '\0';

			printf("COMMAND_ID : %s \n",id);
		}

		//6. CMD_LED_CNTRL		<pin no>	<value>
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){};
		delay();

		command = COMMAND_LED_CTRL;
		SPI_SendData(SPI2, &command, 1);

		//Dummy read to clear off RXEN flag
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//Send some dummy byte to fetch ack or nack response from slave
		SPI_SendData(SPI2, &dummy_write, 1);

		//Receive data from slave
		SPI_ReceiveData(SPI2, &ack_byte, 1);
		if (SPI_Verify_Response(ack_byte)){
			//Send arguments
			uint8_t args[2];
			args[0] = LED_PIN;
			args[1] = LED_OFF;

			SPI_SendData(SPI2, args, 2);
		}


		//check till SPI is finished with transmission
		while(SPI_GetFlagStatus(SPI2, SPI_BSY_FLAG)){};

		SPI_PeripheralControl(SPI2, DISABLE);

	}
}
