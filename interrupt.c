/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: interrupt.c
 *
 * Description: Source file for interrupt
 *
 * Author: Ola Mohamed Ahmed
 *
 *******************************************************************************/
#include "interrupt.h"

static volatile void (*g_callBackPtr1)(void) = NULL_PTR;

ISR(INT1_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();
	}
}
/*Configure interrupt1 with raising edge*/
void INTERRUPT_init()
{

	CLEAR_BIT(DDRD,PD3);
	SET_BIT(GICR,INT1);
    SET_BIT(MCUCR,ISC10);
    SET_BIT(MCUCR,ISC11);
}


void INTERRUPT_callBack(void (*a_ptr)(void))
{
	g_callBackPtr1 = a_ptr;
}


