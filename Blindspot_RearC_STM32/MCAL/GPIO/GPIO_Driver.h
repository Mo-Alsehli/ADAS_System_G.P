/*
 * GPIO_Driver.h
 *
 *  Created on: Sep 23, 2023
 *      Author: Mohamed Magdi
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

//------------------------------------------
// Includes
//------------------------------------------

#include "STM32F103x6.h"

//------------------------------------------
// User Type Definitions (Structures)
//------------------------------------------

typedef struct {
	// Specifies The GPIO pins to be configured.
	// This parameter Must be set as value of @ref GPIO_PINS_define.
	uint16_t GPIO_PinNumber	;

	// Specifies The operating mode for the selected pin.
	// This parameter Must be set as value of @ref GPIO_MODE_define.
	uint8_t GPIO_MODE			;

	// Specifies The Speed for the output selected pin.
	// This parameter Must be set as value of @ref GPIO_SPEED_define.
	uint8_t GPIO_OUTPUT_SPEED	;

}GPIO_PinConfig_t;

//------------------------------------------
// Macros Configuration References
//------------------------------------------

/*@ref GPIO_PINS_define
 */
#define GPIO_PIN_0						((uint16_t)0x0001)	// Pin 0 selected
#define GPIO_PIN_1						((uint16_t)0x0002)	// Pin 1 selected
#define GPIO_PIN_2						((uint16_t)0x0004)	// Pin 2 selected
#define GPIO_PIN_3						((uint16_t)0x0008)	// Pin 3 selected
#define GPIO_PIN_4						((uint16_t)0x0010)	// Pin 4 selected
#define GPIO_PIN_5						((uint16_t)0x0020)	// Pin 5 selected
#define GPIO_PIN_6						((uint16_t)0x0040)	// Pin 6 selected
#define GPIO_PIN_7						((uint16_t)0x0080)	// Pin 7 selected
#define GPIO_PIN_8						((uint16_t)0x0100)	// Pin 8 selected
#define GPIO_PIN_9						((uint16_t)0x0200)	// Pin 9 selected
#define GPIO_PIN_10						((uint16_t)0x0400)	// Pin 10 selected
#define GPIO_PIN_11						((uint16_t)0x0800)	// Pin 11 selected
#define GPIO_PIN_12						((uint16_t)0x1000)	// Pin 12 selected
#define GPIO_PIN_13						((uint16_t)0x2000)	// Pin 13 selected
#define GPIO_PIN_14						((uint16_t)0x4000)	// Pin 14 selected
#define GPIO_PIN_15						((uint16_t)0x8000)	// Pin 15 selected
#define GPIO_PORT_HIGH					((uint16_t)0xFFFF)	// All Pins selected
#define GPIO_PORT_LOW					((uint16_t)0x0000)	// All Pins selected

#define GPIO_PIN_MASK					0x0000FFFFu

/*@ref GPIO_MODE_define
 */

#define GPIO_MODE_ANALOG				0x00000000u		// Analog Mode
#define GPIO_MODE_INPUT_FLO				0x00000001u		// Input flaoting Mode
#define GPIO_MODE_INPUT_PU				0x00000002u		// Input Pull-Up Mode
#define GPIO_MODE_INPUT_PD				0x00000003u		// Input Pull-Down Mode
#define GPIO_MODE_OUTPUT_PP				0x00000004u		// Output Push-Pull Mode
#define GPIO_MODE_OUTPUT_OD				0x00000005u		// Output open-drain Mode
#define GPIO_MODE_OUTPUT_AF_PP			0x00000006u		// Output Alternative Function push-pull Mode
#define GPIO_MODE_OUTPUT_AF_OD			0x00000007u		// Output Alternative function open-drain Mode
#define GPIO_MODE_INPUT_AF				0x00000008u		// Input Alternative function Mode

/*@ref GPIO_SPEED_define
 */

#define GPIO_SPEED_10M					0x00000001u		// OUTPUT mode, max speed 10MHZ
#define GPIO_SPEED_2M					0x00000002u		// OUTPUT mode, max speed 2MHZ
#define GPIO_SPEED_50M					0x00000003u		// OUTPUT mode, max  speed 50MHZ

/*@ref GPIO_PIN_state
 */

#define GPIO_PIN_HIGH 					1
#define GPIO_PIN_LOW  					0

/*@refGPIO_RETURN_LOCK
 */

#define GPIO_RETURN_LOCK_OK				1
#define GPIO_RETURN_LOCK_ERROR			0


//------------------------------------------
// APIs Supported By "MCAL GPIO DRIVER"
//------------------------------------------

void MCAL_GPIO_Init(GPIO_TYPE_DEF* gpiox, GPIO_PinConfig_t* pinConfig);
void MCAL_GPIO_DeInit(GPIO_TYPE_DEF* gpiox);
uint8_t MCAL_GPIO_ReadPin(GPIO_TYPE_DEF* gpiox, uint16_t pinNum);
uint16_t MCAL_GPIO_ReadPort(GPIO_TYPE_DEF* gpiox);
void MCAL_GPIO_WritePin(GPIO_TYPE_DEF* gpiox, uint16_t pinNum, uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TYPE_DEF* gpiox, uint16_t value);
void MCAL_GPIO_TogglePin(GPIO_TYPE_DEF* gpiox, uint16_t pinNum);
uint8_t MCAL_GPIO_LocksPin(GPIO_TYPE_DEF* gpiox, uint16_t pinNum);
void wait(uint32_t time);

#endif /* GPIO_DRIVER_H_ */
