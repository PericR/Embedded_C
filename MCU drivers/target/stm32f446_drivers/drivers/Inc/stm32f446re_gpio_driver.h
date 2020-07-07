/*
 * stm32f446re_gpio_driver.h
 *
 *  Created on: Jul 6, 2020
 *      Author: robert
 */

#ifndef INC_STM32F446RE_GPIO_DRIVER_H_
#define INC_STM32F446RE_GPIO_DRIVER_H_

#include <stdint.h>
#include "stm32f446re.h"


typedef struct{
	uint8_t GPIO_pin_num;
	uint8_t GPIO_pin_mode;					//possible values from @GPIO_PIN_MODES
	uint8_t GPIO_pin_speed;
	uint8_t GPIO_pin_pu_pd;
	uint8_t GPIO_pin_op_type;
	uint8_t GPIO_pin_alt_fun_mode;
}GPIO_pin_config_t;

//handle structure for GPIO pin
typedef struct{
	GPIO_reg_def_t *pGPIOx;					//holds the base address of the GPIO port to which the pin belongs
	GPIO_pin_config_t GPIO_pin_config;		//holds GPIO pin config settings
}GPIO_handle_t;


//@GPIO_PIN_MODES
//GPIO pin possible modes
#define GPIO_MODE_IN				0
#define GPIO_MODE_OUT				1
#define GPIO_MODE_ALTFN				2
#define GPIO_MODE_ANALOG			3
#define GPIO_MODE_IT_FT				4
#define GPIO_MODE_IT_RT				5
#define GPIO_MODE_IT_RFT			6

//GPIO pin possible output types
#define GPIO_OP_TYPE_PP				0
#define GPIO_OP_TYPE_OD				1

//GPIO pin possible output speeds
#define GPIO_OP_SPEED_LOW			0
#define GPIO_OP_SPEED_MEDIUM		1
#define GPIO_OP_SPEED_FAST			2
#define GPIO_OP_SPEED_HIGH			3

//GPIO pin pull up and pull down configuration macros
#define GPIO_PIN_NO_PUPD			0
#define GPIO_PIN_PU					1
#define GPIO_PIN_PD					2



/************************************APIs supported by this driver*****************************************/

//peripheral clock setup
void GPIO_peri_clock_control(GPIO_reg_def_t *pGPIOx, uint8_t en_or_di);

//initialization and de-initialization
void GPIO_init(GPIO_handle_t *pGPIO_handle);
void GPIO_deinit(GPIO_reg_def_t *pGPIOx);

//data read and write
uint8_t GPIO_read_input_pin(GPIO_reg_def_t *pGPIOx, uint8_t pin_number);
uint16_t GPIO_read_input_port(GPIO_reg_def_t *pGPIOx);
void GPIO_write_output_pin(GPIO_reg_def_t *pGPIOx, uint8_t pin_number, uint8_t value);
void GPIO_write_output_port(GPIO_reg_def_t *pGPIOx, uint16_t value);
void GPIO_toggle_output_pin(GPIO_reg_def_t *pGPIOx, uint8_t pin_number);

//IRQ configuration and ISR handling
void GPIO_IRQ_config(uint8_t IRQ_number, uint8_t IRQ_priority, uint8_t en_or_di);
void GPIO_IRQ_handling(uint8_t pin_number);


#endif /* INC_STM32F446RE_GPIO_DRIVER_H_ */
