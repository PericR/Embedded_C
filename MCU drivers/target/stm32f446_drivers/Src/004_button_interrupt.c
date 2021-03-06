/*
 * 004_button_interrupt.c
 *
 *  Created on: Nov 13, 2020
 *      Author: robert
 */


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <string.h>
#include "stm32f446.h"

void delay(){
	for(uint32_t i = 0; i < 500000; i++);
}

int main(void){
	GPIO_Handle_t gpio_led, gpio_btn;
	memset(&gpio_led, 0 ,sizeof(gpio_led));
	memset(&gpio_btn, 0 ,sizeof(gpio_btn));

	gpio_led.pGPIOx = GPIOA;
	gpio_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	gpio_led.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_OUT;
	gpio_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;
	gpio_led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;

	gpio_btn.pGPIOx = GPIOB;
	gpio_btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	gpio_btn.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_IT_FT;
	gpio_btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


	GPIO_PeriClockControl(gpio_led.pGPIOx, ENABLE);
	GPIO_PeriClockControl(gpio_btn.pGPIOx, ENABLE);

	GPIO_Init(&gpio_led);
	GPIO_Init(&gpio_btn);


	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

	for(;;);
}

void EXTI15_10_IRQHandler(void){
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_10);
	delay();

	GPIO_IRQHandling(GPIO_PIN_NO_12);
}

