/*
 * ultrasonic_sensor.c
 *
 * Created: 5/27/2022 4:41:34 PM
 *  Author: K.EMAM
 */ 
#include "ultrasonic_sensor.h"
#include "Interrupt.h"
#include "TIMER.h"
#include <avr/interrupt.h>





void ultrasonic_trig(void)
{
	SET_BIT(DDRA,Trigger_pin);
	_delay_us(2);
	SET_BIT(PORTA,Trigger_pin);
	_delay_us(10);
	CLEAR_BIT(PORTA,Trigger_pin);
}
f64 UltrasonicRead(void)
{
	//ultrasonic_trig();
	CLEAR_BIT(PORTA, Trigger_pin);
	_delay_us(2);
	
	SET_BIT(PORTA, Trigger_pin);
	_delay_us(10);
	CLEAR_BIT(PORTA, Trigger_pin);
	if (flag ==2)
	{
		flag=0;
		ticks=fcap1+(256*OV_final);
		dist=(f64)ticks/932.95;
		OV_final=0;
		no_ovf=0;
	//		SET_BIT(MCUCR, ISC00);
	//		SET_BIT(MCUCR, ISC01);
		(void)select_mode_of_External_Interrupt(External_Interrupt_0,The_rising_edge_mode);
		/* set input ovf flag to 1 to disable it */
		SET_BIT(TIFR, TOV0);
		SET_BIT(GIFR, INTF0);
		/* enable external interrupt and overflow interrupt */
		SET_BIT(TIMSK, TOIE0);
		SET_BIT(GICR, INT0);
		
		
	} 
	return dist;
}

void extInt_init(void)
{
	cli();
	
	CLEAR_BIT(DDRD, 2);  // set PD2 as input for external interrupt
	//DDRC |= 0xFF;
	SET_BIT(DDRA, Trigger_pin); /* Make trigger pin as output */
	
	TCNT0 = 0;
	TCCR0 = 0;		/* Set all bit to zero Normal operation */
	
	
	SET_BIT(TCCR0, CS00); // set prescalar to 1
	
	/*  set external interrupt sense rising edge */
	SET_BIT(MCUCR, ISC00);
	SET_BIT(MCUCR, ISC01);
	
	SET_BIT(GICR, INT0); // enable interrupt 0
	SET_BIT(TIMSK, TOIE0); /* Enable Timer0 overflow interrupts */
	
	sei();			/* Enable global interrupt */
}



