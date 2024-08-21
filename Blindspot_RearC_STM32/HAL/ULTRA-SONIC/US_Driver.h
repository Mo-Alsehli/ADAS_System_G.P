/*
 * US_Driver.h
 *
 *  Created on: Mar 17, 2024
 *      Author: Mohamed Magdi
 */

#ifndef ULTRA_SONIC_US_DRIVER_H_
#define ULTRA_SONIC_US_DRIVER_H_

#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#include "EXTI_Driver.h"
#include "TIM.h"


typedef struct {
	// Specifies The GPIO pins to be configured for trigger.
	// This parameter Must be set as value of @ref GPIO_PINS_define @GPIO_Driver.h File.
	uint16_t trigPin;
	// Specifies the external interrupt gpio pin for echo.
	// This parmaeter must be set based on @ref EXTI_define @EXTI_Driver.h File.
	EXTI_GPIO_Mapping_t echoPin;
	// Specifies The PORT used for Trigger and Echo pin.
	// GPIOA, GPIOB
	GPIO_TYPE_DEF* port;
	// Set the C function which will be called once the Echo IRQ Happen.
	void (*P_IRQ_Callback)(void);

}US_TypeDef;


// APIs
void ultraSonicInit(US_TypeDef* us);
void triggerUltraSonic(US_TypeDef* us, uint32_t clk);







#endif /* ULTRA_SONIC_US_DRIVER_H_ */
