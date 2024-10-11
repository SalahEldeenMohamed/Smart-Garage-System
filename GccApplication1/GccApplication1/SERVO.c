/*
 * SERVO.c
 *
 * Created: 12/4/2023 4:12:49 PM
 *  Author: Eng_A
 */ 
#include "SERVO.h"

void SERVO_INIT()
{
	
	TIMER2_CONF CONF = {compare_mode,N_128,OC2_SET} ;
		TIMER2_INIT(&CONF) ;
		BIT_SET(DDRD,7) ;
}
void SERVO_DEG(uint8 deg) 
{
	if ( deg == 0 )
	{
		TIMER2_SetCompare(250);
	}
	else if ( deg == 180 ) 
	{
		TIMER2_SetCompare(230);
	}
}