/*
 * dio.h
 *
 * Created: 9/29/2022 4:21:55 AM
 *  Author: moust
 */ 


#ifndef DIO_H_
#define DIO_H_


#include "../../MC/registers.h"
#include "../../Utilities/bitManipulation.h"

// Typedefs
typedef enum{
	NO_DIO_ERROR,
	WRONG_DIO_DIRECTION,
	WRONG_DIO_PORT,
	WRONG_DIO_PIN,
	WRONG_DIO_PIN_VALUE
}EN_DIOError_t;

typedef enum{
	Pin0,
	Pin1,
	Pin2,
	Pin3,
	Pin4,
	Pin5,
	Pin6,
	Pin7
}PIN_Name;

typedef enum{
	PORTA,
	PORTB,
	PORTC,
	PORTD
}PORT_Name;

typedef enum{
	Input,
	Output
}Direction;

typedef enum{
	LOW,
	HIGH
}PIN_Value;


// Function prototypes

EN_DIOError_t DIO_initPort(PORT_Name port, Direction direction);			// Initializes DIO PORT Direction
EN_DIOError_t DIO_initPin(PORT_Name port, PIN_Name pin, Direction direction);		// Initializes DIO PIN Direction
EN_DIOError_t DIO_writePort(PORT_Name port, uint8_t value);			// Write Data to DIO  PORT
EN_DIOError_t DIO_writePin(PORT_Name port, PIN_Name pin, PIN_Value value);			// Write Data to DIO PIN
EN_DIOError_t DIO_readPin(PORT_Name port, PIN_Name pin, PIN_Value *value);			// Read DIO PIN, return in value as leave function return for Error Handling
EN_DIOError_t DIO_togglePin(PORT_Name port, PIN_Name pin);		// Toggle DIO PIN



#endif /* DIO_H_ */