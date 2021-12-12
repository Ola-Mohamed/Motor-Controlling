 /******************************************************************************
 *
 * Module: Controlling Motor
 *
 * File Name: Mini_Project2.c
 *
 * Description: Main File For Mini_Project2
 *
 * Author: Ola Mohamed Ahmed
 *
 *******************************************************************************/
#include "ADC.h"
#include "pwm.h"
#include "lcd.h"
#include "interrupt.h"


uint8 dir = 0;

	/* Function will be reverse dir  when rising edge come to INT1 pin
	 * >> it will change the direction of motor
	 */

void Reverse_Direction()
{
  if(dir == 0)
  {
	SET_BIT(PORTB,PB0);
	CLEAR_BIT(PORTB,PB1);
	dir = 1;
	}
 else if(dir == 1)
{
	 SET_BIT(PORTB,PB1);
	 CLEAR_BIT(PORTB,PB0);
	 dir = 0;
 }
}

int main(){

  /* Set 0,1 bits output for motor */
  	SET_BIT(DDRB,PB0);
  	SET_BIT(DDRB,PB1);

  	/* switch motor into clockwise */
  	SET_BIT(PORTB,PB1);
  	CLEAR_BIT(PORTB,PB0);

  	DDRB|= (1<<PB3); /* Make OC0 pin as output */

  	/* ADC config ->
	 * - choose channel 0
	 * - choose AREF in micro-controller
	 * - choose polling not interrupt
	 * - F_CPU / 8 = 1MHZ / 8 = 125KHZ (50 : 200 KHZ)
	 */
	ADC_configType ADC_config = {ADC0,AREF,Polling,F_CPU_8_};

	/* PWM config ->
		 * - choose PWM in Timer0
		 * - choose clear on compare match mode
		 * - choose F_CPU / 8
		 */
	PWM_configType PWM_config = {TIMER_0,CLEAR_OC0,F_CPU_8_};



  ADC_init(&ADC_config);
  LCD_init();
  PWM_init_T(&PWM_config);
  INTERRUPT_init();
  INTERRUPT_callBack(Reverse_Direction);

  /* Enable global interrupt >> sei(); */
  	SREG |= (1<<7);

  	LCD_displayString ("ADC Value = ");

	while(1){

		        g_adcResult = ADC_readChannel(&ADC_config);
				/* value of OCR1 = (adcValue * 256) / 1024 = adcValue /4 */
				g_OCR0 = g_adcResult /4 ;
				/* change duty cycle according to potentiometer value */
				PWM_changeDuty(&PWM_config,g_OCR0);
				/* display adcVaue on chosen place */
				LCD_goToRowColumn(0,12);
				LCD_intgerToString(g_adcResult);

	}
}


