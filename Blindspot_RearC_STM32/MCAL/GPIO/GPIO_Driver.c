/*
 * GPIO_Driver.c
 *	Auther: Mohamed Magdi
 *  Created on: Sep 23, 2023
 */

// ------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------

#include "GPIO_Driver.h"

int getCRLHPinPos(uint16_t pinNum){
	switch(pinNum){
	case (GPIO_PIN_0):
											return 0;
	break;
	case (GPIO_PIN_1):
											return 4;
	break;
	case (GPIO_PIN_2):
											return 8;
	break;
	case (GPIO_PIN_3):
											return 12;
	break;
	case (GPIO_PIN_4):
											return 16;
	break;
	case (GPIO_PIN_5):
											return 20;
	break;
	case (GPIO_PIN_6):
											return 24;
	break;
	case (GPIO_PIN_7):
											return 28;
	break;
	case (GPIO_PIN_8):
											return 0;
	break;
	case (GPIO_PIN_9):
											return 4;
	break;
	case (GPIO_PIN_10):
											return 8;
	break;
	case (GPIO_PIN_11):
											return 12;
	break;
	case (GPIO_PIN_12):
											return 16;
	break;
	case (GPIO_PIN_13):
											return 20;
	break;
	case (GPIO_PIN_14):
											return 24;
	break;
	case (GPIO_PIN_15):
											return 28;
	break;
	}

	return 0;
}

/**==================================================================
 * @Fn 			- MCAL_GPIO_Init.
 * @brief 		- Inits GPIOx PINy according to the specified parameters in the PinConfig.
 * @param [in] 	- gpiox: where x can be (A..E depending on device used) to select the GPIO peripheral.
 * @param [in] 	- pinConfig: pointer to a GPIO_PinConfig_t structure that
 * 				  contains the configuration information for the specified GPO PIN
 * @param [out]	- none
 * @retval 		- none
 * Note 		- STM32F103C6 MCU has GPIO A, B, C, D, E modules but LQFP48 package
 * 				  has only GPIO A, B, PART of C/D exported as external From the MCU.
 */

void MCAL_GPIO_Init(GPIO_TYPE_DEF* gpiox, GPIO_PinConfig_t* pinConfig){
	// Port configuration register low (GPIOx_CRL), Configures pins from 0 >>> 7.
	// Port configuration register low (GPIOx_CRH), Configures pins from 8 >>> 15.

	volatile uint32_t* configReg = NULL;
	uint8_t pin_CNF_MODE = 0;

	// Configure if We are in CRL or CRH.
	configReg = (pinConfig->GPIO_PinNumber > GPIO_PIN_7) ? (&gpiox->CRH) : (&gpiox->CRL);

	// Clear CNFy[1:0] MODEy[1:0];
	(*configReg) &= ~(0xf << getCRLHPinPos(pinConfig->GPIO_PinNumber));

	// If PIN Is OUPUT.
	if(pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP || pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD || pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP || pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD){

		pin_CNF_MODE = ((pinConfig->GPIO_MODE - 4) << 2) | (pinConfig->GPIO_OUTPUT_SPEED & 0x0f);
	}
	// If PIN Is INPUT.
	else {	// MODE = 00: Input mode (reset state).
		if(pinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO || pinConfig->GPIO_MODE == GPIO_MODE_ANALOG){
			pin_CNF_MODE |= ((pinConfig->GPIO_MODE << 2)) & 0x0f;

		} else if(pinConfig->GPIO_MODE == GPIO_MODE_INPUT_AF){
			pin_CNF_MODE |= ((GPIO_MODE_INPUT_FLO << 2)) & 0x0f;
		}else{
			pin_CNF_MODE |= ((GPIO_MODE_INPUT_PU << 2)) & 0x0f;

			// Table 20. Port bit configuration table PxODR configure if pull-up or down.
			if(pinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU){
				gpiox->ODR |= pinConfig->GPIO_PinNumber;
			}else if(pinConfig->GPIO_MODE == GPIO_MODE_INPUT_PD) {
				gpiox->ODR &= ~(pinConfig->GPIO_PinNumber);
			}
		}


	}
	*configReg |= (pin_CNF_MODE << getCRLHPinPos(pinConfig->GPIO_PinNumber));

}

/**==================================================================
 * @Fn 			- MCAL_GPIO_DeInit.
 * @brief 		- Resets All GPIOx registers.
 * @param [in] 	- gpiox: where x can be (A..E depending on device used) to select the GPIO peripheral.
 * @param [out]	- none
 * @retval 		- none
 * Note 		- none
 */

void MCAL_GPIO_DeInit(GPIO_TYPE_DEF* gpiox){
	// If there is no reset controller on the bus so we assign each reset value to its register.
	/*	gpiox->BRR  =  0x00000000		;
	gpiox->BSRR =  0x00000000		;
	gpiox->CRH  =  0x44444444		;
	gpiox->CRL  =  0x44444444		;
	gpiox->LCKR =  0x00000000		;
	gpiox->ODR  =  0x00000000		;	*/

	// resting the periopheral using RCC.
	if(gpiox == GPIOA){
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}else if(gpiox == GPIOB){
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}else if(gpiox == GPIOC){
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}else if(gpiox == GPIOD){
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}else if(gpiox == GPIOE){
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}
}

/**==================================================================
 * @Fn 			- MCAL_GPIO_ReadPin.
 * @brief 		- Reads a specific pin.
 * @param [in] 	- gpiox: where x can be (A..E depending on device used) to select the GPIO peripheral.
 * @param [in]	- pinNum: Set pin number according @ref GPIO_PINS_define
 * @retval 		- The input pin value (two values based on @ref GPIO_PIN_state).
 * Note 		- none
 */

uint8_t MCAL_GPIO_ReadPin(GPIO_TYPE_DEF* gpiox, uint16_t pinNum){
	if((gpiox->IDR & pinNum) != (uint32_t) GPIO_PIN_LOW){
		return (uint8_t) GPIO_PIN_HIGH;
	}else {
		return (uint8_t) GPIO_PIN_LOW;
	}
}

/**==================================================================
 * @Fn 			- MCAL_GPIO_ReadPort.
 * @brief 		- Reads a specific port.
 * @param [in] 	- gpiox: where x can be (A..E depending on device used) to select the GPIO peripheral.
 * @retval 		- The value of port.
 * Note 		- none
 */

uint16_t MCAL_GPIO_ReadPort(GPIO_TYPE_DEF* gpiox){
	return (uint16_t)(gpiox->IDR);
}

/**==================================================================
 * @Fn 			- MCAL_GPIO_WritePin.
 * @brief 		- write a specific pin.
 * @param [in] 	- gpiox: where x can be (A..E depending on device used) to select the GPIO peripheral.
 * @param [in]	- value: Set pin to a specific value.
 * @retval 		- none.
 * Note 		- none
 */

void MCAL_GPIO_WritePin(GPIO_TYPE_DEF* gpiox, uint16_t pinNum, uint8_t value){
	if(value == GPIO_PIN_HIGH){
		gpiox->ODR |= (uint32_t)pinNum;
		// OR
		// gpiox->BSRR = (uint32_t)pinNum;
	}else {
		gpiox->ODR &= (uint32_t)(~pinNum);
		// OR
		// gpiox->BRR = (uint32_t)pinNum;
	}
}

/**==================================================================
 * @Fn 			- MCAL_GPIO_WritePort.
 * @brief 		- Writes a specific port.
 * @param [in] 	- gpiox: where x can be (A..E depending on device used) to select the GPIO peripheral.
 * @retval 		- none.
 * Note 		- none
 */
void MCAL_GPIO_WritePort(GPIO_TYPE_DEF* gpiox, uint16_t value){
	gpiox->ODR = (uint32_t)value;
}

/**==================================================================
 * @Fn 			- MCAL_GPIO_TogglePin.
 * @brief 		- Toggles a specific pin.
 * @param [in] 	- gpiox: where x can be (A..E depending on device used) to select the GPIO peripheral.
 * @param [in]	- pinNum: Toggle pin number according @ref GPIO_PINS_define.
 * @retval 		- none.
 * Note 		- none.
 */

void MCAL_GPIO_TogglePin(GPIO_TYPE_DEF* gpiox, uint16_t pinNum){
	gpiox->ODR ^= pinNum;
}

/**==================================================================
 * @Fn 			- MCAL_GPIO_LockPin.
 * @brief 		- Locks a specific pin.
 * @param [in] 	- gpiox: where x can be (A..E depending on device used) to select the GPIO peripheral.
 * @param [in]	- pinNum: Locks pin number according @ref GPIO_PINS_define.
 * @retval 		- Ok if pin config is locked or error if pin not locked (Ok  & ERROR @ref GPIO_RETURN_LOCK).
 * Note 		- none.
 */

uint8_t MCAL_GPIO_LockPin(GPIO_TYPE_DEF* gpiox, uint16_t pinNum){
	volatile uint32_t tmp = 1 << 16;
	tmp |= pinNum;
	// Write 1
	gpiox->LCKR = tmp;
	// Write 0;
	gpiox->LCKR = pinNum;
	// read 0
	tmp = gpiox->LCKR;
	// read 1
	if((uint32_t)(gpiox->LCKR & 1 << 16)){
		return GPIO_RETURN_LOCK_OK;
	}else {
		return GPIO_RETURN_LOCK_ERROR;
	}
}

// Execution Time (seconds) = (time * 255 * 4) / F_CPU
// when time = 1, It takes 1 Melli-seconds.
void wait(uint32_t time)
{
	uint32_t i, j;
	for (i = 0; i < time; i++)
	{
		for (j = 0; j < 255; j++)
		;
	}
}






