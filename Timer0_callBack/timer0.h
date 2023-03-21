/*
 * Mpdule: timer0
 * File Name: timer0.h
 * Description: header file for Atmega16 Timer0 driver
 * Created on: Mar 19, 2023
 * Author: Mohamed Wageh
 */

#ifndef TIMER0_H_
#define TIMER0_H_

/********************************************************
 * 					Common Header Files
 * ******************************************************/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************
 *                  Extern Global Varibles
 *******************************************************/

/******************************************************
 * 			Declaration for user defined types
 ******************************************************/
typedef struct{
	uint8 s_mode;
	uint8 s_initialValue;
	uint8 s_compareValue;
	uint16 s_prescaler;
}TimerConfig;

/*******************************************************
 * 					Function Prototypes
 *******************************************************/
void TIMER0_init(const TimerConfig * config_ptr);
void TIMER0_setCallBack(void(*PTR2FUNC)(void));
void TIMER0_deInit();

/******************************************************
 * 						Macros
 ******************************************************/

#endif /* TIMER0_H_ */
