 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM Mode
 *
 * Author: Ola Mohamed Ahmed
 *
 *******************************************************************************/


#include "pwm.h"
uint16 g_initialCount_T0;
uint8 g_OCR0;


/*Function responsible for initialize the timer driver with  Pwm mode
		  Prescaler = F_CPU/64 */
 void PWM_init_T(const PWM_configType * config_Ptr){


	 if((config_Ptr->whichTimer) == TIMER_0)
	 	{
	 		SET_BIT(DDRB,PB3);
	 		TCNT0 = g_initialCount_T0;
	 		OCR0  = g_OCR0;
	 		SET_BIT(TCCR0,WGM01);
	 		SET_BIT(TCCR0,WGM00);
	 		TCCR0 = (TCCR0 & 0xCF) | ((config_Ptr->mode)<<4);
	 		TCCR0 = (TCCR0 & 0xF8) | (config_Ptr->clock);
	 	}
	 else if((config_Ptr->whichTimer) == TIMER_1)
	 	{
	 	}
	 	else if((config_Ptr->whichTimer) == TIMER_2)
	 	{

	 	}
	 }


/*this Function responsible for change duty cycle according to potenthimeter value */


void PWM_changeDuty(const PWM_configType * config_Ptr, uint8 a_duty)
{

	if((config_Ptr->whichTimer) ==TIMER_0)
		{
			OCR0 = a_duty;
		}
		else if((config_Ptr->whichTimer) ==TIMER_1)
		{

		}
		else if((config_Ptr->whichTimer) ==TIMER_2)
		{

		}

}
