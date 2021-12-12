 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.C
 *
 * Description: Source file for ADC
 *
 * Author: Ola Mohamed Ahmed
 *
 *******************************************************************************/

#include "ADC.h"

volatile uint8 g_adcResult = 0;


ISR(ADC_vect)
{
	g_adcResult = ADC;
}

/*Function responsible for initialize the ADC driver.
 * 1-ADMUX Register Configure
 * 2-ADCSRA Register Bits
 *
 */
void ADC_init(const ADC_configType * config_Ptr)
{
    ADMUX = ((config_Ptr->reference)<<5);
	SET_BIT(ADCSRA,ADEN);
	SET_BIT(ADCSRA,ADEN);
	ADCSRA |= ((config_Ptr->mode)<<ADIE);
	ADCSRA = (ADCSRA & 0xF8) | ((config_Ptr->Division) & 0x07);

}
/*Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 * 1-channel number must be from 0 --> 7, clear first 5 bits in the ADMUX, choose the correct channel
 * 2- start conversion write
 * 3-wait for conversion to complete if work polling
 * 4-clear ADIF
 *
 */


uint16 ADC_readChannel(const ADC_configType * config_Ptr){
	ADMUX = (ADMUX & 0xE0) | ((config_Ptr->channel) & 0x07);
	SET_BIT(ADCSRA,ADSC);
	if((config_Ptr->mode) == Polling)
	{
		while(BIT_IS_CLEAR(ADCSRA,ADIF));
		SET_BIT(ADCSRA,ADIF);
	}

	return ADC;

}



