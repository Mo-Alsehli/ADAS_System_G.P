/*
 * BlindSpot.h
 *
 *  Created on: Mar 30, 2024
 *      Author: dell
 */

#ifndef BLINDSPOT_BLINDSPOT_H_
#define BLINDSPOT_BLINDSPOT_H_

#include "STM32F103x6.h"


typedef enum{
	BLINDSPOT_SAFE_STATE,
	BLINDSPOT_RIGHT_STATE,
	BLINDSPOT_LEFT_STATE,
	BLINDSPOT_RIGHT_LEFT_STATE,
}BlindSpotState;


BlindSpotState blindSpotWarning(uint32_t leftDistance, uint32_t rightDistance);



#endif /* BLINDSPOT_BLINDSPOT_H_ */
