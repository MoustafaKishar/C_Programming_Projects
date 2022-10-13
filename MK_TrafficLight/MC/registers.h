/*
 * registers.h
 *
 * Created: 9/29/2022 4:15:01 AM
 *  Author: moust
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_


#include "../Utilities/types.h"

/************************************************************************/
/* DIO REGISTERS:                                                       */
/************************************************************************/
// PORTA Registers:
#define PORTA_DIR *((volatile uint8_t*)(0x3A))
#define PORTA_DATA *((volatile uint8_t*)(0x3B))
#define PORTA_PINS *((volatile uint8_t*)(0x39))
// PORTB Registers:
#define PORTB_DIR *((volatile uint8_t*)(0x37))
#define PORTB_DATA *((volatile uint8_t*)(0x38))
#define PORTB_PINS *((volatile uint8_t*)(0x36))
// PORTC Registers:
#define PORTC_DIR *((volatile uint8_t*)(0x34))
#define PORTC_DATA *((volatile uint8_t*)(0x35))
#define PORTC_PINS *((volatile uint8_t*)(0x33))
// PORTD Registers:
#define PORTD_DIR *((volatile uint8_t*)(0x31))
#define PORTD_DATA *((volatile uint8_t*)(0x32))
#define PORTD_PINS *((volatile uint8_t*)(0x30))

/************************************************************************/
/* TIMER REGISTERS:                                                       */
/************************************************************************/
// TIMER0 Registers:
#define TCCR0 *((volatile uint8_t*) 0x53)
#define TCNT0 *((volatile uint8_t*) 0x52)
#define TIFR *((volatile uint8_t*) 0x58)
#define TIMSK *((volatile uint8_t*) 0x59)
#define OCR0 *((volatile uint8_t*) 0x5C)
#define SREG *((volatile uint8_t*) 0x5F)

/************************************************************************/
/* Interrupts Registers:                                                */
/************************************************************************/
// External Interrupts Registers:
#define MCUCR *((volatile uint8_t*) 0x55)
#define MCUCSR *((volatile uint8_t*) 0x54)
#define GICR *((volatile uint8_t*) 0x5B)
#define GIFR *((volatile uint8_t*) 0x5A)

#endif /* REGISTERS_H_ */