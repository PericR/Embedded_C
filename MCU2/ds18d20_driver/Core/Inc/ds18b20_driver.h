/*
 * ds18b20_driver.h
 *
 *  Created on: Feb 6, 2021
 *      Author: robert
 */

#include "stm32f4xx_hal.h"
#include "delay.h"

#ifndef INC_DS18B20_DRIVER_H_
#define INC_DS18B20_DRIVER_H_

/*
 * DS18B20 macros
 * Im using PIN C3, but it can be changed here
 */
#define DS18B20_PIN			3
#define DS18B20_PORT		GPIOC
#define HIGH				1
#define LOW					0

typedef struct{
	uint8_t GPIO_pin;
	GPIO_TypeDef *pGPIOx;
}DS18B20_Handle_t;

/******************************************************DS18B20 API************************************************/
/*
 * DS18B20 has protocol of 4 sequences so this file will reflect that organization
 */


/*
 * Initialization Phase
 */
uint8_t Ds18b20_init_phase(DS18B20_Handle_t *hds18b20);

/*
 * ROM Functions
 */

/*
 * Memory Functions
 */

/*
 * Transanction/Data functions
 */
void Ds18b20_write_byte(uint8_t write_data);
uint8_t Ds18b20_read_byte(void);

/*
 *helper functions for GPIO I/O
 */

void sd18b20_gpio_init(DS18B20_Handle_t *pDs18b20);
void Set_pin_as_out(GPIO_TypeDef *pGpio_port, uint8_t gpio_pin);
void Set_pin_as_in(GPIO_TypeDef *pGpio_port, uint8_t gpio_pin);
void Write_pin(GPIO_TypeDef *pGpio_port, uint8_t gpio_pin, uint8_t value);
uint8_t Read_pin(GPIO_TypeDef *pGpio_port, uint8_t gpio_pin);



#endif /* INC_DS18B20_DRIVER_H_ */
