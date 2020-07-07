/*
 * stm32f446re_gpio_driver.c
 *
 *  Created on: Jul 6, 2020
 *      Author: Robert Peric
 */

#include "stm32f446re_gpio_driver.h"

//peripheral clock enable or disable
/************************************************
 * @fn					- GPIO_peri_clock_control
 *
 * @brief				- This function enables or disables peripheral clock for the given GPIO port
 *
 * @params[in]			- base address of the GPIO peripheral
 * @params[in]			- ENABLE or DISABLE macros
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_peri_clock_control(GPIO_reg_def_t *pGPIOx, uint8_t en_or_di) {
	if (en_or_di == ENABLE) {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_EN();
		} else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_EN();
		} else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_EN();
		} else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_EN();
		} else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_EN();
		} else if (pGPIOx == GPIOF) {
			GPIOF_PCLK_EN();
		} else if (pGPIOx == GPIOG) {
			GPIOG_PCLK_EN();
		} else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_EN();
		}
	} else {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_DI();
		} else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_DI();
		} else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_DI();
		} else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_DI();
		} else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_DI();
		} else if (pGPIOx == GPIOF) {
			GPIOF_PCLK_DI();
		} else if (pGPIOx == GPIOG) {
			GPIOG_PCLK_DI();
		} else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_DI();
		}
	}
}

//initialization and de-initialization

/************************************************
 * @fn					- GPIO_init
 *
 * @brief				- This function initialize given pin
 *
 * @params[in]			- GPIO handle which contains base port address and pin configuration settings
 *
 * @return				- none
 *
 * @note				- none
 *
 */
void GPIO_init(GPIO_handle_t *pGPIO_handle) {
	uint32_t reset = 0;
	uint32_t set = 0;

	//configure the mode of GPIO pin
	if(pGPIO_handle->GPIO_pin_config.GPIO_pin_mode <= GPIO_MODE_ANALOG){
		//the non interrupt mode
		reset = (11 << (2 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
		pGPIO_handle->pGPIOx->MODER &= ~(reset);
		reset = 0;

		set = (pGPIO_handle->GPIO_pin_config.GPIO_pin_mode << (2 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
		pGPIO_handle->pGPIOx->MODER |= set;
		set = 0;
	}else{
		//interrupt mode
	}

	//configure the speed of GPIO pin
	reset = (11 << (2 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
	pGPIO_handle->pGPIOx->OSPEEDR &= ~(reset);
	reset = 0;

	set = (pGPIO_handle->GPIO_pin_config.GPIO_pin_speed << (2 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
	pGPIO_handle->pGPIOx->OSPEEDR |= set;
	set = 0;


	//configure the pull up and pull down resistor of GPIO pin
	reset = (11 << (2 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
	pGPIO_handle->pGPIOx->PUPDR &= ~(reset);
	reset = 0;

	set = (pGPIO_handle->GPIO_pin_config.GPIO_pin_pu_pd << (2 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
	pGPIO_handle->pGPIOx->PUPDR |= set;
	set = 0;


	//configure the output type register of GPIO pin
	reset = (11 << (2 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
	pGPIO_handle->pGPIOx->OTYPER &= ~(reset);
	reset = 0;

	set = (pGPIO_handle->GPIO_pin_config.GPIO_pin_op_type << pGPIO_handle->GPIO_pin_config.GPIO_pin_num);
	pGPIO_handle->pGPIOx->OTYPER |= set;
	set = 0;


	//configure the alternative functionality register of GPIO pin
	if(pGPIO_handle->GPIO_pin_config.GPIO_pin_mode == GPIO_MODE_ALTFN){
		if(pGPIO_handle->GPIO_pin_config.GPIO_pin_num <= 7){
			reset = (1111 << (4 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
			pGPIO_handle->pGPIOx->AFRLOW &= ~(reset);
			reset = 0;

			set = (pGPIO_handle->GPIO_pin_config.GPIO_pin_alt_fun_mode << (4 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
			pGPIO_handle->pGPIOx->AFRLOW |= set;
			set = 0;
		}else{
			reset = (1111 << (4 * pGPIO_handle->GPIO_pin_config.GPIO_pin_num));
			pGPIO_handle->pGPIOx->AFRHIGH &= ~(reset);
			reset = 0;

			set = (pGPIO_handle->GPIO_pin_config.GPIO_pin_alt_fun_mode << (4 * (pGPIO_handle->GPIO_pin_config.GPIO_pin_num % 8)));
			pGPIO_handle->pGPIOx->AFRHIGH |= set;
			set = 0;
		}
	}
}

/************************************************
 * @fn					-
 *
 * @brief				-
 *
 * @params[in]			-
 * @params[in]			-
 * @params[in]			-
 *
 * @return				-
 *
 * @note				-
 *
 */
void GPIO_deinit(GPIO_reg_def_t *pGPIOx) {

}

//data read and write

/************************************************
 * @fn					-
 *
 * @brief				-
 *
 * @params[in]			-
 * @params[in]			-
 * @params[in]			-
 *
 * @return				-
 *
 * @note				-
 *
 */
uint8_t GPIO_read_input_pin(GPIO_reg_def_t *pGPIOx, uint8_t pin_number) {

}

/************************************************
 * @fn					-
 *
 * @brief				-
 *
 * @params[in]			-
 * @params[in]			-
 * @params[in]			-
 *
 * @return				-
 *
 * @note				-
 *
 */
uint16_t GPIO_read_input_port(GPIO_reg_def_t *pGPIOx) {

}

/************************************************
 * @fn					-
 *
 * @brief				-
 *
 * @params[in]			-
 * @params[in]			-
 * @params[in]			-
 *
 * @return				-
 *
 * @note				-
 *
 */
void GPIO_write_output_pin(GPIO_reg_def_t *pGPIOx, uint8_t pin_number,
		uint8_t value) {

}

/************************************************
 * @fn					-
 *
 * @brief				-
 *
 * @params[in]			-
 * @params[in]			-
 * @params[in]			-
 *
 * @return				-
 *
 * @note				-
 *
 */
void GPIO_write_output_port(GPIO_reg_def_t *pGPIOx, uint16_t value) {

}

/************************************************
 * @fn					-
 *
 * @brief				-
 *
 * @params[in]			-
 * @params[in]			-
 * @params[in]			-
 *
 * @return				-
 *
 * @note				-
 *
 */
void GPIO_toggle_output_pin(GPIO_reg_def_t *pGPIOx, uint8_t pin_number) {

}

//IRQ configuration and ISR handling

/************************************************
 * @fn					-
 *
 * @brief				-
 *
 * @params[in]			-
 * @params[in]			-
 * @params[in]			-
 *
 * @return				-
 *
 * @note				-
 *
 */
void GPIO_IRQ_config(uint8_t IRQ_number, uint8_t IRQ_priority, uint8_t en_or_di) {

}

/************************************************
 * @fn					-
 *
 * @brief				-
 *
 * @params[in]			-
 * @params[in]			-
 * @params[in]			-
 *
 * @return				-
 *
 * @note				-
 *
 */
void GPIO_IRQ_handling(uint8_t pin_number) {

}

