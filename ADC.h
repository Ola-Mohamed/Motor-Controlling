/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Description: Header file for ADC
 *
 * Author: Ola Mohamed Ahmed
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"


extern volatile uint8 g_adcResult;

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7
}ADC_channel;

typedef enum
{
	AREF,AVCC,INTERNAL
}ADC_reference;


typedef enum
{
	Polling,Interrupt
}ADC_mode;

typedef enum
{
	NO_prescaler,F_CPU_2,F_CPU_4,F_CPU_8_,F_CPU_16,F_CPU_32,F_CPU_64_,F_CPU_128
}ADC_prescaler;

typedef struct
{
	ADC_channel   channel;
	ADC_reference reference;
	ADC_mode      mode;
	ADC_prescaler Division;
}ADC_configType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */

void ADC_init(const ADC_configType * config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */

uint16 ADC_readChannel(const ADC_configType * config_Ptr);



#endif /* ADC_H_ */
