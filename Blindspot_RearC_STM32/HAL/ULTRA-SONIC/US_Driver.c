/*
 * US_Driver.c
 *
 *  Created on: Mar 17, 2024
 *      Author: Mohamed Magdi
 */

#include "US_Driver.h"


void ultraSonicInit(US_TypeDef* us){
	// configure trigger pin
	GPIO_PinConfig_t gpio_cfg;
	gpio_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	gpio_cfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_2M;
	gpio_cfg.GPIO_PinNumber = us->trigPin;
	MCAL_GPIO_Init(us->port, &gpio_cfg);

	// Configure External Interrupt for Echo pin
	EXTI_PinConfig_t exti_cfg;
	exti_cfg.EXTI_PIN = us->echoPin;
	exti_cfg.Trigger_Case = EXTI_Trigger_RisingAndFalling;
	exti_cfg.IRQ_EN = EXTI_IRQ_Enable;
	exti_cfg.P_IRQ_Callback = us->P_IRQ_Callback;
	MCAL_EXTI_GPIO_Init(&exti_cfg);
}


void triggerUltraSonic(US_TypeDef* us, uint32_t clk){
	MCAL_GPIO_WritePin(us->port, us->trigPin, GPIO_PIN_HIGH);
	delay(10, U_ms, clk);
	MCAL_GPIO_WritePin(us->port, us->trigPin, GPIO_PIN_LOW);
}


