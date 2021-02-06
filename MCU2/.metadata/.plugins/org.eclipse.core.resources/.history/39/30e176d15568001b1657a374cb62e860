/*
 * ds18b20_driver.c
 *
 *  Created on: Feb 6, 2021
 *      Author: robert
 */

#include "ds18b20_driver.h"



/*
 * Initialization Phase
 */

/*********************************************************************
 * @fn      		  - ds18b20_init_phase
 *
 * @brief             - This function serves as Initialization phase
 * 						It scans for device on data line
 *
 * @param[in]         - none
 *
 * @return            -  1 if device is found, 0 if not
 *
 * @Note              -  none

 */
uint8_t Ds18b20_init_phase(DS18B20_Handle_t *hds18b20)
{
	uint8_t response = 0;

	Set_pin_as_out(hds18b20->pGPIOx, hds18b20->GPIO_pin);

	Write_pin(hds18b20->pGPIOx, hds18b20->GPIO_pin, LOW);	//pull data line to LOW for 480-950 microseconds (RESET signal)
	Delay_us(550);

	Set_pin_as_in(hds18b20->pGPIOx, hds18b20->GPIO_pin);
	Delay_us(80);

	if(!Read_pin(hds18b20->pGPIOx, hds18b20->GPIO_pin))	//scan for PRESENCE signal (LOW data line)
	{
		response = 1;
	}

	Delay_us(200);
	return response;
}


/*
 * Transanction/Data functions
 */

/*********************************************************************
 * @fn      		  - Ds18b20_write_byte
 *
 * @brief             - This function read gpio IDR
 *
 * @param[in]         - GPIO_TypeDef *pGpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  returns value from IDR, 1 or 0
 *
 * @Note              -  none

 */
void Ds18b20_write_byte(uint8_t write_data)
{
	for(int i = 0; i < 8; i++)
	{
		if((write_data & (1 << i)) == 0)
		{
			//bit is LOW so we keep LOW for 60 us
			Set_pin_as_out(DS18B20_PORT, DS18B20_PIN);
			Write_pin(DS18B20_PORT, DS18B20_PIN, LOW);
			Delay_us(60);
			Set_pin_as_in(DS18B20_PORT, DS18B20_PIN);
		}
		else
		{
			Set_pin_as_out(DS18B20_PORT, DS18B20_PIN);
			Write_pin(DS18B20_PORT, DS18B20_PIN, LOW);
		}
	}
}


uint8_t Ds18b20_read_byte(void);


/*
 *helper functions for GPIO I/O
 */

/*********************************************************************
 * @fn      		  - sd18b20_gpio_init
 *
 * @brief             - This function sets gpio pin used for OneWire communication with ds18b20
 *
 * @param[in]         - none
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void sd18b20_gpio_init(DS18B20_Handle_t *pDs18b20)
{
	GPIO_InitTypeDef ds_gpio;

	ds_gpio.Pin = pDs18b20->GPIO_pin;
	ds_gpio.Mode = GPIO_MODE_OUTPUT_OD;
	ds_gpio.Pull = GPIO_NOPULL;
	ds_gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(DS18B20_PORT, &ds_gpio);
}

/*********************************************************************
 * @fn      		  - set_pin_as_out
 *
 * @brief             - This function sets gpio moder to output
 *
 * @param[in]         - GPIO_TypeDef *pGpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void Set_pin_as_out(GPIO_TypeDef *pGpio_port, uint8_t gpio_pin)
{
	//reset then set mode as output
	pGpio_port->MODER &= ~(0x3 << (2 * gpio_pin));
	pGpio_port->MODER |= (1 << (2 * gpio_pin));
}

/*********************************************************************
 * @fn      		  - set_pin_as_in
 *
 * @brief             - This function sets gpio moder to input
 *
 * @param[in]         - GPIO_TypeDef *pGpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void Set_pin_as_in(GPIO_TypeDef *pGpio_port, uint8_t gpio_pin)
{
	//set pin as in
	pGpio_port->MODER &= ~(0x3 << (2 * gpio_pin));
}

/*********************************************************************
 * @fn      		  - write_pin
 *
 * @brief             - This function sets gpio ODR to HIGH or LOW
 *
 * @param[in]         - GPIO_TypeDef *pGpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 * 						uint8_t value HIGH or LOW signal to be set
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void Write_pin(GPIO_TypeDef *pGpio_port, uint8_t gpio_pin, uint8_t value)
{
	if(value == 1)
	{
		pGpio_port->ODR |= (1 << gpio_pin);
	}
	else
	{
		pGpio_port->ODR &= ~(1 << gpio_pin);
	}
}

/*********************************************************************
 * @fn      		  - read_pin
 *
 * @brief             - This function read gpio IDR
 *
 * @param[in]         - GPIO_TypeDef *pGpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  returns value from IDR, HIGH or LOW
 *
 * @Note              -  none

 */
uint8_t Read_pin(GPIO_TypeDef *pGpio_port, uint8_t gpio_pin)
{
	uint8_t value = (uint8_t)((pGpio_port->IDR >> gpio_pin) & 0x00000001);
	return value;
}


