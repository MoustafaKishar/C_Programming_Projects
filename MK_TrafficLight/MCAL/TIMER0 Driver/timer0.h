/*
 * timer0.h
 *
 * Created: 9/29/2022 4:22:28 AM
 *  Author: moust
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_


#include "../../MC/registers.h"
#include "../../Utilities/bitManipulation.h"

// Typedefs
typedef enum{
	NO_TIMER_ERROR,
	WRONG_TIMER_MODE,
	WRONG_TIMER_PRESCALER,
}EN_TIMERError_t;
/************************************************************************/
/* TIMER0                                                               */
/************************************************************************/
// TCCR0: Timer/Counter Control Register

#define CS00 0		//Prescaler Bits
#define CS01 1
#define CS02 2
#define WGM00 6		// Mode Bits
#define WGM01 3
#define COM00 4		// Compare Output Match Mode
#define COM01 5
#define FOC0 7		// Force Output Compare

// TIFR: Timer/ Counter Interrupt Flag Register
#define TOV0  0		// Overflow Flag
#define OCF0  1		// Output Compare Flag

// TIMSK: Timer/ Counter Interrupt Mask Register
#define TOIE0 0
#define OCIE0 1

// Timer0 Configurations:
typedef enum{		// TIMER0 MODES: WGM00 & WGM01 Bits
	Normal,
	PhaseCorrectPWM,
	CTC,
	FastPWM
}MODE;

typedef enum{		// PRESCALER:
	STOP_TIMER, //0
	NO_PRESCALER, //1
	PRESCALER_8, //2
	PRESCALER_64, //3
	PRESCALER_256, //4
	PRESCALER_1024, //5
	EXTERNAL_SOURCE_FALLING_EDGE, //6
	EXTERNAL_SOURCE_RISING_EDGE //7
}PRESCALER;


EN_TIMERError_t TIMER0_init(MODE mode);
EN_TIMERError_t TIMER0_start(PRESCALER prescaler);
EN_TIMERError_t TIMER0_stop(void);
EN_TIMERError_t TIMER0_set(uint8_t initialTime);
EN_TIMERError_t TIMER0_getState(uint8_t *currentTime);
EN_TIMERError_t TIMER0_delay_ms(uint16_t delay);


#endif /* TIMER0_H_ */