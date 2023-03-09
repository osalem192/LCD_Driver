/*
 * LCD.c
 *
 * Created: 3/5/2023 9:36:21 PM
 *  Author: osale
 */ 

#include <util/delay.h>
#include "STD_TYPE.h"
#include "LCD_Config.h"
#include "GPIO_DRIVER.h"

void LCD_Init(void)
{	
	Dio_Set_Pin_Dir(CTRL_Port, RS,1);
	Dio_Set_Pin_Dir(CTRL_Port, RW,1);
	Dio_Set_Pin_Dir(CTRL_Port, EN,1);
	
	_delay_ms(40);
	
	#if defined EIGHT_BIT_Mode
	Dio_Set_Port_Dir(Data_Port,1);
	Dio_Pin_Write(Data_Port,RW,0);
	LCD_SendCMD(EIGHT_BITS);
	_delay_ms(1);
	LCD_SendCMD(CURSOR_ON_DISPLAY_ON);
	_delay_ms(1);
	LCD_ClrDisplay();
	LCD_SendCMD(ENTRY_MODE);
	
	#elif defined FOUR_BIT_Mode
	LCD_SendCMD(RETURN_HOME);
	_delay_ms(10);
	LCD_SendCMD(Four_Bits);
	_delay_ms(1);
	LCD_SendCMD(CURSOR_ON_DISPLAY_ON);
	_delay_ms(1);
	LCD_ClrDisplay();
	LCD_SendCMD(ENTRY_MODE);
	Dio_Low_Nibble_Dir(Data_Port,1);
		
	#endif
	
}


void LCD_SendCMD(uint8 CMD)
{	
	Dio_Pin_Write(CTRL_Port, RS, 0);
	Dio_Pin_Write(Data_Port,RW,0);
	
	#if defined EIGHT_BIT_Mode
	Dio_Port_Write(Data_Port,CMD);		
	LCD_EN();
	_delay_ms(1);
	
	#elif defined FOUR_BIT_Mode
	
	uint8 y = CMD;	
	Dio_Low_Nibble_Write(Data_Port, CMD >> 4);
	LCD_EN();
	Dio_Low_Nibble_Write(Data_Port, CMD);
	LCD_EN();
	#endif
}

void LCD_SendChar(uint8 data)
{	
	Dio_Pin_Write(CTRL_Port,RS,1);
	Dio_Pin_Write(Data_Port,RW,0);
	
	#if defined EIGHT_BIT_Mode
	Dio_Port_Write(Data_Port, data);
	LCD_EN();
	
	#elif defined FOUR_BIT_Mode
	uint8 y = data;
	Dio_Low_Nibble_Write(Data_Port, data >> 4);
	LCD_EN();
	Dio_Low_Nibble_Write(Data_Port, data);
	LCD_EN();
	#endif
}

void LCD_SendString(uint8 * data)
{	
	while ((*data) != '\0')
	{
		LCD_SendChar(*data);
		data ++;
	}
}

void LCD_SendCustomChar()
{	uint8 i =0;
	LCD_SendCMD(0x40);
	uint8 arr[] = { 0x00, 0x07, 0x04, 0x04, 0x1F, 0x00, 0x00, 0x00,		// ??? ????? 
					0x00, 0x00, 0x0E, 0x0A, 0x1F, 0x00, 0x00, 0x00,		// ??? ????? 
					0x00, 0x02, 0x02, 0x02, 0x02, 0x04, 0x18, 0x00,		// ??? ????? 
					0x00, 0x00, 0x15, 0x15, 0x1F, 0x00, 0x00, 0x00,		// ??? ?????		  
					0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00,		// ??? ?????
				    0x04, 0x04, 0x04, 0x04, 0x1C, 0x00, 0x00, 0x00,		// ??? ????? 
					0x00, 0x00, 0x07, 0x05, 0x1F, 0x10, 0x10, 0x10,		// ??? ????? ?? ??? ??????
				  };
	for (i ; i < 56; i++)
	{
		LCD_SendChar(arr[i]);
	}
}

void LCD_ReadBusyFlag()
{
	Dio_Pin_Write(CTRL_Port,RW,1);
	Dio_Pin_Read(Data_Port,3);
	LCD_EN();
}

void LCD_ClrDisplay(void)
{
	LCD_SendCMD(0x01);
	_delay_ms(10);
}

void LCD_EN(void)
{
	Dio_Pin_Write(CTRL_Port, EN, 1);
	_delay_ms(3);
	Dio_Pin_Write(CTRL_Port, EN, 0);
}

void LCD_MoveCursor(uint8 coloumn, uint8 row)
{
	uint8 data;
	if (coloumn > 2 || coloumn < 1 || row > 16 || row <1) data = 0x080;
	if (coloumn == 1) data = 0x80 + row - 1;
	if (coloumn == 2) data = 0xC0 + row - 1;
	LCD_SendCMD(data);
}