/*
 * led.h
 *
 * Created: 9/29/2022 4:30:15 AM
 *  Author: moust
 */ 


#ifndef LED_H_
#define LED_H_


#include "../../MCAL/DIO Driver/dio.h"
#include "../../MCAL/TIMER0 Driver/timer0.h"

typedef enum{
	NO_LED_ERROR,
	WRONG_LED_DIRECTION,
	WRONG_LED_PORT,
	WRONG_LED_PIN,
	WRONG_LED_PIN_VALUE,
	WRONG_TIMER_INPUT
}EN_LEDError_t;

EN_LEDError_t LED_init(PORT_Name port, PIN_Name pin);
EN_LEDError_t LED_turnON(PORT_Name port, PIN_Name pin);
EN_LEDError_t LED_turnOFF(PORT_Name port, PIN_Name pin);
EN_LEDError_t LED_toggle(PORT_Name port, PIN_Name pin);
EN_LEDError_t LED_toggle_w_delay(PORT_Name port, PIN_Name pin, uint16_t delay_ms);
EN_LEDError_t LED_blink(PORT_Name port, PIN_Name pin, uint8_t blinks, uint16_t delay_ms);
EN_LEDError_t TWO_LEDs_blink(PORT_Name port1, PIN_Name pin1, PORT_Name port2, PIN_Name pin2, uint8_t blinks, uint16_t delay_ms);
EN_LEDError_t LED_get_state(PORT_Name port, PIN_Name pin, PIN_Value *value);



#endif /* LED_H_ */