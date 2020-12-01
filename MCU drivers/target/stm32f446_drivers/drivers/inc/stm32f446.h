/*
 * stm32f446.h
 *
 *  Created on: Nov 8, 2020
 *      Author: Robert
 */

#ifndef INC_STM32F446_H_
#define INC_STM32F446_H_

#include <stdint.h>


#define __vo volatile

/*********************************PROCESSOR SPRECIFIC DETAILS*******************************/

/*
 *	ARM cortex M4 processor NVIC ISERx register addresses
 */
#define NVIC_ISER0							((__vo uint32_t*) 0xE000E100)
#define NVIC_ISER1							((__vo uint32_t*) 0xE000E104)
#define NVIC_ISER2							((__vo uint32_t*) 0xE000E108)
#define NVIC_ISER3							((__vo uint32_t*) 0xE000E10C)

/*
 *	ARM cortex M4 processor NVIC ICERx register addresses
 */
#define NVIC_ICER0							((__vo uint32_t*) 0xE000E180)
#define NVIC_ICER1							((__vo uint32_t*) 0xE000E184)
#define NVIC_ICER2							((__vo uint32_t*) 0xE000E188)
#define NVIC_ICER3							((__vo uint32_t*) 0xE000E18C)

/*
 * ARM cortex M4 processor priority register address calculations
 */
#define NVIC_PR_BASE_ADDR 					((__vo uint32_t*) 0xE000E400)


/*
 * ARM cortex M4 processor number of priority bits implemented in priority register
 */
#define NO_PR_BITS_IMPLEMENTED				4

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
 * Base addresses of bus peripherals
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
#define RCC_BASEADDR						(AHB1_PERIPH_BASE + 0x3800)		/*Base address of RCC Peripheral*/

#define GPIOA_BASEADDR						(AHB1_PERIPH_BASE + 0x0000)		/*Base address of GPIOA Peripheral*/
#define GPIOB_BASEADDR						(AHB1_PERIPH_BASE + 0x0400)		/*Base address of GPIOB Peripheral*/
#define GPIOC_BASEADDR						(AHB1_PERIPH_BASE + 0x0800)		/*Base address of GPIOC Peripheral*/
#define GPIOD_BASEADDR						(AHB1_PERIPH_BASE + 0x0C00)		/*Base address of GPIOD Peripheral*/
#define GPIOE_BASEADDR						(AHB1_PERIPH_BASE + 0x1000)		/*Base address of GPIOE Peripheral*/
#define GPIOF_BASEADDR						(AHB1_PERIPH_BASE + 0x1400)		/*Base address of GPIOF Peripheral*/
#define GPIOG_BASEADDR						(AHB1_PERIPH_BASE + 0x1800)		/*Base address of GPIOG Peripheral*/
#define GPIOH_BASEADDR						(AHB1_PERIPH_BASE + 0x1C00)		/*Base address of GPIOH Peripheral*/

/*
 * Base addresses of peripherals hanging on APB1 bus
 */
#define I2C1_BASEADDR						(APB1_PERIPH_BASE + 0x5400)		/*Base address of I2C1 Peripheral*/
#define I2C2_BASEADDR						(APB1_PERIPH_BASE + 0x5800)		/*Base address of I2C2 Peripheral*/
#define I2C3_BASEADDR						(APB1_PERIPH_BASE + 0x5C00)		/*Base address of I2C3 Peripheral*/

#define SPI2_BASEADDR						(APB1_PERIPH_BASE + 0x3800)		/*Base address of SPI2 Peripheral*/
#define SPI3_BASEADDR						(APB1_PERIPH_BASE + 0x3C00)		/*Base address of SPI3 Peripheral*/

#define USART2_BASEADDR						(APB1_PERIPH_BASE + 0x4400)		/*Base address of USART2 Peripheral*/
#define USART3_BASEADDR						(APB1_PERIPH_BASE + 0x4800)		/*Base address of USART3 Peripheral*/

#define UART4_BASEADDR						(APB1_PERIPH_BASE + 0x4C00)		/*Base address of UART4 Peripheral*/
#define UART5_BASEADDR						(APB1_PERIPH_BASE + 0x5000)		/*Base address of UART5 Peripheral*/

/*
 * Base addresses of peripherals hanging on APB2 bus
 */
#define SPI1_BASEADDR						(APB2_PERIPH_BASE + 0x3000)		/*Base address of SPI1 Peripheral*/
#define SPI4_BASEADDR						(APB2_PERIPH_BASE + 0x3400)		/*Base address of SPI4 Peripheral*/

#define USART1_BASEADDR						(APB2_PERIPH_BASE + 0x1000)		/*Base address of USART1 Peripheral*/
#define USART6_BASEADDR						(APB2_PERIPH_BASE + 0x1400)		/*Base address of USART6 Peripheral*/

#define EXTI_BASEADDR						(APB2_PERIPH_BASE + 0x3C00)		/*Base address of EXTI Peripheral*/
#define SYSCFG_BASEADDR						(APB2_PERIPH_BASE + 0x3800)		/*Base address of SYSCFG Peripheral*/


/*************************PERIPHERAL REGISTER DEFINITION STRUCTURES**********************/

/*
 *	peripheral register definition structure for RCC
 */
typedef struct{
	__vo uint32_t CR;						/*address offset: 0x00		RCC clock control register*/
	__vo uint32_t PLLCFGR;					/*address offset: 0x04 		RCC PLL configuration register*/
	__vo uint32_t CFGR;						/*address offset: 0x08 		RCC clock configuration register*/
	__vo uint32_t CIR;						/*address offset: 0x0C 		RCC clock interrupt register*/
	__vo uint32_t AHB1RSTR;					/*address offset: 0x10 		RCC AHB1 peripheral reset register*/
	__vo uint32_t AHB2RSTR;					/*address offset: 0x14 		RCC AHB2 peripheral reset register*/
	__vo uint32_t AHB3RSTR;					/*address offset: 0x18 		RCC AHB3 peripheral reset register*/
	uint32_t RESERVED1;						/*address offset: 0x1C 		reserved*/
	__vo uint32_t APB1RSTR;					/*address offset: 0x20 		RCC APB1 peripheral reset register*/
	__vo uint32_t APB2RSTR;					/*address offset: 0x24 		RCC APB2 peripheral reset register*/
	uint32_t RESERVED2[2];					/*address offset: 0x28 		reserved*/
	__vo uint32_t AHB1ENR;					/*address offset: 0x30 		RCC AHB1 peripheral clock enable register*/
	__vo uint32_t AHB2ENR;					/*address offset: 0x34 		RCC AHB2 peripheral clock enable register*/
	__vo uint32_t AHB3ENR;					/*address offset: 0x38 		RCC AHB3 peripheral clock enable register*/
	uint32_t RESERVED3;						/*address offset: 0x3C 		reserved*/
	__vo uint32_t APB1ENR;					/*address offset: 0x40 		RCC APB1 peripheral clock enable register*/
	__vo uint32_t APB2ENR;					/*address offset: 0x44 		RCC APB2 peripheral clock enable register*/
	uint32_t RESERVED4[2];					/*address offset: 0x48 		reserved*/
	__vo uint32_t AHB1LPENR;				/*address offset: 0x50 		RCC AHB1 peripheral clock enable in low power mode register*/
	__vo uint32_t AHB2LPENR;				/*address offset: 0x54 		RCC AHB2 peripheral clock enable in low power mode register*/
	__vo uint32_t AHB3LPENR;				/*address offset: 0x58 		RCC AHB3 peripheral clock enable in low power mode register*/
	uint32_t RESERVED5;						/*address offset: 0x5C 		reserved*/
	__vo uint32_t APB1LPENR;				/*address offset: 0x60 		RCC APB1 peripheral clock enable in low power mode register*/
	__vo uint32_t APB2LPENR;				/*address offset: 0x64 		RCC APB2 peripheral clock enable in low power mode register*/
	uint32_t RESERVED6[2];					/*address offset: 0x68 		reserved*/
	__vo uint32_t BDCR;						/*address offset: 0x70 		RCC Backup domain control register*/
	__vo uint32_t CSR;						/*address offset: 0x74 		RCC clock control & status register*/
	uint32_t RESERVED7[2];					/*address offset: 0x78 		reserved*/
	__vo uint32_t SSCGR;					/*address offset: 0x80 		RCC spread spectrum clock generation register*/
	__vo uint32_t PLLI2SCFGR;				/*address offset: 0x84 		RCC PLLI2S configuration register*/
	__vo uint32_t PLLSAICFGR;				/*address offset: 0x88 		RCC PLL configuration register*/
	__vo uint32_t DCKCFGR;					/*address offset: 0x8C 		RCC Dedicated Clock Configuration Register*/
	__vo uint32_t CKGATENR;					/*address offset: 0x90 		RCC clocks gated enable register*/
	__vo uint32_t DCKCFGR2;					/*address offset: 0x94 		RCC dedicated clocks configuration register 2*/
}RCC_RegDef_t;

/*
 *	peripheral register definition structure for EXTI
 */
typedef struct{
	__vo uint32_t IMR;					/*address offset: 0x00		EXTI port interrupt mask register*/
	__vo uint32_t EMR;					/*address offset: 0x04 		EXTI port Event mask register*/
	__vo uint32_t RTSR;					/*address offset: 0x08 		EXTI port Rising trigger selection register*/
	__vo uint32_t FTSR;					/*address offset: 0x0C 		EXTI port Falling trigger selection register*/
	__vo uint32_t SWIER;				/*address offset: 0x10 		EXTI port Software interrupt event register*/
	__vo uint32_t PR;					/*address offset: 0x14 		EXTI port Pending register*/
}EXTI_RegDef_t;

/*
 *	peripheral register definition structure for SYSCFG
 */
typedef struct{
	__vo uint32_t MEMRMP;					/*address offset: 0x00		SYSCFG memory remap register*/
	__vo uint32_t PMC;						/*address offset: 0x04 		SYSCFG peripheral mode configuration register*/
	__vo uint32_t EXTICR[4];				/*address offset: 0x08 		SYSCFG external interrupt configuration register*/
	uint32_t RESERVED1[2];					/*address offset: 0x18 		reserved*/
	__vo uint32_t CMPCR;					/*address offset: 0x20 		Compensation cell control register*/
	uint32_t RESERVED2[2];					/*address offset: 0x24 		reserved*/
	__vo uint32_t CFGR;						/*address offset: 0x2C 		SYSCFG configuration register*/
}SYSCFG_RegDef_t;

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
 *	peripheral register definition structure for SPI
 */
typedef struct{
	__vo uint32_t CR1;						/*address offset: 0x00		SPI control register 1 (not used in I2S mode)*/
	__vo uint32_t CR2;						/*address offset: 0x04 		SPI control register 2*/
	__vo uint32_t SR;						/*address offset: 0x08 		SPI status register*/
	__vo uint32_t DR;						/*address offset: 0x0C 		SPI data register*/
	__vo uint32_t CRCPR;					/*address offset: 0x10 		SPI CRC polynomial register (not used in I2S mode*/
	__vo uint32_t RXCRCR;					/*address offset: 0x14 		SPI RX CRC register (not used in I 2 S mode)*/
	__vo uint32_t TXCRCR;					/*address offset: 0x18 		SPI RX CRC register (not used in I 2 S mode)*/
	__vo uint32_t I2SCFGR;					/*address offset: 0x1C 		SPI_I2S configuration register*/
	__vo uint32_t I2SPR;					/*address offset: 0x20 		SPI_I2S prescaler register*/
}SPI_RegDef_t;



/*
 *	peripheral definitions
 */
#define RCC									((RCC_RegDef_t*) RCC_BASEADDR)
#define EXTI								((EXTI_RegDef_t*) EXTI_BASEADDR)
#define SYSCFG								((SYSCFG_RegDef_t*) SYSCFG_BASEADDR)

#define GPIOA								((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB								((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC								((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD								((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE								((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF								((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG								((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH								((GPIO_RegDef_t*) GPIOH_BASEADDR)

#define SPI1								((SPI_RegDef_t*) SPI1_BASEADDR)
#define SPI2								((SPI_RegDef_t*) SPI2_BASEADDR)
#define SPI3								((SPI_RegDef_t*) SPI3_BASEADDR)
#define SPI4								((SPI_RegDef_t*) SPI4_BASEADDR)

/*
 *	clock enable macros for GPIO peripherals
 */
#define GPIOA_PCLK_EN()						(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()						(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()						(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()						(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()						(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()						(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()						(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()						(RCC->AHB1ENR |= (1 << 7))

/*
 *	clock enable macros for I2C peripherals
 */
#define I2C1_PCLK_EN()						(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()						(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()						(RCC->APB1ENR |= (1 << 23))

/*
 *	clock enable macros for SPI peripherals
 */
#define SPI1_PCLK_EN()						(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()						(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()						(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()						(RCC->APB2ENR |= (1 << 13))

/*
 *	clock enable macros for USART/UART peripherals
 */
#define USART1_PCLK_EN()						(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()						(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()						(RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()							(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()							(RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()						(RCC->APB2ENR |= (1 << 5))

/*
 *	clock enable macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_EN()						(RCC->APB2ENR |= (1 << 14))


/*
 *	clock disable macros for GPIO peripherals
 */
#define GPIOA_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 7))

/*
 *	clock disable macros for I2C peripherals
 */
#define I2C1_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 23))

/*
 *	clock disable macros for SPI peripherals
 */
#define SPI1_PCLK_DI()						(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()						(RCC->APB2ENR &= ~(1 << 13))

/*
 *	clock disable macros for USART/UART peripherals
 */
#define USART1_PCLK_DI()						(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()							(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()							(RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI()						(RCC->APB2ENR &= ~(1 << 5))

/*
 *	clock disable macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_DI()						(RCC->APB2ENR &= ~(1 << 14))


/*
 *	GPIO peripherals reset macros
 */
#define GPIOA_REG_RESET()								do{ RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0);} while(0)
#define GPIOB_REG_RESET()								do{ RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1);} while(0)
#define GPIOC_REG_RESET()								do{ RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2);} while(0)
#define GPIOD_REG_RESET()								do{ RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3);} while(0)
#define GPIOE_REG_RESET()								do{ RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4);} while(0)
#define GPIOF_REG_RESET()								do{ RCC->AHB1RSTR |= (1 << 5); RCC->AHB1RSTR &= ~(1 << 5);} while(0)
#define GPIOG_REG_RESET()								do{ RCC->AHB1RSTR |= (1 << 6); RCC->AHB1RSTR &= ~(1 << 6);} while(0)
#define GPIOH_REG_RESET()								do{ RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7);} while(0)


#define GPIO_BASEADDR_TO_CODE(gpio_baseaddr)			(	(gpio_baseaddr == GPIOA)? 0:\
															(gpio_baseaddr == GPIOB)? 1:\
															(gpio_baseaddr == GPIOC)? 2:\
															(gpio_baseaddr == GPIOD)? 3:\
															(gpio_baseaddr == GPIOE)? 4:\
															(gpio_baseaddr == GPIOF)? 5:\
															(gpio_baseaddr == GPIOG)? 6:\
															(gpio_baseaddr == GPIOH)? 7:0	)


//EXTI IRQ numbers
#define IRQ_NO_EXTI0 							6
#define IRQ_NO_EXTI1 							7
#define IRQ_NO_EXTI2 							8
#define IRQ_NO_EXTI3 							9
#define IRQ_NO_EXTI4 							10
#define IRQ_NO_EXTI9_5 							23
#define IRQ_NO_EXTI15_10 						40

//macros for the all possible EXTI IRQ priority levels
#define NVIC_IRQ_PRI0 							0
#define NVIC_IRQ_PRI1 							1
#define NVIC_IRQ_PRI2 							2
#define NVIC_IRQ_PRI3 							3
#define NVIC_IRQ_PRI4 							4
#define NVIC_IRQ_PRI5 							5
#define NVIC_IRQ_PRI6 							6
#define NVIC_IRQ_PRI7 							7
#define NVIC_IRQ_PRI8 							8
#define NVIC_IRQ_PRI9 							9

// some generic macros
#define ENABLE 									1
#define DISABLE 								0
#define SET										ENABLE
#define RESET									DISABLE
#define GPIO_PIN_SET							SET
#define GPIO_PIN_RESET							RESET



#include "stm32f446_gpio_driver.h"
#include "stm32f446_spi_driver.h"

#endif /* INC_STM32F446_H_ */
