/*
 * external_interrupts.h
 *
 * Created: 9/29/2022 4:24:09 AM
 *  Author: moust
 */ 


#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_


#include "../../MC/registers.h"
#include "../../Utilities/bitManipulation.h"

/************************************************************************/
/* Interrupts Bits:                                                     */
/************************************************************************/
// MCUCR Bits
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
// MCUCSR Bit
#define ISC2 6
// GICR Bits
#define INT0 6
#define INT1 7
#define INT2 5
// GIFR Bits
#define INTF0 6
#define INTF1 7
#define INTF2 5

/************************************************************************/
/* Typedefs:                                                            */
/************************************************************************/
typedef enum{
	NO_INT_ERROR,
	WRONG_INT_SENSE,
	WRONG_INT_CHANNEL
}EN_ExtIntError_t;

typedef enum{
	EXT0,
	EXT1,
	EXT2
}External_Interrupt;

typedef enum{
	LowLevel,
	Any,
	FallingEdge,
	RisingEdge
}Interrupt_Sense;

/************************************************************************/
/* Interrupts Vectors:                                                  */
/************************************************************************/
// External Interrupts Vectors:
#define EXT_INT_0 __vector_1		// External Interrupt Request 0
#define EXT_INT_1 __vector_2		// External Interrupt Request 1
#define EXT_INT_2 __vector_3		// External Interrupt Request 2

/************************************************************************/
/* Interrupts Functions:                                                */
/************************************************************************/
// Set Global Interrupts, Set the I-bit in the status register to 1
#define sei() __asm__ __volatile__ ("sei" ::: "memory")

// Set Global Interrupts, Set the I-bit in the status register to 0
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

// ISR Definition
#define ISR(INT_VECT)void INT_VECT(void) __attribute__ ((signal, used));\
void INT_VECT(void)

/************************************************************************/
/* External Interrupts Functions:                                       */
/************************************************************************/
EN_ExtIntError_t external_interrupt_init(External_Interrupt extInt, Interrupt_Sense intSense);



#endif /* EXTERNAL_INTERRUPTS_H_ */