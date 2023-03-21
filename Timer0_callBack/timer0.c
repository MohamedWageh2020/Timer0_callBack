/*
 * Module: timer0
 * File Name: timer0.c
 * Description: source file for Atmega16 Timer0 Driver
 * Created on: Mar 19, 2023
 * Author: Mohamed Wageh
 */

#include "timer0.h"

/************************************************
 *			Global Variables
 ************************************************/

/* global pointer to function to hold the address of
 * the function that will be called after timer finished
 * static because do not let any module use this pointer except this module
 * volatile because it will change in ISR
 * */
static volatile void (*g_TIMER0_Call_Back_Ptr)(void) ;

/************************************************
 * 			Function Definitions
 ************************************************/

/* Description:
 * 			  this function responsible about initialization of timer0
 * 			  with mode = over flow
 * 			  prescaler =
 * */
TIMER0_init(const TimerConfig *config_ptr){

	switch(config_ptr->s_prescaler){

	case 1:
			/*choose prescaler 1 "No prescaling" */
			SET_BIT(TCCR0,CS00);
			CLEAR_BIT(TCCR0,CS01);
			CLEAR_BIT(TCCR0,CS02);
			break;
	case 8:
			/*choose prescaler 8 */
			CLEAR_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLEAR_BIT(TCCR0,CS02);
			break;
	case 64:
			/*choose prescaler 64 */
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLEAR_BIT(TCCR0,CS02);
			break;
	case 256:
			/*choose prescaler 256 */
			CLEAR_BIT(TCCR0,CS00);
			CLEAR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
	case 1024:
			/*choose prescaler 1024 */
			SET_BIT(TCCR0,CS00);
			CLEAR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
	}

	/*switch case to confige the mode */
	switch(config_ptr->s_mode){

	case 0:	/*first case for normal mode "overflow mode*/
			/* set to one to choose non PWM mode */
			SET_BIT(TCCR0,FOC0);

			/*choose Normal mode */
			CLEAR_BIT(TCCR0,WGM00);
			CLEAR_BIT(TCCR0,WGM01);

			/*set the initial value*/
			 TCNT0=config_ptr->s_initialValue;

			 /*enable interrupt to overflow mode */
			 SET_BIT(TIMSK,TOIE0);
			 break;
	case 1:
		/*code of CTC mode*/
		/* set to one to choose non PWM mode */
		SET_BIT(TCCR0,FOC0);

		/*choose CTC mode */
		CLEAR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);

		/*set the initial value*/
		TCNT0=config_ptr->s_initialValue;

		/* set compare value*/
		OCR0=config_ptr->s_compareValue;

		/*enable interrupt to CTC mode */
		SET_BIT(TIMSK,OCIE0);
		break;
	}



}
/* Description:
 * 			  this function responsible to hold the address of the function
 * 			  to be called after timer finished count
 * */
TIMER0_setCallBack(void(*PTR2FUNC)(void)){
	g_TIMER0_Call_Back_Ptr =PTR2FUNC;
}

/* Description:
 * 			  this function responsible to de initialization timer0
 * */

void TIMER0_deInit(){
		/*set the initial value to zero*/
		TCNT0=0;
		/*cut off clock to the timer */
		CLEAR_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
}


/************************************************
 * 				ISR
 ***********************************************/
ISR(TIMER0_OVF_vect){
	(*g_TIMER0_Call_Back_Ptr)();
}

ISR(TIMER0_COMP_vect){
	(*g_TIMER0_Call_Back_Ptr)();
}
/***********************************************
 * 	Function Prototypes for Private Functions
 ***********************************************/
