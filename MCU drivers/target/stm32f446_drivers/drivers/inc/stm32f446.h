/*
 * stm32f446.h
 *
 *  Created on: Nov 8, 2020
 *      Author: robert
 */

#ifndef INC_STM32F446_H_
#define INC_STM32F446_H_

#include <stdint.h>

#define __vo volatile

/*************************BASE ADDRESSES OF MEMORY AND PERIPHERALS*************************/
/*
 * Base addresses of flash and SRAM memories
 */
#define FLASH_BASEADDR						0x08000000U		/*Base address of Flash memory*/
#define SRAM1_BASEADDR						0x20000000U		/*Base address of SRAM1 memory*/
#define SRAM2_BASEADDR						0x2001C000U		/*Base address of SRAM2 memory*/
#define ROM_BASEADDR						0x1FFF0000U		/*Base address of ROM memory*/
#define SRAM 								SRAM1_BASEADDR	/*Base address of SRAM memory*/

/*
 * Base addresses of flash and SRAM memories
 */
#define PERIPH_BASE							0x40000000U		/*Base address of Peripherals*/
#define APB1_PERIPH_BASE					PERIPH_BASE		/*Base address of APB1 Peripheral*/
#define APB2_PERIPH_BASE					0x40010000U		/*Base address of APB2 Peripheral*/
#define AHB1_PERIPH_BASE					0x40020000U		/*Base address of AHB1 Peripheral*/
#define AHB2_PERIPH_BASE					0x50000000U		/*Base address of AHB2 Peripheral*/
#define AHB3_PERIPH_BASE					0x60000000U		/*Base address of AHB3 Peripheral*/

/*
 * Base addresses of peripherals hanging on AHB1 bus
 */
#define GPIOA_BASEADDR						(AHB1_PERIPH_BASE + 0x0000)U	/*Base address of GPIOA Peripheral*/
#define GPIOB_BASEADDR						(AHB1_PERIPH_BASE + 0x0400)U	/*Base address of GPIOB Peripheral*/
#define GPIOC_BASEADDR						(AHB1_PERIPH_BASE + 0x0800)U	/*Base address of GPIOC Peripheral*/
#define GPIOD_BASEADDR						(AHB1_PERIPH_BASE + 0x0C00)U	/*Base address of GPIOD Peripheral*/
#define GPIOE_BASEADDR						(AHB1_PERIPH_BASE + 0x1000)U	/*Base address of GPIOE Peripheral*/
#define GPIOF_BASEADDR						(AHB1_PERIPH_BASE + 0x1400)U	/*Base address of GPIOF Peripheral*/
#define GPIOG_BASEADDR						(AHB1_PERIPH_BASE + 0x1800)U	/*Base address of GPIOG Peripheral*/
#define GPIOH_BASEADDR						(AHB1_PERIPH_BASE + 0x1C00)U	/*Base address of GPIOH Peripheral*/

/*
 * Base addresses of peripherals hanging on APB1 bus
 */
#define I2C1_BASEADDR						(APB1_PERIPH_BASE + 0x5400)U	/*Base address of I2C1 Peripheral*/
#define I2C2_BASEADDR						(APB1_PERIPH_BASE + 0x5800)U	/*Base address of I2C2 Peripheral*/
#define I2C3_BASEADDR						(APB1_PERIPH_BASE + 0x5C00)U	/*Base address of I2C3 Peripheral*/

#define SPI2_BASEADDR						(APB1_PERIPH_BASE + 0x3800)U	/*Base address of SPI2 Peripheral*/
#define SPI3_BASEADDR						(APB1_PERIPH_BASE + 0x3C00)U	/*Base address of SPI3 Peripheral*/

#define USART2_BASEADDR						(APB1_PERIPH_BASE + 0x4400)U	/*Base address of USART2 Peripheral*/
#define USART3_BASEADDR						(APB1_PERIPH_BASE + 0x4800)U	/*Base address of USART3 Peripheral*/

#define UART4_BASEADDR						(APB1_PERIPH_BASE + 0x4C00)U	/*Base address of UART4 Peripheral*/
#define UART5_BASEADDR						(APB1_PERIPH_BASE + 0x5000)U	/*Base address of UART5 Peripheral*/

/*
 * Base addresses of peripherals hanging on APB2 bus
 */
#define SPI1_BASEADDR						(APB2_PERIPH_BASE + 0x3000)U	/*Base address of SPI1 Peripheral*/
#define SPI4_BASEADDR						(APB2_PERIPH_BASE + 0x3400)U	/*Base address of SPI4 Peripheral*/

#define USART1_BASEADDR						(APB2_PERIPH_BASE + 0x1000)U	/*Base address of USART1 Peripheral*/
#define USART6_BASEADDR						(APB2_PERIPH_BASE + 0x1400)U	/*Base address of USART6 Peripheral*/

#define EXTI_BASEADDR						(APB2_PERIPH_BASE + 0x3C00)U	/*Base address of EXTI Peripheral*/
#define SYSCFG_BASEADDR						(APB2_PERIPH_BASE + 0x4000)U	/*Base address of SYSCFG Peripheral*/


/*************************PERIPHERAL REGISTER DEFINITION STRUCTURES**********************/

/*
 *	peripheral register definition structure for GPIO
 */
typedef struct{
	__vo uint32_t MODER;					/*address offset: 0x00		GPIO port mode register*/
	__vo uint32_t OTYPER;					/*address offset: 0x04 		GPIO port output type register*/
	__vo uint32_t OSPEEDER;					/*address offset: 0x08 		GPIO port output speed register*/
	__vo uint32_t PUPDR;					/*address offset: 0x0C 		GPIO port pull-up/pull-down register*/
	__vo uint32_t IDR;						/*address offset: 0x10 		GPIO port input data register*/
	__vo uint32_t ODR;						/*address offset: 0x14 		GPIO port output data register*/
	__vo uint32_t BSRR;						/*address offset: 0x18 		GPIO port bit set/reset register*/
	__vo uint32_t LCKR;						/*address offset: 0x1C 		GPIO port configuration lock register*/
	__vo uint32_t AFR[2];					/*address offset: 0x20 		[0] = GPIO alternate function low register, [1] = GPIO alternate function high register*/
}GPIO_RegDef_t;

/*
 *	peripheral definitions
 */
#define GPIOA								((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB								((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC								((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD								((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE								((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF								((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG								((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH								((GPIO_RegDef_t*) GPIO_BASEADDR)

#endif /* INC_STM32F446_H_ */
