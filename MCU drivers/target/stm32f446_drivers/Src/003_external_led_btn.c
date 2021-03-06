/*
 * 003_external_led_btn.c
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
	gpioa_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	gpioa_led.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_OUT;
	gpioa_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OP_TYPE_PP;

	GPIO_Handle_t gpiob_button;
	gpiob_button.pGPIOx = GPIOB;

	gpiob_button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	gpiob_button.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_MODE_IN;
	gpiob_button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(gpioa_led.pGPIOx, ENABLE);
	GPIO_PeriClockControl(gpiob_button.pGPIOx, ENABLE);

	GPIO_Init(&gpioa_led);
	GPIO_Init(&gpiob_button);

	while(1){
		uint8_t button_value = GPIO_ReadFromInputPin(gpiob_button.pGPIOx, gpiob_button.GPIO_PinConfig.GPIO_PinNumber);

		if(!button_value){
			GPIO_ToggleOutputPin(gpioa_led.pGPIOx, gpioa_led.GPIO_PinConfig.GPIO_PinNumber);
			delay();
		}
	}
}
