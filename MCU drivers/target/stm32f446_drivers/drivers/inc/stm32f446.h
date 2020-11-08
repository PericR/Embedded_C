/*
 * stm32f446.h
 *
 *  Created on: Nov 8, 2020
 *      Author: robert
 */

#ifndef INC_STM32F446_H_
#define INC_STM32F446_H_

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
#define I2C1_BASEADDR						(APB1_PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR						(APB1_PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR						(APB1_PERIPH_BASE + 0x5C00)

#define SPI2_BASEADDR						(APB1_PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR						(APB1_PERIPH_BASE + 0x3C00)

#define USART2_BASEADDR						(APB1_PERIPH_BASE + 0x4400)
#define USART3_BASEADDR						(APB1_PERIPH_BASE + 0x4800)

#define UART4_BASEADDR						(APB1_PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR						(APB1_PERIPH_BASE + 0x5000)



#endif /* INC_STM32F446_H_ */
