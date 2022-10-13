/*
 * button.c
 *
 * Created: 9/29/2022 4:29:54 AM
 *  Author: moust
 */ 

#include "button.h"

EN_ButtonError_t Button_init(PORT_Name port, PIN_Name pin){
	return DIO_initPin(port, pin, Input);
}
EN_ButtonError_t Button_get_state(PORT_Name port, PIN_Name pin, PIN_Value *value){
	return DIO_readPin(port, pin, value);
}