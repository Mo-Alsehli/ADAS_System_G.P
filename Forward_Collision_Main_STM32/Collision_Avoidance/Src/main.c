/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "Stm32_F103C6_TIMERS_driver.h"
#include "Stm32_F103C6_UART_driver.h"
#include "Stm32_F103X6.h"
#include "Ultrasonic_Sensor.h"
#include "Collision_Avoidance.h"

uint16_t distance ;
uint32_t Vrel  , Vf , VAct ;

void Clock_init()
{
	// UART Enable
	RCC_USART1_CLK_EN();
	RCC_USART2_CLK_EN();

	// GPIO Enable
	RCC_GPIOC_CLK_EN();
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

	// TIMER Enable
	RCC_TIMER2_CLK_EN();
	RCC_TIMER3_CLK_EN();
	RCC_TIMER4_CLK_EN();

	// AFIO Enable
	RCC_AFIO_CLK_EN();


}


int main(void)
{
	Clock_init();
	HAL_US_Init(UART_With_Microcontroller , USART1 , TIMER3);
	APP_FCA_Init(USART2);

    /* Loop forever */
	while(1)
	{
		APP_FCA_Detecte_Collision_Status();
	}
}
