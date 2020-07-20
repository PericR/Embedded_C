/*
 * 005_ext_btn_interrupt.c
 *
 *  Created on: Jul 20, 2020
 *      Author: robert
 */

#include <stdio.h>
#include <string.h>
#include "stm32f446re.h"

#define BTN_PRESSED LOW

void delay(void){
	for(uint32_t i = 0; i < 3000000; i++);
}

int main(void)
{
	GPIO_handle_t gpio_led;
	memset(&gpio_led, 0, sizeof(gpio_led));

	gpio_led.pGPIOx = GPIOA;
	gpio_led.GPIO_pin_config.GPIO_pin_num = GPIO_PIN_NO_10;
	gpio_led.GPIO_pin_config.GPIO_pin_mode = GPIO_MODE_OUT;
	gpio_led.GPIO_pin_config.GPIO_pin_speed = GPIO_OP_SPEED_FAST;
	gpio_led.GPIO_pin_config.GPIO_pin_op_type = GPIO_OP_TYPE_PP;
	gpio_led.GPIO_pin_config.GPIO_pin_pu_pd = GPIO_PIN_NO_PUPD;

	GPIO_handle_t gpio_button;
	memset(&gpio_button, 0, sizeof(gpio_button));

	gpio_button.pGPIOx = GPIOB;
	gpio_button.GPIO_pin_config.GPIO_pin_num = GPIO_PIN_NO_12;
	gpio_button.GPIO_pin_config.GPIO_pin_mode = GPIO_MODE_IT_FT;
	gpio_button.GPIO_pin_config.GPIO_pin_speed = GPIO_OP_SPEED_FAST;
	gpio_button.GPIO_pin_config.GPIO_pin_pu_pd = GPIO_PIN_PU;

	GPIO_peri_clock_control(GPIOA, ENABLE);
	GPIO_peri_clock_control(GPIOB, ENABLE);

	GPIO_init(&gpio_led);
	GPIO_init(&gpio_button);

	//IRQ configurations
	GPIO_IRQ_priority_config(IRQ_NO_EXTI_15_10, IRQ_PR_15);
	GPIO_IRQ_interrupt_config(IRQ_NO_EXTI_15_10, ENABLE);

	for(;;);
}

void EXTI15_10_IRQHandler(void){

	GPIO_IRQ_handling(GPIO_PIN_NO_12);
	GPIO_toggle_output_pin(GPIOA, GPIO_PIN_NO_10);
	delay();
}
