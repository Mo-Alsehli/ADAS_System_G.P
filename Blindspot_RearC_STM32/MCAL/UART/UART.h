/*
 * UART.h
 *
 *  Created on: Dec 15, 2023
 *      Author: dell
 */

#ifndef UART_UART_H_
#define UART_UART_H_

//------------------------------------------
// Includes
//------------------------------------------
#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#include "RCC.h"

//------------------------------------------
// User Type Definitions (Structures)
//------------------------------------------

typedef struct {
	// Specifies the mode TX, RX Or TX_RX
	// This parameter Must be set as value of @ref UART_Mode_define.
	uint8_t		Mode;
	// Specifies the Baud Rate
	// This parameter Must be set as value of @ref UART_BaudRate_define.
	uint32_t	BaudRate;
	// Specifies the Data Length
	// This parameter Must be set as value of @ref UART_PayloadLength_define.
	uint8_t	Payload;
	// Specifies the Parity
	// This parameter Must be set as value of @ref UART_Parity_define.
	uint8_t	Parity;
	// Specifies the Stop Bits.
	// This parameter Must be set as value of @ref UART_StopBits_define.
	uint8_t	StopBits;
	// Specifies the Hardware Flow Control.
	// This parameter Must be set as value of @ref UART_HwFlowCtl_define.
	uint8_t	HwFlowCtl;
	// Enable or Disable UART IRQ TX/RX
	// This parameter is set @ref UART_IRQ_Enable_define
	uint8_t IRQ_Enable;
	// Set the function() which will be called once the IRQ Happen.
	void(* P_IRQ_Callback)(void);
}UART_Config_t;

//------------------------------------------
// Macros Configuration References
//------------------------------------------

/*@ref UART_Mode_define
 */
#define UART_Mode_TX				(uint32_t)(1 << 3) // Bit 3  TE: Transmitter enable
#define UART_Mode_RX				(uint32_t)(1 << 2) // Bit 2  RE: Receiver enable
#define UART_Mode_TX_RX			(uint32_t)(1 << 3 | 1 << 2) // Transmitter Reciever enable

/*@ref UART_BaudRate_define
 */

#define UART_BaudRate_2400			2400
#define UART_BaudRate_9600 			9600
#define UART_BaudRate_19200			19200
#define UART_BaudRate_57600			57600
#define UART_BaudRate_115200		115200
#define UART_BaudRate_230400		230400
#define UART_BaudRate_460800		460800
#define UART_BaudRate_921600		921600
#define UART_BaudRate_2250000		2250000
#define UART_BaudRate_4500000		4500000

/* @ref UART_PayloadLength_define
 */
#define UART_PayloadLength_8B		(uint32_t)(0)
#define UART_PayloadLength_9B		(uint32_t)(1<<12)

/*@ref UART_Parity_define.
 */
#define UART_Parity_NONE			(uint32_t)(0)
#define UART_Parity_EVEN			(uint32_t)(1<<10)
#define UART_Parity_ODD				(uint32_t)(1<<10 | 1 << 9)

/*@ref UART_StopBits_define
 */
//Bits 13:12  STOP: STOP bits
//These bits are used for programming the stop bits.
//00: 1 Stop bit
//01: 0.5 Stop bit
//10: 2 Stop bits
//11: 1.5 Stop bit
//The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.

#define UART_StopBits_One			(uint32_t)(0)
#define UART_StopBits_Half			(uint32_t)(1 << 12)
#define UART_StopBits_Two			(uint32_t)(2 << 12)
#define UART_StopBits_OneHalf		(uint32_t)(3 << 12)

/* @ref UART_HwFlowCtl_define
 */

#define UART_HwFlowCtl_NONE			(uint32_t)(0)
#define UART_HwFlowCtl_RTS			((uint32_t)1<<8)
#define UART_HwFlowCtl_CTS			((uint32_t)1<<9)
#define UART_HwFlowCtl_RTS_CTS		((uint32_t) 1 << 8 | 1 << 9)

/*@ref UART_IRQ_Enable_define
 */

#define UART_IRQ_Eanble_NONE		(uint32_t)(0)
#define UART_IRQ_Eanble_TXE			(uint32_t)(1<<7)
#define UART_IRQ_Eanble_TC 			(uint32_t)(1<<6)
#define UART_IRQ_Eanble_RXNEIE		(uint32_t)(1<<5)
#define UART_IRQ_Eanble_PE		    (uint32_t)(1<<8)

enum Polling_Mechanism {
	enable,
	disable
};

//------------------------------------------
// Baudrate Calculation
//------------------------------------------
#define UARTDIV(_PCLK_, _BAUD_)					(uint32_t)(_PCLK_ / (16*_BAUD_))
#define UARTDIV_MUL100(_PCLK_, _BAUD_)			(uint32_t)((25 * _PCLK_) / (4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_, _BAUD_)			(uint32_t)(UARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)				(uint32_t)(UARTDIV(_PCLK_, _BAUD_))
#define Div_Fraction(baudrate,clock)           	(uint32_t)(((UARTDIV_MUL100(baudrate,clock)-100*UARTDIV(baudrate,clock))*16)/100)
#define UART_BRR_REG(baudrate,clock)      		((Mantissa(baudrate,clock)) <<4)|(Div_Fraction(baudrate,clock)&0xf)


//------------------------------------------
// APIs Supported By "MCAL UART DRIVER"
//------------------------------------------

void MCAL_UART_Init				(UART_TYPE_DEF* uartx, UART_Config_t* UARTCfg);
void MCAL_UART_DeInit			(UART_TYPE_DEF* uartx);
void MCAL_UART_GPIO_SetPins		(UART_TYPE_DEF* uartx);
void MCAL_UART_SendData			(UART_TYPE_DEF* uartx, uint16_t* pTxBuffer, uint8_t len, enum Polling_Mechanism pollingEn);
void MCAL_UART_ReceiveData         (UART_TYPE_DEF* uartx, uint16_t* pRxBuffer, enum Polling_Mechanism pollingEn);
void MCAL_UART_Wait_TC				(UART_TYPE_DEF* uartx);

//void MCAL_UART_LIN_Init				(UART_TYPE_DEF* UARTx);
//void MCAL_USART_DMA_Init 				(UART_TYPE_DEF* UARTx);
//void MCAL_USART_Init  				(UART_TYPE_DEF* UARTx);



#endif /* UART_UART_H_ */
