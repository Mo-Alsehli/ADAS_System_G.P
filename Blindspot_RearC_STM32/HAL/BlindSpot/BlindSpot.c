/*
 * BlindSpot.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Mohamed Magdi
 */

#include "BlindSpot.h"
#include "UART.h"
#include "GPIO_Driver.h"
uint8_t ch1 = 'S';


BlindSpotState blindSpotWarning(uint32_t leftDistance, uint32_t rightDistance){
	if(leftDistance <= 100 && rightDistance <= 100){
		// uart send alert left and right blind spot detected.
		ch1 = 'D';
		MCAL_UART_SendData(UART2, (uint16_t*)&ch1,1, enable);
		return BLINDSPOT_RIGHT_LEFT_STATE;
	}else if(leftDistance <= 100){
		// uart send alert left blind spot detected.
		ch1 = 'L';
		MCAL_UART_SendData(UART2, (uint16_t*)&ch1,1, enable);
		return BLINDSPOT_LEFT_STATE;
	}else if(rightDistance <= 100){
		// uart send alert right blind spot detected.
		ch1 = 'R';
		MCAL_UART_SendData(UART2, (uint16_t*)&ch1,1, enable);
		return BLINDSPOT_RIGHT_STATE;
	}
	return BLINDSPOT_SAFE_STATE;
}



