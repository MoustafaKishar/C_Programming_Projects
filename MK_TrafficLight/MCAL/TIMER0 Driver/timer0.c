/*
 * timer0.c
 *
 * Created: 9/29/2022 4:22:39 AM
 *  Author: moust
 */ 


#include "timer0.h"
#include <math.h>

EN_TIMERError_t TIMER0_init(MODE mode){
	switch(mode){
		case Normal:			CLEAR_BIT(TCCR0, WGM00);	CLEAR_BIT(TCCR0, WGM01); break;
		case PhaseCorrectPWM:	SET_BIT(TCCR0, WGM00);		CLEAR_BIT(TCCR0, WGM01); break;
		case CTC:				CLEAR_BIT(TCCR0, WGM00);	SET_BIT(TCCR0, WGM01); break;
		case FastPWM:			SET_BIT(TCCR0, WGM00);		SET_BIT(TCCR0, WGM01); break;
		default:	return WRONG_TIMER_MODE			;break;		// Error Handling
	}
	TCNT0 = 0x00;	// Set Timer Initial Value to Zero
	return NO_TIMER_ERROR;
}
EN_TIMERError_t TIMER0_start(PRESCALER prescaler){
	switch(prescaler){
		case STOP_TIMER:		CLEAR_BIT(TCCR0, CS00);		CLEAR_BIT(TCCR0, CS01);		CLEAR_BIT(TCCR0, CS02); break;
		case NO_PRESCALER:		SET_BIT(TCCR0, CS00);		CLEAR_BIT(TCCR0, CS01);		CLEAR_BIT(TCCR0, CS02); break;
		case PRESCALER_8:		CLEAR_BIT(TCCR0, CS00);		SET_BIT(TCCR0, CS01);		CLEAR_BIT(TCCR0, CS02); break;
		case PRESCALER_64:		SET_BIT(TCCR0, CS00);		SET_BIT(TCCR0, CS01);		CLEAR_BIT(TCCR0, CS02); break;
		case PRESCALER_256:		CLEAR_BIT(TCCR0, CS00);		CLEAR_BIT(TCCR0, CS01);		SET_BIT(TCCR0, CS02); break;
		case PRESCALER_1024:	SET_BIT(TCCR0, CS00);		CLEAR_BIT(TCCR0, CS01);		SET_BIT(TCCR0, CS02); break;
		case EXTERNAL_SOURCE_FALLING_EDGE:		CLEAR_BIT(TCCR0, CS00);		SET_BIT(TCCR0, CS01);		SET_BIT(TCCR0, CS02); break;
		case EXTERNAL_SOURCE_RISING_EDGE:		SET_BIT(TCCR0, CS00);		SET_BIT(TCCR0, CS01);		SET_BIT(TCCR0, CS02); break;
		default:		return WRONG_TIMER_PRESCALER		;break;
	}
	return NO_TIMER_ERROR;
}
EN_TIMERError_t TIMER0_stop(void){
	CLEAR_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS02);
	return NO_TIMER_ERROR;
}
EN_TIMERError_t TIMER0_set(uint8_t initialTime){
	TCNT0 = initialTime;
	return NO_TIMER_ERROR;
}
EN_TIMERError_t TIMER0_getState(uint8_t *currentTime){
	*currentTime = TCNT0;
	return NO_TIMER_ERROR;
}

EN_TIMERError_t TIMER0_delay_ms(uint16_t delay){
	EN_TIMERError_t timerIntError = TIMER0_init(Normal);
	EN_TIMERError_t timerPreError = NO_TIMER_ERROR;
	uint16_t no_of_iter = 0;
	uint16_t start;
	if(delay<=256){
		no_of_iter = 1;
		start = 256-delay;
		}else{
		no_of_iter = (uint16_t) ceil(delay/256.0);
		start = 256 - delay/no_of_iter;
	}
	uint16_t i;
	for(i=0; i<no_of_iter; i++){
		TIMER0_set(start);
		timerPreError = TIMER0_start(PRESCALER_1024);
		while(GET_BIT(TIFR, TOV0) == 0);
		SET_BIT(TIFR, TOV0);
	}
	TIMER0_stop();
	if(timerIntError == NO_TIMER_ERROR){
		return timerPreError;
	}else{
		return timerIntError;
	}
}