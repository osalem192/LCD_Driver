/*
 * LCD_Config.h
 *
 * Created: 3/3/2023 3:20:55 PM
 *  Author: osale
 */ 



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	 Always Use Low Nibble	 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   configurable section   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// #define EIGHT_BIT_Mode
#define FOUR_BIT_Mode
#define Data_Port 'd'
#define CTRL_Port 'c'
#define RS 5
#define RW 6
#define EN 7

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   non-configurable section   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define EIGHT_BITS 0x38
#define Four_Bits 0x28
#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAY_ON 0x0e
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06



#endif /* LCD_CONFIG_H_ */