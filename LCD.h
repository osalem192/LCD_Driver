/*
 * LCD.h
 *
 * Created: 3/5/2023 9:36:43 PM
 *  Author: osale
 */ 

#include "STD_TYPE.h"

#ifndef LCD_H_
#define LCD_H_

void LCD_Init();
void LCD_SendCMD(uint8 CMD);
void LCD_SendChar(uint8 data);
void LCD_SendString(uint8 * data);
void LCD_SendCustomChar();
void LCD_ReadBusyFlag();
void LCD_ClrDisplay();
void LCD_EN();
void LCD_MoveCursor(uint8 coloumn, uint8 row);



#endif /* LCD_H_ */