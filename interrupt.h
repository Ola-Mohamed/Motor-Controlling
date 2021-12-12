/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: interrupt.h
 *
 * Description: Header file for interrupt
 *
 *
 *******************************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void INTERRUPT_init();
void INTERRUPT_callBack(void (*a_ptr)(void));

#endif /* INTERRUPT_H_ */
