/*
 * RearCollsion.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Mohamed Magdi
 */

#ifndef REARCOLLISION_REARCOLLISION_H_
#define REARCOLLISION_REARCOLLISION_H_

#include "STM32F103x6.h"

typedef enum{
	REAR_SAFE_STATE,
	REAR_DANGER_SPEED_STATE,
	REAR_DANGER_DISTANCE_STATE,
	REAR_DANGER_SPEED_DISTANCE_STATE
}RearCollisionState;



float getRelativeSpeed(uint32_t prevDistance,uint32_t currDistance, float timeDiff);
RearCollisionState rearCollisionWarning(float relativeSpeed, uint32_t rearDistance);


#endif /* REARCOLLISION_REARCOLLISION_H_ */
