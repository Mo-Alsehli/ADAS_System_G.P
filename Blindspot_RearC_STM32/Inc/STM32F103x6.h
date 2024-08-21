/*
 * STM32F103x6.h
 *
 *  Created on: Sep 23, 2023
 *      Author: Mohamed Magdi
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_


// <---------------------------------------------- DEVICE HEADER ------------------------------------------------>


//---------------------------------------------------
//Includes
//---------------------------------------------------

#include <stdlib.h>
#include <stdint.h>

//---------------------------------------------------
//Base addresses for memories
//---------------------------------------------------

#define FLASH_MEM_BASE					0x08000000UL
#define SYS_MEM_BASE 					0x1FFFF000UL
#define SRAM_BASE 						0x20000000UL

#define PERIPHERALS_BASE 				0x40000000UL
#define CORTEXM3_PERIPHERAL_BASE 		0xE0000000UL
// NVIC Base
#define NVIC_BASE						0xE000E100UL
#define NVIC_ISER0						*(volatile uint32_t*)(NVIC_BASE + 0x0)
#define NVIC_ISER1						*(volatile uint32_t*)(NVIC_BASE + 0x4)
#define NVIC_ISER2						*(volatile uint32_t*)(NVIC_BASE + 0x8)
#define NVIC_ICER0 					    *(volatile uint32_t*)(NVIC_BASE + 0x80)
#define NVIC_ICER1						*(volatile uint32_t*)(NVIC_BASE + 0x84)
#define NVIC_ICER2						*(volatile uint32_t*)(NVIC_BASE + 0x88)

//---------------------------------------------------
//Base addresses for Bus AHB Peripherals.
//---------------------------------------------------

#define RCC_BASE						0x40021000UL	// OR (PERIPHERALS_BASE + 0x00021000UL)

//---------------------------------------------------
//Base addresses for Bus APB2 Peripherals.
//---------------------------------------------------
// fully included in LQFP48 package
#define GPIOA_BASE						0x40010800UL
#define GPIOB_BASE						0x40010C00UL
// partially included in LQFP48 package
#define GPIOC_BASE						0x40011000UL
#define GPIOD_BASE						0x40011400UL
// Not included in LQFP48 package
#define GPIOE_BASE						0x40011800UL


// EXTI
#define EXTI_BASE						0x40010400UL

// AFIO
#define AFIO_BASE						0x40010000UL

// UART
#define UART1_BASE						0x40013800UL

// SPI (Serial Peripheral Interface).
#define SPI1_BASE						0x40013000UL

// TIMER 1
#define TIM1_BASE						0x40012C00UL


//---------------------------------------------------
//Base addresses for Bus APB1 Peripherals.
//---------------------------------------------------

// SPI (Serial Peripheral Interface).
#define SPI2_BASE						0x40003800UL

// UART
#define UART2_BASE						0x40004400UL
#define UART3_BASE						0x40014800UL

// TIM2, TIM3, TIM4
#define TIM2_BASE						0x40000000UL
#define TIM3_BASE						0x40000400UL
#define TIM4_BASE						0x40000800UL


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register:	GPIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

}GPIO_TYPE_DEF;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register:	RCC
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
}RCC_TYPE_DEF;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register:	EXTI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TYPE_DEF;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register:	AFIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	uint32_t 		  RESERVED0;
	volatile uint32_t MAPR2;
}AFIO_TYPE_DEF;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register:	UART
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}UART_TYPE_DEF;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register:	SPI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_TYPE_DEF;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register:	TIMx, TIM2,3,4
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR; // This Register is reserved in TIM2,3,4 but not inTIM1
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR; // This Register is reserved in TIM2,3,4 but not inTIM1
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}TIMx_TYPE_DEF;


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA			                ((GPIO_TYPE_DEF*) GPIOA_BASE)
#define GPIOB			                ((GPIO_TYPE_DEF*) GPIOB_BASE)
#define GPIOC			                ((GPIO_TYPE_DEF*) GPIOC_BASE)
#define GPIOD			                ((GPIO_TYPE_DEF*) GPIOD_BASE)
#define GPIOE			                ((GPIO_TYPE_DEF*) GPIOE_BASE)

#define RCC				                ((RCC_TYPE_DEF*)  RCC_BASE)

#define EXTI			                ((EXTI_TYPE_DEF*) EXTI_BASE)

#define AFIO			                ((AFIO_TYPE_DEF*) AFIO_BASE)

// UART
#define UART1			                ((UART_TYPE_DEF*) UART1_BASE)
#define UART2			                ((UART_TYPE_DEF*) UART2_BASE)
#define UART3			                ((UART_TYPE_DEF*) UART3_BASE)

// SPI
#define SPI1			                ((SPI_TYPE_DEF*) SPI1_BASE)
#define SPI2			                ((SPI_TYPE_DEF*) SPI2_BASE)

// TIMx
#define TIM1			                ((TIMx_TYPE_DEF*) TIM1_BASE)
#define TIM2			                ((TIMx_TYPE_DEF*) TIM2_BASE)
#define TIM3			                ((TIMx_TYPE_DEF*) TIM3_BASE)
#define TIM4			                ((TIMx_TYPE_DEF*) TIM4_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Clock Enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLk_EN()				(RCC->APB2ENR |= 1 << 2)
#define RCC_GPIOB_CLk_EN()				(RCC->APB2ENR |= 1 << 3)
#define RCC_GPIOC_CLk_EN()				(RCC->APB2ENR |= 1 << 4)
#define RCC_GPIOD_CLk_EN()				(RCC->APB2ENR |= 1 << 5)
#define RCC_GPIOE_CLk_EN()				(RCC->APB2ENR |= 1 << 6)

#define RCC_AFIO_CLK_EN()				(RCC->APB2ENR |= 1 << 0)

// UART
// Clock Enable UART
#define RCC_UART1_CLk_EN()				(RCC->APB2ENR |= 1 << 14)
#define RCC_UART2_CLk_EN()				(RCC->APB1ENR |= 1 << 17)
#define RCC_UART3_CLk_EN()				(RCC->APB1ENR |= 1 << 18)

// RCC Reset Mechanism
#define RCC_UART1_Reset()			    (RCC->APB2RSTR |= 1 << 14)
#define RCC_UART2_Reset()				(RCC->APB1RSTR |= 1 << 17)
#define RCC_UART3_Reset()				(RCC->APB1RSTR |= 1 << 18)

// TIMx
// Clock Enable TIMx
#define RCC_TIM1_CLk_EN()				(RCC->APB2ENR |= 1 << 11)
#define RCC_TIM2_CLk_EN()				(RCC->APB1ENR |= 1 << 0)
#define RCC_TIM3_CLk_EN()				(RCC->APB1ENR |= 1 << 1)
#define RCC_TIM4_CLk_EN()				(RCC->APB1ENR |= 1 << 2)

// Clock Reset TIMx
#define RCC_TIM1_CLk_Reset()				(RCC->APB2RSTR |= 1 << 11)
#define RCC_TIM2_CLk_Reset()				(RCC->APB1RSTR |= 1 << 0)
#define RCC_TIM3_CLk_Reset()				(RCC->APB1RSTR |= 1 << 1)
#define RCC_TIM4_CLk_Reset()				(RCC->APB1RSTR |= 1 << 2

// SPI
// Clock Enable
#define RCC_SPI1_CLK_EN()				(RCC->APB2ENR |= 1 << 12)
#define RCC_SPI2_CLK_EN()				(RCC->APB1ENR |= 1 << 14)
// Clock Reset
#define RCC_SPI1_CLK_DIS()				(RCC->APB2RSTR |= 1 << 12)
#define RCC_SPI2_CLK_DIS()				(RCC->APB1RSTR |= 1 << 14)
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// IVT:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// EXTI

#define EXTI0_IRQ						6
#define EXTI1_IRQ						7
#define EXTI2_IRQ						8
#define EXTI3_IRQ						9
#define EXTI4_IRQ						10
#define EXTI5_IRQ						23
#define EXTI6_IRQ						23
#define EXTI7_IRQ						23
#define EXTI8_IRQ						23
#define EXTI9_IRQ						23
#define EXTI10_IRQ						40
#define EXTI11_IRQ						40
#define EXTI12_IRQ						40
#define EXTI13_IRQ						40
#define EXTI14_IRQ						40
#define EXTI15_IRQ						40

// UART
#define UART1_IRQ						37
#define UART2_IRQ						38
#define UART3_IRQ						39

// SPI
#define SPI1_IRQ						35
#define SPI2_IRQ						36


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// NVIC IRQ Enable/Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// ENABLE
// ISER0 -> Sets from 0-31 Interrupts lines.
#define NVIC_IRQ6_EXTI0_Enable			(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Enable			(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable			(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable			(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable			(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable		(NVIC_ISER0 |= 1<<23)
// ISER1 -> Sets from 32-63 Interrupts and the base of us is 32.
// EXTI10 to 15 have line 40 so 40 - 32 = 8.
#define NVIC_IRQ40_EXTI10_15_Enable		(NVIC_ISER1 |= 1<<8)

// DISABLE
#define NVIC_IRQ6_EXTI0_Disable			(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Disable			(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Disable			(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Disable			(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable		(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable		(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable	(NVIC_ICER1 |= 1<<8)

// UART Interruptsd
// Enable
#define NVIC_IRQ38_UART2_Enable			(NVIC_ISER1 |= 1 << (UART2_IRQ - 32))
#define NVIC_IRQ37_UART1_Enable			(NVIC_ISER1 |= 1 << (UART1_IRQ - 32))
#define NVIC_IRQ39_UART3_Enable			(NVIC_ISER1 |= 1 << (UART3_IRQ - 32))
// Disable
#define NVIC_IRQ37_UART1_Disable		(NVIC_ICER1 |= 1 << (UART1_IRQ - 32))
#define NVIC_IRQ38_UART2_Disable		(NVIC_ICER1 |= 1 << (UART2_IRQ - 32))
#define NVIC_IRQ39_UART3_Disable		(NVIC_ICER1 |= 1 << (UART3_IRQ - 32))

// TIMx 2, 3, 4 Interrupt Mask Enable.
#define NVIC_IRQ25_TIM1_Enable			(NVIC_ISER0 |= 1 << 25)
#define NVIC_IRQ28_TIM2_Enable			(NVIC_ISER0 |= 1 << 28)
#define NVIC_IRQ29_TIM3_Enable			(NVIC_ISER0 |= 1 << 29)
#define NVIC_IRQ30_TIM4_Enable			(NVIC_ISER0 |= 1 << 30)
// TIMx 2, 3, 4 Interrupt Mask Disable.
#define NVIC_IRQ25_TIM1_Disable			(NVIC_ICER0 |= 1 << 25)
#define NVIC_IRQ28_TIM2_Disable			(NVIC_ICER0 |= 1 << 28)
#define NVIC_IRQ29_TIM3_Disable			(NVIC_ICER0 |= 1 << 29)
#define NVIC_IRQ30_TIM4_Disable			(NVIC_ICER0 |= 1 << 30)

// SPI Interrupt Mask Enable
#define NVIC_IRQ35_SPI1_Enable			(NVIC_ISER1 |= 1 << SPI1_IRQ - 32)
#define NVIC_IRQ36_SPI2_Enable			(NVIC_ISER1 |= 1 << SPI2_IRQ - 32)
// SPI Interrupt Mask Disable
#define NVIC_IRQ35_SPI1_Disable			(NVIC_ICER1 |= 1 << SPI1_IRQ - 32)
#define NVIC_IRQ36_SPI2_Disable			(NVIC_ICER1 |= 1 << SPI2_IRQ - 32)




#endif /* INC_STM32F103X6_H_ */
