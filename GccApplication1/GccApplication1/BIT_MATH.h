/*
@Author : Abdullah waheed
@brief  : BIT_MATH.H
@date   : 1/11/2023
@IEEE TEAM
*/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


/******************** BIT MATH macros ********************/
#define BIT_SET(PORT,PIN) (PORT |= (1<<PIN))
#define BIT_CLR(PORT,PIN) (PORT &=~(1<<PIN))
#define BIT_TGL(PORT,PIN) (PORT ^= (1<<PIN))
#define BIT_GET(PORT,PIN) (1 & (PORT >> PIN))
#define PORT_SET(PORT)    PORT = 0XFF
#define PORT_CLR(PORT)    PORT = 0 
/******************** BIT MATH macros ********************/



#endif /* BIT_MATH_H_ */