/*
 * Module:Test Timer0 using Call Back function
 * File Name: main.c
 *  Created on: Mar 19, 2023
 *  Author: Mohamed Wageh
 */

#include "timer0.h"

uint8 tick=0;
uint8 count=0;

void toggle(){
	tick++;
	if(tick==4){
		count++;
		tick=0;
		TOGGLE_BIT(PORTC,0);

	}
}




int main(void){

	/*set global interrupt*/
	SREG|=(1<<7);

	/*structure for timer0
	 * mode= overflow mode
	 * initial value= 6 to let timer0 count 250 counts
	 * prescaler=1024
	 * */
	TimerConfig Timer0Config={1,0,250,1024};


	/*pin0 in port c as output*/
	SET_BIT(DDRC,1);

	/*make it off at the beginning*/
	CLEAR_BIT(PORTC,0);

	/*call TIMER0_init to initialize timer0*/
	TIMER0_init(&Timer0Config);
//	ctc();
	/*pass toggle function to execute after timer finished*/
	TIMER0_setCallBack(toggle);


	while(1){
		if(count==5){
			TIMER0_deInit();
		}
	}

	return 0;
}
