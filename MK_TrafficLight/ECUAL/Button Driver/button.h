/*
 * button.h
 *
 * Created: 9/29/2022 4:29:42 AM
 *  Author: moust
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO Driver/dio.h"
#include "../../MCAL/External Interrupts Driver/external_interrupts.h"


typedef enum{
	NO_BUTTON_ERROR,
	WRONG_BUTTON_DIRECTION,
	WRONG_BUTTON_PORT,
	WRONG_BUTTON_PIN,
	WRONG_BUTTON_PIN_VALUE
}EN_ButtonError_t;

EN_ButtonError_t Button_init(PORT_Name port, PIN_Name pin);
EN_ButtonError_t Button_get_state(PORT_Name port, PIN_Name pin, PIN_Value *value);

#endif /* BUTTON_H_ */