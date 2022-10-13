/*
 * bitManipulation.h
 *
 * Created: 9/29/2022 4:15:27 AM
 *  Author: moust
 */ 


#ifndef BITMANIPULATION_H_
#define BITMANIPULATION_H_

#include "types.h"

#define SET_BIT(PORT_Name, PIN_Name)	(PORT_Name) |= (1<<PIN_Name)
#define CLEAR_BIT(PORT_Name, PIN_Name)	(PORT_Name) &= ~(1<<PIN_Name)
#define TOGGLE_BIT(PORT_Name, PIN_Name)	(PORT_Name) ^= (1<<PIN_Name)
#define GET_BIT(PORT_Name, PIN_Name)	((PORT_Name & (1<<PIN_Name))>>PIN_Name)


#endif /* BITMANIPULATION_H_ */