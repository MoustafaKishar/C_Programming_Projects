/*
 * app.h
 *
 * Created: 9/29/2022 4:14:03 AM
 *  Author: moust
 */ 


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/LED Driver/led.h"
#include "../ECUAL/Button Driver/button.h"


#define CARS_TL_GREEN_LED PORTA, Pin0
#define CARS_TL_YELLOW_LED PORTA, Pin1
#define CARS_TL_RED_LED PORTA, Pin2

#define PED_TL_GREEN_LED PORTB, Pin0
#define PED_TL_YELLOW_LED PORTB, Pin1
#define PED_TL_RED_LED PORTB, Pin2

#define PED_BUTTON PORTD, Pin2

typedef enum{
	NormalMode,
	PedestrianMode	
}TrafficLightsMode;

TrafficLightsMode currentMode;
//Boolean isLongPress;

void APP_init(void);
void APP_start(void);



#endif /* APP_H_ */