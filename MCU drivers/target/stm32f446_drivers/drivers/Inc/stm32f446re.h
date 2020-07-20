/*
 * stm32f446re.h
 *
 *  Created on: Jul 6, 2020
 *      Author: Robert Peric
 */

#ifndef INC_STM32F446RE_H_
#define INC_STM32F446RE_H_


#include<stdint.h>


#define __vo volatile



/**************************************START: PROCESSOR SPECIFIC DETAILS****************************************/

//ARM Cortex M4 Processor NVIC ISERx register addresses
#define NVIC_ISER0				((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1				((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2				((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3				((__vo uint32_t*)0xE000E10C)

//ARM Cortex M4 Processor NVIC ICERx register addresses
#define NVIC_ICER0				((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1				((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2				((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3				((__vo uint32_t*)0xE000E18C)

//ARM Cortex M4 Processor NVIC IPR0x register addresses
#define NVIC_IPRO_BASSE_ADDR	((__vo uint32_t*)0xE000E400)

//ARM Cortex M4 Processor number of priority bits implemented in priority register
#define NO_PR_BITS_IMPLEMENTED	4
/****************************************END: PROCESSOR SPECIFIC DETAILS****************************************/



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

#define RCC_BASE_ADDR			(AHB1_BASE_ADDR + 0x3800)
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




/********************************peripheral register definition structures**********************/

typedef struct{
	__vo uint32_t MODER;			//address offset :0x00. GPIO port mode register.
	__vo uint32_t OTYPER;			//address offset :0x04. GPIO port output type register.
	__vo uint32_t OSPEEDR;			//address offset :0x08. GPIO port output speed register.
	__vo uint32_t PUPDR;			//address offset :0x0C. GPIO port pull-up/pull-down register.
	__vo uint32_t IDR;				//address offset :0x10. GPIO port input data register.
	__vo uint32_t ODR;				//address offset :0x14. GPIO port output data register.
	__vo uint32_t BSRR;				//address offset :0x18. GPIO port bit set/reset register.
	__vo uint32_t LCKR;				//address offset :0x1C. GPIO port configuration lock register.
	__vo uint32_t AFRLOW;			//address offset :0x20. GPIO alternate function low register.
	__vo uint32_t AFRHIGH;			//address offset :0x24. GPIO alternate function high register.
}GPIO_reg_def_t;

typedef struct{
	__vo uint32_t CR;				//address offset :0x00. RCC clock control register
	__vo uint32_t PLLCFGR;			//address offset :0x04. RCC PLL configuration register
	__vo uint32_t CFGR;				//address offset :0x08. RCC clock configuration register
	__vo uint32_t CIR;				//address offset :0x0C. RCC clock interrupt register
	__vo uint32_t AHB1RSTR;			//address offset :0x10. RCC AHB1 peripheral reset register
	__vo uint32_t AHB2RSTR;			//address offset :0x14. RCC AHB2 peripheral reset register
	__vo uint32_t AHB3RSTR;			//address offset :0x18. RCC AHB3 peripheral reset register
	uint32_t RESERVED0;				//address offset :0x1C.
	__vo uint32_t APB1RSTR;			//address offset :0x20. RCC APB1 peripheral reset register
	__vo uint32_t APB2RSTR;			//address offset :0x24. RCC APB2 peripheral reset register
	uint32_t RESERVED1;				//address offset :0x28.
	uint32_t RESERVED2;				//address offset :0x2C.
	__vo uint32_t AHB1ENR;			//address offset :0x30. RCC AHB1 peripheral clock enable register
	__vo uint32_t AHB2ENR;			//address offset :0x34. RCC AHB2 peripheral clock enable register
	__vo uint32_t AHB3ENR;			//address offset :0x38. RCC AHB3 peripheral clock enable register
	uint32_t RESERVED3;				//address offset :0x3C.
	__vo uint32_t APB1ENR;			//address offset :0x40. RCC APB1 peripheral clock enable register
	__vo uint32_t APB2ENR;			//address offset :0x44. RCC APB2 peripheral clock enable register
	uint32_t RESERVED4;				//address offset :0x48.
	uint32_t RESERVED5;				//address offset :0x4C.
	__vo uint32_t AHB1LPENR;		//address offset :0x50. RCC AHB1 peripheral clock enable in low power mode register
	__vo uint32_t AHB2LPENR;		//address offset :0x54. RCC AHB2 peripheral clock enable in low power mode register
	__vo uint32_t AHB3LPENR;		//address offset :0x58. RCC AHB3 peripheral clock enable in low power mode register
	uint32_t RESERVED6;				//address offset :0x5C.
	__vo uint32_t APB1LPENR;		//address offset :0x60. RCC APB1 peripheral clock enable in low power mode register
	__vo uint32_t APB2LPENR;		//address offset :0x64. RCC APB2 peripheral clock enable in low power mode register
	uint32_t RESERVED7;				//address offset :0x68.
	uint32_t RESERVED8;				//address offset :0x6C.
	__vo uint32_t BDCR;				//address offset :0x70. RCC Backup domain control register
	__vo uint32_t CSR;				//address offset :0x74. RCC clock control & status register
	uint32_t RESERVED9;				//address offset :0x78.
	uint32_t RESERVED10;			//address offset :0x7C.
	__vo uint32_t SSCGR;			//address offset :0x80. RCC spread spectrum clock generation register
	__vo uint32_t PLLI2SCFGR;		//address offset :0x84. RCC PLLI2S configuration register
	__vo uint32_t PLLSAICFGR;		//address offset :0x88. RCC PLL configuration register
	__vo uint32_t DCKCFGR;			//address offset :0x8C. RCC Dedicated Clock Configuration Register
	__vo uint32_t CKGATENR;			//address offset :0x90. RCC clocks gated enable register
	__vo uint32_t DCKCFGR2;			//address offset :0x94. RCC dedicated clocks configuration register 2
}RCC_reg_def_t;

typedef struct{
	__vo uint32_t IMR;				//address offset :0x00. Interrupt mask register.
	__vo uint32_t EMR;				//address offset :0x04. Event mask register
	__vo uint32_t RTSR;				//address offset :0x08. Rising trigger selection register
	__vo uint32_t FTSR;				//address offset :0x0C. Falling trigger selection register
	__vo uint32_t SWIER;			//address offset :0x10. Software interrupt event register
	__vo uint32_t PR;				//address offset :0x14. Pending register
}EXTI_reg_def_t;

typedef struct{
	__vo uint32_t MEMRMP;			//address offset :0x00. SYSCFG memory remap register
	__vo uint32_t PMC;				//address offset :0x04. SYSCFG peripheral mode configuration register
	__vo uint32_t EXTICR[4];		//address offset :0x08-0x14. SYSCFG external interrupt configuration registers
	uint32_t RESERVED1[2];			//address offset :0x18-0x1C.
	__vo uint32_t CMPCR;			//address offset :0x20. Compensation cell control register
	uint32_t RESERVED2[2];			//address offset :0x24-0x28.
	__vo uint32_t CFGR;				//address offset :0x2C. SYSCFG configuration register
}SYSCFG_reg_def_t;

//peripheral definitions (peripheral base addresses typecasted to xxx_reg_def_t)
#define GPIOA					((GPIO_reg_def_t*) GPIOA_BASE_ADDR)
#define GPIOB					((GPIO_reg_def_t*) GPIOB_BASE_ADDR)
#define GPIOC					((GPIO_reg_def_t*) GPIOC_BASE_ADDR)
#define GPIOD					((GPIO_reg_def_t*) GPIOD_BASE_ADDR)
#define GPIOE					((GPIO_reg_def_t*) GPIOE_BASE_ADDR)
#define GPIOF					((GPIO_reg_def_t*) GPIOF_BASE_ADDR)
#define GPIOG					((GPIO_reg_def_t*) GPIOG_BASE_ADDR)
#define GPIOH					((GPIO_reg_def_t*) GPIOH_BASE_ADDR)

#define RCC						((RCC_reg_def_t*) RCC_BASE_ADDR)

#define EXTI					((EXTI_reg_def_t*) EXTI_BASE_ADDR)

#define SYSCFG					((SYSCFG_reg_def_t*) SYSCFG_BASE_ADDR)

//Clock enable macros for GPIOx peripherals
#define GPIOA_PCLK_EN()			(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()			(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()			(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()			(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()			(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()			(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()			(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()			(RCC->AHB1ENR |= (1 << 7))

//Clock enable macros for I2C peripherals
#define I2C1_PCLK_EN()			(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()			(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()			(RCC->APB1ENR |= (1 << 23))

//Clock enable macros for SPI peripherals
#define SPI1_PCLK_EN()			(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()			(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()			(RCC->APB1ENR |= (1 << 15))

//Clock enable macros for USARTx peripherals
#define USART1_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()		(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()		(RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()			(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()			(RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()		(RCC->APB2ENR |= (1 << 5))

//Clock enable macros for SYSCFG peripheral
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))


//Clock disable macros for GPIOx peripherals
#define GPIOA_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 7))

//Clock disable macros for I2C peripherals
#define I2C1_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 23))

//Clock disable macros for SPI peripherals
#define SPI1_PCLK_DI()			(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 15))

//Clock disable macros for USARTx peripherals
#define USART1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 5))

//Clock disable macros for SYSCFG peripheral
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))


//Macros to reset GPIOx peripherals
#define GPIOA_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)


#define GPIO_EXTI_CODE(x)		(	(x == GPIOA)? 0 :\
									(x == GPIOB)? 1 :\
									(x == GPIOC)? 2 :\
									(x == GPIOD)? 3 :\
									(x == GPIOE)? 4 :\
									(x == GPIOF)? 5 :\
									(x == GPIOG)? 6 :\
									(x == GPIOH)? 7 :0 )
//IRQ EXTI numbers macros
#define IRQ_NO_EXTI_0			6
#define IRQ_NO_EXTI_1			7
#define IRQ_NO_EXTI_2			8
#define IRQ_NO_EXTI_3			9
#define IRQ_NO_EXTI_4			10
#define IRQ_NO_EXTI_9_5			23
#define IRQ_NO_EXTI_15_10		40

//some generic macros
#define HIGH					1
#define LOW						0
#define ENABLE 					1
#define DISABLE 				0
#define SET 					ENABLE
#define RESET 					DISABLE
#define GPIO_PIN_SET			SET
#define GPIO_PIN_RESET			RESET


#include "stm32f446re_gpio_driver.h"

#endif /* INC_STM32F446RE_H_ */