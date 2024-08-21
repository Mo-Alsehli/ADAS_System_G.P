/*
 * RCC.h
 *
 *  Created on: Dec 15, 2023
 *      Author: Mohamed Magdi
 */

#ifndef RCC_RCC_H_
#define RCC_RCC_H_
//------------------------------------------
// Includes
//------------------------------------------
#include "STM32F103x6.h"
#include "GPIO_Driver.h"

// Clock Frequencies.
// Internal Clock.
#define HSI_RC_CLK						(uint32_t)8000000;
// External Clock.
#define HSE_CLK							(uint32_t)1600000;

uint32_t MCAL_RCC_GET_SYS_CLKFreq(void);
uint32_t MCAL_RCC_GET_HCLKFreq(void);
uint32_t MCAL_RCC_GET_PCLK1Freq(void);
uint32_t MCAL_RCC_GET_PCLK2Freq(void);



#endif /* RCC_RCC_H_ */
