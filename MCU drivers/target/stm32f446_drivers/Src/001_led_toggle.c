/*
 * 001_led_toggle.c
 *
 *  Created on: Jul 16, 2020
 *      Author: robert
 */

#include "stm32f446re.h"

void delay(void){
	for(uint32_t i = 0; i < 500000; i++){

	}
}

int main(void)
{
	GPIO_handle_t gpio_led;
	gpio_led.pGPIOx = GPIOA;
	gpio_led.GPIO_pin_config.GPIO_pin_num = GPIO_PIN_NO_5;
	gpio_led.GPIO_pin_config.GPIO_pin_mode = GPIO_MODE_OUT;
	gpio_led.GPIO_pin_config.GPIO_pin_speed = GPIO_OP_SPEED_FAST;
	gpio_led.GPIO_pin_config.GPIO_pin_op_type = GPIO_OP_TYPE_PP;
	gpio_led.GPIO_pin_config.GPIO_pin_pu_pd = GPIO_PIN_NO_PUPD;

	GPIO_handle_t gpio_button;
	gpio_button.pGPIOx = GPIOC;
	gpio_button.GPIO_pin_config.GPIO_pin_num = GPIO_PIN_NO_13;
	gpio_button.GPIO_pin_config.GPIO_pin_mode = GPIO_MODE_IN;
	gpio_button.GPIO_pin_config.GPIO_pin_speed = GPIO_OP_SPEED_FAST;
	gpio_button.GPIO_pin_config.GPIO_pin_pu_pd = GPIO_PIN_NO_PUPD;


	GPIO_peri_clock_control(GPIOA, ENABLE);
	GPIO_peri_clock_control(GPIOC, ENABLE);

	GPIO_init(&gpio_led);
	GPIO_init(&gpio_button);

	while(1){
		if(GPIO_read_input_pin(GPIOC, GPIO_PIN_NO_13) == 0){
			delay();
			GPIO_toggle_output_pin(GPIOA, GPIO_PIN_NO_5);
		}
	}

	return 0;
}