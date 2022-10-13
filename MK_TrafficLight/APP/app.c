/*
 * app.c
 *
 * Created: 9/29/2022 4:13:20002 AM
 *  Author: moust
 */ 

#include "app.h"


void APP_init(void){
	LED_init(CARS_TL_GREEN_LED);
	LED_init(CARS_TL_YELLOW_LED);
	LED_init(CARS_TL_RED_LED);
	
	LED_init(PED_TL_GREEN_LED);
	LED_init(PED_TL_YELLOW_LED);
	LED_init(PED_TL_RED_LED);
	
	Button_init(PED_BUTTON);
	external_interrupt_init(EXT0, RisingEdge);		// Rising Edge handles the long press

	currentMode = NormalMode;
}

void APP_start(void){
	cli();
	sei();		// To restart the interrupt
	while(1){
		if(currentMode == PedestrianMode){		// If button was pressed, perform Pedestrian Mode Logic
			LED_turnOFF(PED_TL_RED_LED);
			PIN_Value greenLedValue = LOW, yellowLedValue = LOW, redLedValue = LOW;
			LED_get_state(CARS_TL_GREEN_LED, &greenLedValue);
			LED_get_state(CARS_TL_YELLOW_LED, &yellowLedValue);
			LED_get_state(CARS_TL_RED_LED, &redLedValue);
		
			if(redLedValue == HIGH){
				LED_turnON(PED_TL_GREEN_LED);
				LED_toggle_w_delay(CARS_TL_RED_LED, 5000);
			}else if(greenLedValue == HIGH || yellowLedValue == HIGH){
				LED_turnON(PED_TL_RED_LED);
				TWO_LEDs_blink(PED_TL_YELLOW_LED, CARS_TL_YELLOW_LED, 20, 5000);
				LED_turnOFF(CARS_TL_GREEN_LED);
				LED_turnOFF(PED_TL_RED_LED);
				LED_turnON(PED_TL_GREEN_LED);
				LED_toggle_w_delay(CARS_TL_RED_LED, 5000);
			}
			TWO_LEDs_blink(PED_TL_YELLOW_LED, CARS_TL_YELLOW_LED, 20, 5000);
			LED_turnOFF(PED_TL_GREEN_LED);
			LED_turnON(PED_TL_RED_LED);
			currentMode = NormalMode;
		}else{	// If not, perform Normal Mode Logic
			LED_turnON(PED_TL_RED_LED);
			LED_toggle_w_delay(CARS_TL_GREEN_LED, 5000);
			LED_blink(CARS_TL_YELLOW_LED, 20, 5000);
			LED_toggle_w_delay(CARS_TL_RED_LED, 5000);
			LED_blink(CARS_TL_YELLOW_LED, 20, 5000);
		}
	}
}
		

ISR(EXT_INT_0){
	if(currentMode == NormalMode) // IF condition to handle the multi-press & long press
	{	
		currentMode = PedestrianMode;
		APP_start();
	}
}