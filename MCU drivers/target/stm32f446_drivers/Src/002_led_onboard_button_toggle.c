/*
 * 002_led_onboard_button_toggle.c
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
	gpioa_led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioa_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	GPIO_Handle_t gpioc_button;
	gpioc_button.pGPIOx = GPIOC;

	gpioc_button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	gpioc_button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;

	GPIO_PeriClockControl(gpioa_led.pGPIOx, ENABLE);
	GPIO_PeriClockControl(gpioc_button.pGPIOx, ENABLE);

	GPIO_Init(&gpioa_led);
	GPIO_Init(&gpioc_button);

	while(1){
		uint8_t button_value = GPIO_ReadFromInputPin(gpioc_button.pGPIOx, gpioc_button.GPIO_PinConfig.GPIO_PinNumber);

		if(!button_value){
			GPIO_ToggleOutputPin(gpioa_led.pGPIOx, gpioa_led.GPIO_PinConfig.GPIO_PinNumber);
			delay();
		}
	}
}
