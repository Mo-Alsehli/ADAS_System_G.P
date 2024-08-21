/*
 * RCC.c
 *
 *  Created on: Dec 15, 2023
 *      Author: Mohamed Magdi
 */

#include "RCC.h"

//Bits 10:8  PPRE1: APB low-speed prescaler (APB1)
//Set and cleared by software to control the division factor of the APB low-speed clock
//(PCLK1).
//Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16

const uint8_t APBPreSCTable[8U] = {0, 0, 0, 0, 1, 2, 3, 4};

//Bits 7:4  HPRE: AHB prescaler
//Set and cleared by software to control the division factor of the AHB clock.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHBPreSCTable[17U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

uint32_t MCAL_RCC_GET_SYS_CLKFreq(void){
	switch(RCC->CFGR >> 2 & 0b11){
	case 0:
		return HSI_RC_CLK;
		break;
	case 1:
		// ToDo and you need to calculate it.
		return HSE_CLK;
		break;
	case 2:
		// ToDo and you need to calculate it.
		return 16000000;
		break;
	}

	return 0;
}
uint32_t MCAL_RCC_GET_HCLKFreq(void){
	return (MCAL_RCC_GET_SYS_CLKFreq() >> (AHBPreSCTable[RCC->CFGR >> 4 & 0xF]));
}
uint32_t MCAL_RCC_GET_PCLK1Freq(void){
	// Bits 10:8  PPRE1: APB low-speed prescaler (APB1)
	return (MCAL_RCC_GET_HCLKFreq() >> (APBPreSCTable[RCC->CFGR >> 8 & 0b111]));
}
uint32_t MCAL_RCC_GET_PCLK2Freq(void){
	// Bits 13:11  PPRE2: APB high-speed prescaler (APB2)
	return (MCAL_RCC_GET_HCLKFreq() >> (APBPreSCTable[RCC->CFGR >> 11 & 0b111]));
}


