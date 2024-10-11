/*
 * TIMER2.c
 *
 * Created: 11/29/2023 1:09:12 AM
 *  Author: Eng_A
 */ 

#include "TIMER2.h"
void TIMER2_INIT(const TIMER2_CONF *conf)
{
	sei() ;                      /* ENABLE GENERAL INTERRUPT */
	TCNT2  =   0 ;                  /* SET COUNTER TO START FROM 0 */
	TCCR2  |=  conf->mode  ;        /* SET MODE OF COUNTER */
	TCCR2  |=  conf->OC2_STATE  ;   /* SET STATE OF OC0 PIN TO TGL OR SET OR CLEAR WHEN INTERRUPT HAPPEN */
	TCCR2  |=  conf->pre_scaler ;   /* SET PRESCALER */
	switch (conf->mode)             /* Switch for the mode to select interrupt */
	{ 
		case compare_mode :
		{
			BIT_SET(PORTA,2);
			BIT_SET(TIMSK,OCIE2) ;     /* set interrupt enable for compare mode */
			BIT_CLR(TIMSK,TOIE2) ;     /* clear interrupt enable for ov mode */
		}
		break ;
		case normal_mode :
		{
			
			BIT_SET(TIMSK,TOIE2) ;		  /* set interrupt enable for v mode */
			BIT_CLR(TIMSK,OCIE2) ;		  /* clear interrupt enable for compare mode */
		}
		break ;
	}
	
}

void TIMER2_SetCounter(uint8 counter)            /* set value at TCNT0 TO START COUNT FROM */
{
	TCNT2 = counter ;
	//g_counter = counter ;
}

void TIMER2_SetCompare(uint8 Compare) 		    /* set value at OCR0 TO MAKE COMPARE MATCH AT  */
{
	OCR2 = Compare ;
}

void TIMER2_CallBack(void(*ptr)(void))        /* CALL BACK FUNCTION TO SELECT FUNCTION IN ISR */
{
	call_back_T2 = ptr ;
}
uint32 TIMER2_TIME(void)                       /* FUNCTIONTO CALC TIME IN MSEC */
{
	static bool flag = 0 ;
	TIMER2_CONF t = {compare_mode,OC2_TGL,N_64} ;
	
	if ( flag == 0 )
	{
		TIMER2_CallBack(&add_clks_2);
		TIMER2_SetCompare(250) ;
		TIMER2_SetCounter(0);
		TIMER2_INIT(&t);
		flag = 1 ;
	}
	
	return Time ;
	
}
void add_clks_2(void)
{
	Time++;
}
ISR(TIMER2_OVF_vect)
{
	if (call_back_T2 != NULL_PTR)
	{
		call_back_T2();
	}
}
ISR(TIMER2_COMP_vect)
{
	if (call_back_T2 != NULL_PTR)
	{
		call_back_T2();
	}
}
