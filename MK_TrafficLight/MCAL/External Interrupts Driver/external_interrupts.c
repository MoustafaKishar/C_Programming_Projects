/*
 * external_interrupts.c
 *
 * Created: 9/29/2022 4:23:56 AM
 *  Author: moust
 */ 


#include "external_interrupts.h"

EN_ExtIntError_t external_interrupt_init(External_Interrupt extInt, Interrupt_Sense intSense){
	sei();
	if(extInt == EXT0){
		switch(intSense){
			case LowLevel:		CLEAR_BIT(MCUCR, ISC00);
								CLEAR_BIT(MCUCR, ISC01);	break;
			case Any:			SET_BIT(MCUCR, ISC00);
								CLEAR_BIT(MCUCR, ISC01);	break;
			case FallingEdge:	CLEAR_BIT(MCUCR, ISC00);
								SET_BIT(MCUCR, ISC01);		break;
			case RisingEdge:	SET_BIT(MCUCR, ISC00);
								SET_BIT(MCUCR, ISC01);		break;
			default: return WRONG_INT_SENSE; break;	// Error Handling
		}
		SET_BIT(GICR, INT0);
	}else if(extInt == EXT1){
		switch(intSense){
			case LowLevel:		CLEAR_BIT(MCUCR, ISC10);
								CLEAR_BIT(MCUCR, ISC11);	break;
			case Any:			SET_BIT(MCUCR, ISC10);
								CLEAR_BIT(MCUCR, ISC11);	break;
			case FallingEdge:	CLEAR_BIT(MCUCR, ISC10);
								SET_BIT(MCUCR, ISC11);		break;
			case RisingEdge:	SET_BIT(MCUCR, ISC10);
								SET_BIT(MCUCR, ISC11);		break;
			default: return WRONG_INT_SENSE; break;	// Error Handling
		}
		SET_BIT(GICR, INT1);
	}else if(extInt == EXT2){
		switch(intSense){
			case FallingEdge:	CLEAR_BIT(MCUCSR, ISC2);	break;
			case RisingEdge:	SET_BIT(MCUCSR, ISC2);		break;
			default: return WRONG_INT_SENSE; break;	// Error Handling
		}
		SET_BIT(GICR, INT2);
	}else{
		return WRONG_INT_CHANNEL;// Error Handling
	}
	return NO_INT_ERROR;
}