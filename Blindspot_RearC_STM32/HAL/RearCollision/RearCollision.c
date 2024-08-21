/*
 * RearCollision.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Mohamed Magdi
 */

#include "RearCollision.h"
#include "UART.h"
uint8_t ch2 = 'S';


float getRelativeSpeed(uint32_t prevDistance, uint32_t currDistance, float timeDiff){
	float relativeSpeed = 0;
	if(prevDistance > currDistance){
		// Acceleration Case
		relativeSpeed = (prevDistance - currDistance) / ((timeDiff) / 1000000);
	}else{
		// Decelration.
//		relativeSpeed =  (currDistance - prevDistance) / ((timeDiff) / 1000000);
		relativeSpeed = 0;
	}
	if(relativeSpeed > 1000){
		relativeSpeed = 0;
	}
	return relativeSpeed;
}


RearCollisionState rearCollisionWarning(float relativeSpeed, uint32_t rearDistance){
	if(relativeSpeed >= 400 && rearDistance < 90){
		// send uart alert rear distance and speed limit exceeded.
		ch2 = 'R';
		MCAL_UART_SendData(UART2, (uint16_t*)&ch2,1, enable);
		return REAR_DANGER_SPEED_DISTANCE_STATE;
	}else if(rearDistance < 90){
		// send uart alert rear distance limit exceeded.
		ch2 = 'R';
		MCAL_UART_SendData(UART2, (uint16_t*)&ch2,1, enable);
		return REAR_DANGER_DISTANCE_STATE;
	}else if(relativeSpeed >= 400 ){
		// send uart alert relative speed limit exceeded.
		ch2 = 'R';
		MCAL_UART_SendData(UART2, (uint16_t*)&ch2,1, enable);
		return REAR_DANGER_SPEED_STATE;
	}

	return REAR_SAFE_STATE;
}

