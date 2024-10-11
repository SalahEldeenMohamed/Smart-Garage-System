/*
 * LCD_Lib.h
 *
 * Created: 11/12/2023 9:47:19 PM
 *  Author: dell
 */ 


#ifndef LCD_LIB_H_
#define LCD_LIB_H_


#define databus_direction DDRC
#define controlbus_direction DDRB
#define databus PORTC
#define controlbus PORTB

#define rs 0
#define rw 1
#define en 3

/* 16x2 LCD Specifications */

#define LCDMaxLines 2
#define LCDMaxChars 16
#define LineOne 0x80
#define LineTWo 0xc0
#define BlankSpace ' '

void LCD_Init();
void LCD_Clear();
void LCD_GoToLineOne();
void LCD_GoToLineTwo();
void LCD_GoTOXY(char row, char col);
void LCD_CmdWrite(char cmd);
void LCD_DataWrite(char dat);
void LCD_DisplayString(char *string_ptr);



#endif /* LCD_LIB_H_ */