/*
 * main.c
 *
 *  Created on: Jul 20, 2020
 *      Author: robert
 */


#include "stm32f446re.h"

int main(void)
{
	return 0;
}

void EXTI0_IRQHandler(void){
	GPIO_IRQ_handling(0);
}
