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
 */
#define DS18B20_PIN			3
#define DS18B20_PORT		GPIOC



uint8_t ds18b20_init_phase(void);


/*
 *helper functions for GPIO I/O
 */
void set_pin_as_out(GPIO_TypeDef *gpio_port, uint8_t gpio_pin);
void set_pin_as_in(GPIO_TypeDef *gpio_port, uint8_t gpio_pin);
void write_pin(GPIO_TypeDef *gpio_port, uint8_t gpio_pin, uint8_t value);
uint8_t read_pin(GPIO_TypeDef *gpio_port, uint8_t gpio_pin);



#endif /* INC_DS18B20_DRIVER_H_ */
