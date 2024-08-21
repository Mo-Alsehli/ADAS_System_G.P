/*
 * LCD.c
 *
 *  Created on: Oct 4, 2023
 *      Author: Mohamed Magdi
 */


#include "LCD.h"
#include "GPIO_Driver.h"



void fallingEdge(void){
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, EN, GPIO_PIN_HIGH);
	wait(1);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, EN, GPIO_PIN_LOW);
	wait(1);
}

void lcdGotoXY(uint8_t line, uint8_t col){
	if(line == 1){
		 sendCommand((uint8_t)LCD_BEGIN_AT_FIRST_ROW + col);
	}else if(line == 2){
		sendCommand((uint8_t)LCD_BEGIN_AT_SECOND_ROW + col);
	}
}


void sendChar(uint8_t data){
#if LCD_BIT_MODE == 8
	MCAL_GPIO_WritePort(LCD_PORT, data);
	// RS = 1, RW = 0, EN = FALLING EDGE;
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RS, GPIO_PIN_HIGH);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RW, GPIO_PIN_LOW);
	// Falling Edge
	fallingEdge();
	wait(1);
#endif

}

void sendStr(uint8_t *data){
	uint8_t count = 0;
	while(*data){
		count++;
		MCAL_GPIO_WritePort(LCD_PORT, *data);
		// RS = 1, RW = 0, EN = FALLING EDGE;
		MCAL_GPIO_WritePin(LCD_CTRL_PORT, RS, GPIO_PIN_HIGH);
		MCAL_GPIO_WritePin(LCD_CTRL_PORT, RW, GPIO_PIN_LOW);
		// Falling Edge
		fallingEdge();
		data++;
		wait(1);
		if(count == 16){
			lcdGotoXY(2, 0);
		}else if(count == 32){
			wait(1000);
			displayClear();
			lcdGotoXY(1, 0);
			count = 0;
		}

	}
}

void sendCommand(uint8_t command){
#if LCD_BIT_MODE == 8
	MCAL_GPIO_WritePort(LCD_PORT, command);
	// RS = 0, RW = 0, EN = FALLING EDGE;
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RS, GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RW, GPIO_PIN_LOW);
	// Falling Edge
	fallingEdge();
	wait(1);
#endif
}

void LCDInit(void){
#if LCD_BIT_MODE == 8
	sendCommand(0x02);
	wait(1);
	wait(50);
	sendCommand(FUN_SET_8_BIT);
	wait(1);
	sendCommand(LCD_DISP_ON_CURSOR_BLINK);
	wait(1);
	displayClear();
	sendCommand(ENTRY_MODE_SET);
	wait(1);

#endif
}


void displayClear(void){
	sendCommand(DISP_CLEAR);
}








