/*
 * 001_led_toggle.c
 *
 *  Created on: Nov 11, 2020
 *      Author: robert
 */


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f446.h"

void delay(){
	for(uint32_t i = 0; i < 500000; i++);
}

int main(void)
{
	GPIO_Handle_t gpioa_led;
	gpioa_led.pGPIOx = GPIOA;
	gpioa_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	gpioa_led.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_OUT;
	gpioa_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;

	GPIO_PeriClockControl(gpioa_led.pGPIOx, ENABLE);
	GPIO_Init(&gpioa_led);

	while(1){
		GPIO_ToggleOutputPin(gpioa_led.pGPIOx, gpioa_led.GPIO_PinConfig.GPIO_PinNumber);
		delay();
	}

	for(;;);
}
