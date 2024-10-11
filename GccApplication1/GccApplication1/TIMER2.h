/*
 * TIMER2.h
 *
 * Created: 11/29/2023 1:10:00 AM
 *  Author: Eng_A
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_
#include <avr/io.h>
#include  <avr/interrupt.h>
#include "BIT_MATH.h"
#include "Standard.h"

uint16 Time ;
static volatile void (*call_back_T2)(void)  = NULL_PTR ;
static volatile uint8 g_counter ;

#define NO_CLK   0x00
#define CPU_CLK  0x01
#define N_8      0x02
#define N_32     0x03
#define N_64     0x04
#define N_128    0x05
#define N_256    0x06
#define N_1024   0x07


#define compare_mode  0xc0
#define normal_mode   0x00

#define OC2_NORM  0x00
#define OC2_TGL   0x10
#define OC2_SET   0x30
#define OC2_CLR   0x20

typedef struct 
{
		uint8 mode ;
		uint8 OC2_STATE ;
		uint8 pre_scaler ;
	}TIMER2_CONF;





void TIMER2_INIT(const TIMER2_CONF *conf) ;
		  
void TIMER2_SetCounter(uint8 counter) ;
		  
void TIMER2_SetCompare(uint8 Compare) ;
		  
void TIMER2_CallBack(void(*ptr)(void));

void add_clks_2(void);

uint32 TIMER2_TIME(void);




#endif /* TIMER2_H_ */