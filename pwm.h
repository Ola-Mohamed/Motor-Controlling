/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: pwm.h
 *
 * Description: Header file for the PWM Mode
 *
 * Author: Ola Mohamed Ahmed
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                        External Variables                                   *
 *******************************************************************************/
extern uint16 g_initialCount_T0;
extern uint8 g_OCR0;

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	TIMER_0,TIMER_1,TIMER_2
}PWM_timerType;

typedef enum
{
	NORMAL_OC0_DISCONNECTED,REVERSED,CLEAR_OC0,SET_OC0
}PWM_modeType;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CLOCK_FALLING,EXTERNAL_CLOCK_RISING
}PWM_ClockType;

typedef struct
{
	PWM_timerType whichTimer;
	PWM_modeType  mode;
	PWM_ClockType clock;
}PWM_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Function responsible for initialize the timer driver.*/

void PWM_init_T(const PWM_configType * config_Ptr);

/*Function responsible for change dutycycle of pwm.*/

void PWM_changeDuty(const PWM_configType * config_Ptr,uint8 a_duty);

#endif /* PWM_H_ */
