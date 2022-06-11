/*
 * ultrasonic_sensor.h
 *
 * Created: 5/27/2022 4:40:55 PM
 *  Author: K.EMAM
 */ 


#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_
#include "Interrupt.h" 
#include "TIMER.h"
#include <avr/delay.h>
#include "GPIO_KAREEM.h"
#include "REG_ATMEL.h"
#include "STD_TYPES.h"

#define	TOV0		0
#define	TOIE0		0

#define trig_pin	 GPIO_PIN_0
#define ECho		 GPIO_PIN_2
#define Trigger_pin	 GPIO_PIN_0

volatile u16 fcap1,fcap2;  // variables for fist  capture and second capture
volatile u8 flag;          //flag  used in ISR
volatile u16 OV_final; // the total  no of over flow ultra sonic read
volatile u16 no_ovf;    // the no of overflow in ISR
u32 ticks;
f64 dist;

void ultrasonic_trig(void);
 f64 UltrasonicRead(void);
 void extInt_init(void);


 




#endif /* ULTRASONIC_SENSOR_H_ */