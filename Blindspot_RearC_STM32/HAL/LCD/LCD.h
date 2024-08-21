/*
 * LCD.h
 *
 *  Created on: Oct 4, 2023
 *      Author: Mohamed Magdi
 */

#ifndef LCD_H_
#define LCD_H_


#include "STM32F103x6.h"

#define LCD_BIT_MODE 8

#define LCD_PORT GPIOA
#define LCD_CTRL_PORT GPIOA

#define RS GPIO_PIN_8
#define RW GPIO_PIN_9
#define EN GPIO_PIN_10



#define FUN_SET_8_BIT					0X38
#define FUN_SET_4_BIT					0X28
#define DISP_ON_OFF_CTRL				0X0c
#define DISP_CLEAR						0X01
#define ENTRY_MODE_SET					0X06
#define LCD_MOVE_DISP_RIGHT				0x1C
#define LCD_MOVE_DISP_LEFT				0x18
#define LCD_MOVE_CURSOR_RIGHT			0x14
#define LCD_MOVE_CURSOR_LEFT			0x10
#define LCD_DISP_OFF					0x08
#define LCD_DISP_ON_CURSOR				0x0E
#define LCD_DISP_ON_CURSOR_BLINK		0x0F
#define LCD_DISP_ON_BLINK				0x0D
#define LCD_ENTRY_DEC					0x04
#define LCD_ENTRY_DEC_SHIFT				0x05
#define LCD_BEGIN_AT_FIRST_ROW			0x80
#define LCD_BEGIN_AT_SECOND_ROW			0xC0


void sendChar(uint8_t data);
void sendStr(uint8_t *data);
void sendCommand(uint8_t command);
void displayClear(void);
void LCDInit(void);

#endif



