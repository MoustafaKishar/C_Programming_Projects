/*
 * led.c
 *
 * Created: 9/29/2022 4:30:03 AM
 *  Author: moust
 */ 

#include "led.h"

EN_LEDError_t LED_init(PORT_Name port, PIN_Name pin){
	return DIO_initPin(port, pin, Output);
}
EN_LEDError_t LED_turnON(PORT_Name port, PIN_Name pin){
	return DIO_writePin(port, pin, HIGH);
}
EN_LEDError_t LED_turnOFF(PORT_Name port, PIN_Name pin){
	return DIO_writePin(port, pin, LOW);
}
EN_LEDError_t LED_toggle(PORT_Name port, PIN_Name pin){
	return DIO_togglePin(port, pin);
}
EN_LEDError_t LED_get_state(PORT_Name port, PIN_Name pin, PIN_Value *value){
	return DIO_readPin(port, pin, value);
}
EN_LEDError_t LED_toggle_w_delay(PORT_Name port, PIN_Name pin, uint16_t delay_ms){
	LED_turnON(port, pin);
	EN_TIMERError_t timerError = TIMER0_delay_ms(delay_ms);
	LED_turnOFF(port, pin);
	if(timerError == NO_TIMER_ERROR){
		return NO_LED_ERROR;
	}else{
		return WRONG_TIMER_INPUT;
	}
}

EN_LEDError_t LED_blink(PORT_Name port, PIN_Name pin, uint8_t blinks, uint16_t delay_ms){
	uint8_t i;
	EN_LEDError_t error = NO_LED_ERROR;
	for(i = 0; i<blinks; i++){
		error = LED_toggle_w_delay(port, pin, (delay_ms/blinks));
	}
	return error;
}

EN_LEDError_t TWO_LEDs_blink(PORT_Name port1, PIN_Name pin1, PORT_Name port2, PIN_Name pin2, uint8_t blinks, uint16_t delay_ms){
	uint8_t i;
	EN_TIMERError_t timerError = NO_TIMER_ERROR;
	for(i = 0; i<blinks; i++){
		LED_turnON(port1, pin1);
		LED_turnON(port2, pin2);
		timerError = TIMER0_delay_ms(delay_ms/blinks);
		LED_turnOFF(port1, pin1);
		LED_turnOFF(port2, pin2);
	}
	if(timerError == NO_TIMER_ERROR){
		return NO_LED_ERROR;
	}else{
		return WRONG_TIMER_INPUT;
	}
}