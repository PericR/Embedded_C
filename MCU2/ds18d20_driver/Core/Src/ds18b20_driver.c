/*
 * ds18b20_driver.c
 *
 *  Created on: Feb 6, 2021
 *      Author: robert
 */

#include "ds18b20_driver.h"



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
uint8_t ds18b20_init_phase(void)
{
	uint8_t response = 0;

	set_pin_as_out(DS18B20_PORT, DS18B20_PIN);

	write_pin(DS18B20_PORT, DS18B20_PIN, 0);	//pull data line to LOW for 480-950 microseconds (RESET signal)
	delay_us(550);

	set_pin_as_in(DS18B20_PORT, DS18B20_PIN);
	delay_us(80);

	if(!read_pin(DS18B20_PORT, DS18B20_PIN))	//scan for PRESENCE signal (LOW data line)
	{
		response = 1;
	}

	delay_us(200);
	return response;
}

/*********************************************************************
 * @fn      		  - set_pin_as_out
 *
 * @brief             - This function sets gpio moder to output
 *
 * @param[in]         - GPIO_TypeDef *gpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void set_pin_as_out(GPIO_TypeDef *gpio_port, uint8_t gpio_pin)
{
	//reset then set mode as output
	gpio_port->MODER &= ~(0x3 << (2 * gpio_pin));
	gpio_port->MODER |= (1 << (2 * gpio_pin));
}

/*********************************************************************
 * @fn      		  - set_pin_as_in
 *
 * @brief             - This function sets gpio moder to input
 *
 * @param[in]         - GPIO_TypeDef *gpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void set_pin_as_in(GPIO_TypeDef *gpio_port, uint8_t gpio_pin)
{
	//set pin as in
	gpio_port->MODER &= ~(0x3 << (2 * gpio_pin));
}

/*********************************************************************
 * @fn      		  - write_pin
 *
 * @brief             - This function sets gpio ODR to HIGH or LOW
 *
 * @param[in]         - GPIO_TypeDef *gpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 * 						uint8_t value 1 or 0 signal to be set
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void write_pin(GPIO_TypeDef *gpio_port, uint8_t gpio_pin, uint8_t value)
{
	if(value == 1)
	{
		gpio_port->ODR |= (1 << gpio_pin);
	}
	else
	{
		gpio_port->ODR &= ~(1 << gpio_pin);
	}
}

/*********************************************************************
 * @fn      		  - read_pin
 *
 * @brief             - This function read gpio IDR
 *
 * @param[in]         - GPIO_TypeDef *gpio_port - pointer to GPIO port
 * 						uint8_t gpio_pin number of GPIO pin
 *
 * @return            -  returns value from IDR, 1 or 0
 *
 * @Note              -  none

 */
uint8_t read_pin(GPIO_TypeDef *gpio_port, uint8_t gpio_pin)
{
	uint8_t value = (uint8_t)((gpio_port->IDR >> gpio_pin) & 0x00000001);
	return value;
}





