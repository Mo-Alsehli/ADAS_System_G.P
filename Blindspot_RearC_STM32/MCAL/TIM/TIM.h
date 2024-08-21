/*
 * TIM.h
 *
 *  Created on: Mar 2, 2024
 *      Author: Mohamed Magdi
 */

#ifndef TIM_TIM_H_
#define TIM_TIM_H_

#include "STM32F103x6.h"
#include "GPIO_Driver.h"



// PWM
#define CH_1		1
#define CH_2		2
#define CH_3		3
#define CH_4		4

// Delay
#define U_ms		0 // Time In Milli-Seconds
#define U_us		1 // Time In Micro-Seconds

// Timer State.
#define TIM_START	1
#define TIM_STOP	0

// Register Bits
#define CEN			0	 // Counter Enable Pin.
#define URS			2   // Update request Source
#define UIE			0  //  Update interrupt enable


// APIs

void delay( uint16_t time, uint8_t unit, uint32_t clk);
uint32_t timeCalc(TIMx_TYPE_DEF* timx, uint32_t clk, uint8_t timerState);
void TIM1CalcMicrosInit(void);
uint64_t TIM1CalcMicros(uint32_t clk);



#endif /* TIM_TIM_H_ */
