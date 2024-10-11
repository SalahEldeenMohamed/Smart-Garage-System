/*
 * try_1_code.c
 *
 * Created: 12/22/2023 6:34:25 PM
 *  Author: dell
 */ 

#define F_CPU 2000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "LCD_Lib.h"
#include "SERVO.h"

void IsEmpty_Message();
void NotEmpty_Message();
void PlacesEmpty_Message(unsigned int num);

unsigned int Number;


int main(void)
{
	LCD_Init();
	SERVO_INIT();
	DDRA=0xFF;
	DDRD=0x00;
	PORTD=0xFF;
	PORTA=0x00;
	DDRB &=~ (1<<2);
	DDRD |= (1<<7);

	// Configure external interrupt INT0
	GICR |= (1 << 6);      // Enable external interrupt INT0
	//MCUCR |= (1 << ISC01);    // Trigger on any  logical change for INT0 (you can change this based on your requirement)
	
	// Configure external interrupt INT1
	GICR |= (1 << 7);      // Enable external interrupt INT1
	//MCUCR |= (1 << ISC01);    // Trigger on any  logical change for INT1 (you can change this based on your requirement)
	
	// Configure external interrupt INT2
	GICR |= (1 << 5);      // Enable external interrupt INT2
	//MCUCR |= (1 << ISC01);    // Trigger on any  logical change for INT2 (you can change this based on your requirement)
	
	sei();
	while(1)
	{
		Number=0;
		if((PIND&(1<<0))==0)
		{
			Number++;
		}
		if((PIND&(1<<1))==0)
		{
			Number++;
		}
		if((PIND&(1<<4))==0)
		{
			Number++;
		}
		if((PIND&(1<<5))==0)
		{
			Number++;
		}
		if((PIND&(1<<6))==0)
		{
			Number++;
		}
		
		if(Number==5)
		{
			NotEmpty_Message();
			PORTA &=~(1<<0);
			PORTA |= (1<<1);
		}
		else if(Number==0)
		{
			IsEmpty_Message();
			PORTA &=~(1<<1);
			PORTA |= (1<<0);
		}
		else{
			PlacesEmpty_Message(Number);
			PORTA &=~(1<<1);
			PORTA |= (1<<0);
		}
	}
}


void IsEmpty_Message()
{
	LCD_CmdWrite(0xff);  //cursor on
	LCD_GoToLineOne();
	LCD_DisplayString("    Welcome!    ");
			
	LCD_GoToLineTwo();
			
	LCD_DisplayString(" Garage Is Empty");			
	LCD_CmdWrite(0x0C); //cursor off
	
	PORTB &=~ (1<<4) & (1<<5) & (1<<6) & (1<<7);
	
}

void PlacesEmpty_Message(unsigned int num)
{
	LCD_CmdWrite(0xff);  //cursor on
	LCD_GoToLineOne();
	LCD_DisplayString("    Welcome!    ");
	
	LCD_GoToLineTwo();
	
	/*switch (num)
	{
		case 1:
		LCD_DisplayString(" 4 Places Empty");
		LCD_CmdWrite(0x0C);
		break;
		case 2:
		LCD_DisplayString(" 3 Places Empty");
		LCD_CmdWrite(0x0C);
		break;
		case 3:
		LCD_DisplayString(" 2 Places Empty");
		LCD_CmdWrite(0x0C);
		break;
		default:
		LCD_DisplayString(" 1 Places Empty");
		LCD_CmdWrite(0x0C);
	}*/
	char str[16];
	sprintf(str, " %i Places Empty", 5-num);	
	LCD_DisplayString(&str);
	LCD_CmdWrite(0x0C);	
	
	PORTB |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
} 

void NotEmpty_Message()
{
	
	LCD_CmdWrite(0xff);  //cursor on
	LCD_GoToLineOne();
	LCD_DisplayString(" Garage Is Full");
	
	LCD_GoToLineTwo();
	
	LCD_DisplayString("               ");
	LCD_CmdWrite(0x0C); //cursor off	
	
	PORTB |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
}

ISR(INT0_vect)
{
		LCD_CmdWrite(0xff);  //cursor on
		LCD_GoToLineOne();
		LCD_DisplayString("  EMERGENCY!!!  ");
		
		LCD_GoToLineTwo();
		
		LCD_DisplayString(" Fire In Garage ");
		LCD_CmdWrite(0x0C); //cursor off
		
		SERVO_DEG(180);
		PORTA |=(1<<1);
		PORTA &=~(1<<0);
		int count=50;
		while (count)
		{
			PORTA |=(1<<2);
			_delay_ms(100);
			PORTA &=~(1<<2);
			_delay_ms(100);
			count--;
		}
		SERVO_DEG(0) ;
}

ISR(INT1_vect)
{
		if (Number!=5)
		{
			LCD_Clear();
			LCD_CmdWrite(0xff);  //cursor on
			LCD_GoToLineOne();
			LCD_DisplayString("    Welcome!    ");
			
			LCD_GoToLineTwo();
			
			LCD_DisplayString("Gate Is Opening.");
			LCD_CmdWrite(0x0C); //cursor off
			
			SERVO_DEG(180);
			_delay_ms(5000);
			SERVO_DEG(0) ;
			_delay_ms(5000);
		}	
}

ISR(INT2_vect)
{
	
		LCD_Clear();
		LCD_CmdWrite(0xff);  //cursor on
		LCD_GoToLineOne();
		LCD_DisplayString("   Good Bye!!   ");
		
		LCD_GoToLineTwo();
		
		LCD_DisplayString("Gate Is Opening.");
		LCD_CmdWrite(0x0C); //cursor off
		
		SERVO_DEG(180);
		_delay_ms(5000);
		SERVO_DEG(0) ;
		_delay_ms(5000);
	
}

