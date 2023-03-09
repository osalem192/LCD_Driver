/*
 * LCD_2.c
 *
 * Created: 3/5/2023 9:34:28 PM
 * Author : osale
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"


int main(void)
{	
	LCD_Init();
	LCD_SendString("Omar");
	LCD_SendCustomChar();				// write ??? ???? 
	for (uint8 i =0; i < 8; i ++)
	{	
		LCD_MoveCursor(2, 15 - i);
		LCD_SendChar(i);
	}
	
    while (1) 
    {
		
    }
}

