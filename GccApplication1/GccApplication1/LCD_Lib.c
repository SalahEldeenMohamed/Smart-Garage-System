/*
 * LCD_Lib.c
 *
 * Created: 11/12/2023 9:47:35 PM
 *  Author: dell
 */ 

#include "LCD_Lib.h"
#include <avr/io.h>
#include <util/delay.h>


void LCD_Init()
{
	databus_direction=0xFF; //output
	controlbus_direction=0xFF; //output
	LCD_CmdWrite(0x38); // declare 2 lines lcd with 5*7 character matrix
	LCD_CmdWrite(0x0E); //to power on display and show cursor
	LCD_CmdWrite(0x01); //clear display 
}

void LCD_CmdWrite(char cmd)
{
	databus=cmd;
	controlbus &=~(1<<rs); //store in the data bus
	controlbus &=~(1<<rw); //enable write
	controlbus |=(1<<en); //ask the lcd to start executing
	_delay_ms(1);
	controlbus &=~(1<<en);
	_delay_ms(1); 
}

void LCD_DataWrite(char dat)
{
	databus=dat; //put char on databus
	controlbus |=(1<<rs); //store in the data register
	controlbus &=~(1<<rw); //enable write
	controlbus |=(1<<en); //ask the lcd to start executing
	_delay_ms(1);
	controlbus &=~(1<<en);
	_delay_ms(1);
	
}

void LCD_DisplayString(char *string_ptr)
{
	for(int i=0; i<16; i++)
	{
		LCD_DataWrite(string_ptr[i]);
	}
}

void LCD_Clear()
{
	LCD_CmdWrite(0x01);
}

void LCD_GoToLineOne()
{
	LCD_CmdWrite(0x80);	//move cursor to the begining of the line 
}

void LCD_GoToLineTwo()
{
	LCD_CmdWrite(0xC0);		
}

