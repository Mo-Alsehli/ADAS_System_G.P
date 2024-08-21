/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Magdi
 * @Date           : 3 MAR 2024
 ******************************************************************************
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "GPIO_Driver.h"
#include "EXTI_Driver.h"
#include "TIM.h"
#include "UART.h"
#include "RCC.h"
#include "LCD.h"
#include "stdio.h"
#include "US_Driver.h"
#include <RearCollision.h>
#include <stdio.h>
#include "PID.h"
#include "BlindSpot.h"
#include "string.h"

#define clk	8000000



GPIO_PinConfig_t gpioB_cfg;
GPIO_PinConfig_t gpioA_cfg;
EXTI_PinConfig_t exti_cfg;

// Global variables
uint8_t echoFlagLeft = 0;
uint32_t distanceTimeLeft = 0;
uint64_t distanceLeft = 0;

// Rear Collision Sensor Variables
uint8_t echoFlagRear = 0;
uint64_t distanceRear = 30;
uint64_t endTimeRear = 0, startTimeRear = 0;


// Global variables for sensor2 uses tim3 (Left Sensor)
uint8_t echoFlagRight = 0;
uint32_t distanceTimeRight = 0;
uint64_t distanceRight = 40;
uint64_t endTimeRight = 0, startTimeRight = 0;
uint64_t endTimeLeft = 0, startTimeLeft = 0;

// Rear-Collision Variables
uint32_t prevRearDistance = 400;
uint32_t currRearDistance = 400;
uint32_t currRearTime = 0;
uint32_t prevRearTime = 0;
float relativeSpeed = 0;
float timeDiff = 0;
char flag = 0;



char text[20];
uint8_t lcdFlag = 0;
uint64_t millisCount = 0;
uint8_t ch = 'M';
uint16_t rp;

void UARTSendCharCallBack(){
	//MCAL_UART_SendData(UART2, (uint8_t*)ch, (uint8_t)3, disable);
	//MCAL_UART_ReceiveData(UART2, &rp, enable);
}


void echoSensorRight(){
	if(echoFlagRight == 0){
		//timeCalc(TIM3, clk, TIM_START);
		startTimeRight = TIM1CalcMicros(clk);
		echoFlagRight = 1;
	}else{
		//distanceTimeRight = timeCalc(TIM3, clk, TIM_STOP);
		endTimeRight  = TIM1CalcMicros(clk);
		uint64_t diff = endTimeRight - startTimeRight;
		distanceRight = (((diff)*170) / 10000);
		echoFlagRight = 0;
	}
}

void echoSensorLeft(){
	if(echoFlagLeft == 0){
		//timeCalc(TIM4, clk, TIM_START);
		startTimeLeft = TIM1CalcMicros(clk);
		echoFlagLeft = 1;
	}else{
		//distanceTimeLeft = timeCalc(TIM4, clk, TIM_STOP);
		endTimeLeft = TIM1CalcMicros(clk);
		uint64_t diff = endTimeLeft - startTimeLeft;
		distanceLeft = (((diff)*170) / 10000);
		echoFlagLeft = 0;
	}
}


void echoSensorRear(){
	if(echoFlagRear == 0){
		startTimeRear = TIM1CalcMicros(clk);
		echoFlagRear = 1;
	}else{
		endTimeRear = TIM1CalcMicros(clk);
		uint64_t diff = endTimeRear - startTimeRear;
		distanceRear = (((diff)*170) / 10000);
		echoFlagRear = 0;
		if(distanceRear > 400){
			distanceRear = 0;
		}

	}
}


int main(void)
{
	RCC_GPIOB_CLk_EN();
	RCC_GPIOA_CLk_EN();
	RCC_AFIO_CLK_EN();
	TIM1CalcMicrosInit();

	// GPIO PIN Configuratoin
	GPIO_PinConfig_t pinCfg;

	pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pinCfg.GPIO_PinNumber = GPIO_PIN_6;
	pinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_PIN_7;
	MCAL_GPIO_Init(GPIOB, &pinCfg);
	pinCfg.GPIO_PinNumber = GPIO_PIN_8;
	MCAL_GPIO_Init(GPIOB, &pinCfg);


	// Ultra-sonci Sensor Configuration
	US_TypeDef usRight;
	usRight.trigPin = GPIO_PIN_7;
	usRight.echoPin = EXTI6_PA6;
	usRight.port = GPIOA;
	usRight.P_IRQ_Callback = echoSensorRight;
	ultraSonicInit(&usRight);

	US_TypeDef usLeft;
	usLeft.trigPin = GPIO_PIN_5;
	usLeft.echoPin = EXTI4_PA4;
	usLeft.port = GPIOA;
	usLeft.P_IRQ_Callback = echoSensorLeft;
	ultraSonicInit(&usLeft);

	US_TypeDef usRear;
	usRear.trigPin = GPIO_PIN_10;
	usRear.echoPin = EXTI15_PA15;
	usRear.port = GPIOA;
	usRear.P_IRQ_Callback = echoSensorRear;
	ultraSonicInit(&usRear);

	UART_Config_t uartCfg;
	uartCfg.BaudRate = UART_BaudRate_115200;
	uartCfg.IRQ_Enable = UART_IRQ_Eanble_NONE;
	uartCfg.HwFlowCtl = UART_HwFlowCtl_NONE;
	uartCfg.Parity = UART_Parity_NONE;
	uartCfg.Mode = UART_Mode_TX_RX;
	uartCfg.Payload = UART_PayloadLength_8B;
	uartCfg.StopBits = UART_StopBits_One;
	uartCfg.P_IRQ_Callback = NULL;

	MCAL_UART_Init(UART2, &uartCfg);
	MCAL_UART_GPIO_SetPins(UART2);

	while(1){
		triggerUltraSonic(&usRear, clk);
		triggerUltraSonic(&usLeft, clk);
		triggerUltraSonic(&usRight, clk);

		// Rear-Collision
		currRearTime = TIM1CalcMicros(clk);
		timeDiff = currRearTime - prevRearTime;
		if((timeDiff) >= 200000){
			relativeSpeed = getRelativeSpeed(prevRearDistance, distanceRear, timeDiff);
			//relativeSpeed /= 10.0;
			prevRearTime = currRearTime;
			prevRearDistance = distanceRear;
			timeDiff = 0;
		}

		// Rear-Collsion Send Warning
		if(rearCollisionWarning(relativeSpeed, distanceRear) == REAR_DANGER_DISTANCE_STATE){
			MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_HIGH);
		}else {
			MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_LOW);
		}

		// Blind Spot Warning
		switch(blindSpotWarning(distanceLeft, distanceRight)){
			case BLINDSPOT_LEFT_STATE:
				MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_HIGH);
				MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_LOW);

				break;
			case BLINDSPOT_RIGHT_STATE:
				MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_HIGH);
				MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_LOW);

				break;
			case BLINDSPOT_RIGHT_LEFT_STATE:
				MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_HIGH);
				MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_HIGH);
				break;
			default:
				MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_LOW);
				MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_LOW);
		}

		delay(25, U_ms, clk);
	}
}
