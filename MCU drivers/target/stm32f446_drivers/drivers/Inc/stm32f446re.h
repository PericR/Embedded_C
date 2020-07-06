/*
 * stm32f446re.h
 *
 *  Created on: Jul 6, 2020
 *      Author: Robert Peric
 */

#ifndef INC_STM32F446RE_H_
#define INC_STM32F446RE_H_

//base addresses of flash and SRAM memories
#define FLASH_BASE_ADDR			0x08000000U								//starting address of flash memory with size of 512kb
#define ROM_BASE_ADDR			0x1FFF0000U								//starting address of ROM memory with size of 30kb
#define SRAM1_BASE_ADDR			0x20000000U								//starting address of SRAM1 memory with size of 112kb
#define SRAM2_BASE_ADDR			(SRAM1_BASE_ADDR + (1024 * 112))U		//starting address of SRAM2 memory with size of 16kb
#define SRAM_BASE_ADDR			SRAM1_BASE_ADDR							//starting address of SRAM memory with size of 128kb


//AHBx and APBx base addresses
#define PERIPH_BASE_ADDR		0x40000000U								//starting address of peripherals
#define APB1_BASE_ADDR			0x40000000U								//starting address of APB1 peripheral
#define APB2_BASE_ADDR			0x40010000U								//starting address of APB2 peripheral
#define AHB1_BASE_ADDR			0x40020000U								//starting address of AHB1 peripheral
#define AHB2_BASE_ADDR			0x50000000U								//starting address of AHB2 peripheral


//base addresses of peripherals that are hanging on AHB1 bus
#define GPIOA_BASE_ADDR			(AHB1_BASE_ADDR + 0x0000)				//base address of general purpose IO pins on port A
#define GPIOB_BASE_ADDR			(AHB1_BASE_ADDR + 0x0400)				//base address of general purpose IO pins on port B
#define GPIOC_BASE_ADDR			(AHB1_BASE_ADDR + 0x0800)				//base address of general purpose IO pins on port C
#define GPIOD_BASE_ADDR			(AHB1_BASE_ADDR + 0x0C00)				//base address of general purpose IO pins on port D
#define GPIOE_BASE_ADDR			(AHB1_BASE_ADDR + 0x1000)				//base address of general purpose IO pins on port E
#define GPIOF_BASE_ADDR			(AHB1_BASE_ADDR + 0x1400)				//base address of general purpose IO pins on port F
#define GPIOG_BASE_ADDR			(AHB1_BASE_ADDR + 0x1800)				//base address of general purpose IO pins on port G
#define GPIOH_BASE_ADDR			(AHB1_BASE_ADDR + 0x1C00)				//base address of general purpose IO pins on port H


//base addresses of peripherals that are hanging on APB1 bus
#define I2C1_BASE_ADDR			(APB1_BASE_ADDR + 0x5400)				//base address of 12C1 peripheral
#define I2C2_BASE_ADDR			(APB1_BASE_ADDR + 0x5800)				//base address of 12C2 peripheral
#define I2C3_BASE_ADDR			(APB1_BASE_ADDR + 0x5C00)				//base address of 12C3 peripheral

#define SPI2_BASE_ADDR			(APB1_BASE_ADDR + 0x3800)				//base address of serial peripheral interface 1 peripheral
#define SPI3_BASE_ADDR			(APB1_BASE_ADDR + 0x3C00)				//base address of serial peripheral interface 2 peripheral

#define USART2_BASE_ADDR		(APB1_BASE_ADDR + 0x4400)				//base address of universal synchronous and asynchronous receiver and transmitter 2 peripheral
#define USART3_BASE_ADDR		(APB1_BASE_ADDR + 0x4800)				//base address of universal synchronous and asynchronous receiver and transmitter 3 peripheral
#define UART4_BASE_ADDR			(APB1_BASE_ADDR + 0x4C00)				//base address of universal asynchronous receiver and transmitter 4 peripheral
#define UART5_BASE_ADDR			(APB1_BASE_ADDR + 0x5000)				//base address of universal asynchronous receiver and transmitter 5 peripheral


//base addresses of peripherals that are hanging on APB2 bus
#define EXTI_BASE_ADDR			(APB2_BASE_ADDR + 0x3C00)				//base address of external interrupt peripheral
#define SPI1_BASE_ADDR			(APB2_BASE_ADDR + 0x3000)				//base address of serial peripheral 1 peripheral
#define USART1_BASE_ADDR		(APB2_BASE_ADDR + 0x1000)				//base address of universal synchronous and asynchronous receiver 1 peripheral
#define USART6_BASE_ADDR		(APB2_BASE_ADDR + 0x1400)				//base address of universal synchronous and asynchronous receiver 6 peripheral
#define SYSCFG_BASE_ADDR		(APB2_BASE_ADDR + 0x3800)				//base address of system configuration controller

#endif /* INC_STM32F446RE_H_ */
