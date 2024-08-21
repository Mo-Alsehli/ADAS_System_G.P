/*
 * UART.c
 *
 *  Created on: Dec 15, 2023
 *      Author: Mohamed Magdi
 */

// ------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------

#include "UART.h"

// ------------------------------------------------------------------
// Generic Variables
// ------------------------------------------------------------------
UART_Config_t* UARTGlobalCfg[3];
uint32_t pclk, BRR;

// ------------------------------------------------------------------
// Generic Functions
// ------------------------------------------------------------------



// ------------------------------------------------------------------
// APIs
// ------------------------------------------------------------------

/**==================================================================
 * @Fn 			- MCAL_UART_Init.
 * @brief 		- Initilizes UART (Supported Feature of Async. only).
 * @param [in] 	- usartx: where x can be (1..3 depending on device used) to select the GPIO peripheral.
 * @param [in] 	- usartCfg: pointer to a UART_Config_t structure that
 * 				  contains the configuration information for the specified UART.
 * @param [out]	- none
 * @retval 		- none
 * Note 		- Support for now Asynchronous mode & clock 8 MHZ.
 */

void MCAL_UART_Init(UART_TYPE_DEF* uartx, UART_Config_t* uartCfg){

	// Enable Clock for given uart peripheral.
	if(uartx == UART1){
		UARTGlobalCfg[0] = uartCfg;
		RCC_UART1_CLk_EN();
	}
	else if(uartx == UART2){
		UARTGlobalCfg[1] = uartCfg;
		RCC_UART2_CLk_EN();
	}
	else if(uartx == UART3){
		UARTGlobalCfg[2] = uartCfg;
		RCC_UART3_CLk_EN();
	}

	// Enable UART Module
	uartx->CR1 |= 1 << 13;

	// Enable UART tx and rx
	uartx->CR1 |= uartCfg->Mode;

	// Payload width
	uartx->CR1 |= uartCfg->Payload;

	// Configuration of parity control bit fields.
	uartx->CR2 |= uartCfg->Parity;

	// configure number of stop bits
	uartx->CR2 |= uartCfg->StopBits;

	// uart Hardware Flow Control.
	uartx->CR3 |= uartCfg->HwFlowCtl;

	// Configuration of BRR.
	// PCLK1 for USART2, 3.
	// PCLK2 for USART1.

	if(uartx == UART1){
		pclk = MCAL_RCC_GET_PCLK2Freq();
	}else {
		pclk = MCAL_RCC_GET_PCLK1Freq();
	}

	BRR = UART_BRR_REG(pclk, uartCfg->BaudRate);
	uartx->BRR = BRR;

	// Enable / Disable Interrupt.
	if(uartCfg->IRQ_Enable != UART_IRQ_Eanble_NONE){
		uartx->CR1 |= (uartCfg->IRQ_Enable);
		// Enable NVIC for uartx IRQ.
		if(uartx == UART1){
			NVIC_IRQ37_UART1_Enable;
		}else if(uartx == UART2){
			NVIC_IRQ38_UART2_Enable;
		}else if(uartx == UART3){
			NVIC_IRQ39_UART3_Enable;
		}
	}
}


/**==================================================================
 * @Fn 			- MCAL_UART_DeInit.
 * @brief 		-  DeInitilizes UART (Supported Feature of Async. only).
 * @param [in] 	- usartx: where x can be (1..3 depending on device used) to select the GPIO peripheral.
 * @param [out]	- none
 * @retval 		- none
 * Note 		- Reset The Module By RCC.
 */

void MCAL_UART_DeInit (UART_TYPE_DEF* uartx){
	if(uartx == UART1){
		RCC_UART1_Reset();
		NVIC_IRQ37_UART1_Disable;
	}else if(uartx == UART2){
		RCC_UART2_Reset();
		NVIC_IRQ38_UART2_Disable;
	}else if(uartx == UART3){
		RCC_UART3_Reset();
		NVIC_IRQ39_UART3_Disable;
	}
}

/**==================================================================
 * @Fn 			- MCAL_UART_SendData.
 * @brief 		- Sends user data as 9 Bits or 8 Bits.
 * @param [in] 	- usartx: where x can be (1..3 depending on device used) to select the GPIO peripheral.
 * @param [in] 	- pTxBuffer: Data To Be Sent.
 * @param [in] 	- pollingEn: Enum to specify if polling mechanism is enabled.
 * @param [out]	- none
 * @retval 		- none
 * Note 		- none
 */

void MCAL_UART_SendData	(UART_TYPE_DEF* uartx, uint16_t* pTxBuffer, uint8_t len, enum Polling_Mechanism pollingEn){

	uint8_t *p8DataBits = (uint8_t*)pTxBuffer;

	// Wait until TXE flag is set in the SR.
	if (pollingEn == enable) {
		while (!(uartx->SR & 1 << 7));
	}

	// Check the usart word length item for 9 BIT or 8 BIT in a frame.
	uint8_t payloadLength = uartx == UART1 ? UARTGlobalCfg[0]->Payload : uartx == UART2 ? UARTGlobalCfg[1]->Payload : UARTGlobalCfg[2]->Payload;
	uint8_t parity = uartx == UART1 ? UARTGlobalCfg[0]->Parity : uartx == UART2 ? UARTGlobalCfg[1]->Parity : UARTGlobalCfg[2]->Parity;

	if (payloadLength == UART_PayloadLength_9B) {
		// Handle 9-bit data transmission (if supported)
	} else if (payloadLength == UART_PayloadLength_8B) {
		for (int i = 0; i < len; i++) {
			// Calculate parity bit if enabled
			uint8_t data = *p8DataBits;
			if (parity != UART_Parity_NONE) {
				// Implement parity bit calculation logic here based on parity configuration
			}

			uartx->DR = data;
			p8DataBits++;
		}
	}

}

/**==================================================================
 * @Fn 			- MCAL_UART_Wait_TC.
 * @brief 		- UART wait until Transimission is complete.
 * @param [in] 	- usartx: where x can be (1..3 depending on device used) to select the GPIO peripheral.
 * @param [out]	- none
 * @retval 		- none
 * Note 		- none
 */

void MCAL_UART_Wait_TC (UART_TYPE_DEF* uartx){
	// Wait till TC flag is set in the SR
	while(! (uartx->SR & 1 << 6));
}

/**==================================================================
 * @Fn 			- MCAL_UART_ReceiveData.
 * @brief 		- Sends user data as 9 Bits or 8 Bits.
 * @param [in] 	- usartx: where x can be (1..3 depending on device used) to select the GPIO peripheral.
 * @param [in] 	- pRxBuffer: Recieved Data.
 * @param [in] 	- pollingEn: Enum to specify if polling mechanism is enabled.
 * @param [out]	- none
 * @retval 		- none
 * Note 		- none
 */

void MCAL_UART_ReceiveData (UART_TYPE_DEF* uartx, uint16_t* pRxBuffer, enum Polling_Mechanism pollingEn){
	if(pollingEn == enable){
		while (!(uartx->SR & 1 << 5));
	}

	uint8_t payLoad = uartx == UART1 ? UARTGlobalCfg[0]->Payload : uartx == UART2 ? UARTGlobalCfg[1]->Payload : UARTGlobalCfg[2]->Payload;
	uint8_t parity = uartx == UART1 ? UARTGlobalCfg[0]->Parity : uartx == UART2 ? UARTGlobalCfg[1]->Parity : UARTGlobalCfg[2]->Parity;
	// Check if the word length is 9 Bit or 8 Bit.
	if(payLoad == UART_PayloadLength_9B){
		if(parity == UART_Parity_NONE){
			*((uint16_t*) pRxBuffer) = uartx->DR;
		}else{
			*((uint16_t*) pRxBuffer) = (uartx->DR & (uint8_t)0xFF);
		}
	}else if (payLoad == UART_PayloadLength_8B){
		if(parity == UART_Parity_NONE){
			*((uint16_t*) pRxBuffer) = uartx->DR;
		}else{
			*((uint16_t*) pRxBuffer) = (uartx->DR & (uint8_t)0x7F);
		}
	}
}

/**==================================================================
 * @Fn 			- MCAL_UART_GPIO_SetPins.
 * @brief 		- Sets the GPIO pins with its recommended specificiation for UART.
 * @param [in] 	- usartx: where x can be (1..3 depending on device used) to select the GPIO peripheral.
 * @param [out]	- none
 * @retval 		- none
 * Note 		- Those GPIO pins clock must be enabled after initialization.
 */

void MCAL_UART_GPIO_SetPins	(UART_TYPE_DEF* uartx){
	GPIO_PinConfig_t pinCfg;

	if(uartx == UART1){
		// PA9 TX
		// PA10 RX
		// PA11 CTS
		// PA12 RTS

		// PA9 TX
		pinCfg.GPIO_PinNumber = GPIO_PIN_9;
		pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		pinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinCfg);

		// PA10 RX
		pinCfg.GPIO_PinNumber = GPIO_PIN_10;
		pinCfg.GPIO_MODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pinCfg);

		if(UARTGlobalCfg[0]->HwFlowCtl == UART_HwFlowCtl_CTS || UARTGlobalCfg[0]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			// PA11 CTS
			pinCfg.GPIO_PinNumber = GPIO_PIN_11;
			pinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinCfg);
		}
		if(UARTGlobalCfg[0]->HwFlowCtl == UART_HwFlowCtl_RTS || UARTGlobalCfg[0]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			// PA12 RTS
			pinCfg.GPIO_PinNumber = GPIO_PIN_12;
			pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinCfg);
		}
	}else if(uartx == UART2){
		// PA2 TX
		// PA3 RX
		// PA0 CTS
		// PA1 RTS

		// PA2 TX
		pinCfg.GPIO_PinNumber = GPIO_PIN_2;
		pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		pinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinCfg);

		// PA3 RX
		pinCfg.GPIO_PinNumber = GPIO_PIN_3;
		pinCfg.GPIO_MODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pinCfg);

		if(UARTGlobalCfg[1]->HwFlowCtl == UART_HwFlowCtl_CTS || UARTGlobalCfg[1]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			// PA0 CTS
			pinCfg.GPIO_PinNumber = GPIO_PIN_0;
			pinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinCfg);
		}
		if(UARTGlobalCfg[1]->HwFlowCtl == UART_HwFlowCtl_RTS || UARTGlobalCfg[1]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			// PA1 RTS
			pinCfg.GPIO_PinNumber = GPIO_PIN_1;
			pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinCfg);
		}
	}else if(uartx == UART3){
		// PB10 TX
		// PB11 RX
		// PB13 CTS
		// PB14 RTS

		// PB10 TX
		pinCfg.GPIO_PinNumber = GPIO_PIN_10;
		pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		pinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinCfg);

		// PB11 RX
		pinCfg.GPIO_PinNumber = GPIO_PIN_11;
		pinCfg.GPIO_MODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOB, &pinCfg);

		if(UARTGlobalCfg[2]->HwFlowCtl == UART_HwFlowCtl_CTS || UARTGlobalCfg[2]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			// PB13 CTS
			pinCfg.GPIO_PinNumber = GPIO_PIN_13;
			pinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pinCfg);
		}
		if(UARTGlobalCfg[2]->HwFlowCtl == UART_HwFlowCtl_RTS || UARTGlobalCfg[2]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			// PA14 RTS
			pinCfg.GPIO_PinNumber = GPIO_PIN_14;
			pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinCfg);
		}
	}
}




// ISR()
void USART1_IRQHandler(){
	UARTGlobalCfg[0]->P_IRQ_Callback();
}

void USART2_IRQHandler(){
	UARTGlobalCfg[1]->P_IRQ_Callback();
}

void USART3_IRQHandler(){
	UARTGlobalCfg[2]->P_IRQ_Callback();
}





















