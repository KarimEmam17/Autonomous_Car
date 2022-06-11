/*
* Autonomous_Car.c
*
* Created: 6/1/2022 3:53:08 PM
* Author : K.EMAM
*/

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "Interrupt.h"
#include "REG_ATMEL.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_KAREEM.h"
#include "servo_motor.h"
#include "ultrasonic_sensor.h"
#include "LCD.h"
#include "dcMotor.h"


int main(void)
{
	interrupt_enable();
	CLEAR_BIT(DDRD, GPIO_PIN_2);
	CLEAR_BIT(PORTA, Trigger_pin);
	Servo_MotorInit();
	LCD_INIT();
	motorInit();
	init_timer0(T0_NORMAL);
	extInt_init();
    init_External_Interrupt(External_Interrupt_0);
	select_mode_of_External_Interrupt(External_Interrupt_0,The_rising_edge_mode);
	f64 distl;
	f64 distR=0;

	/* Replace with your application code */
	while (1)
	{
		ultrasonic_trig();
		
		Servo_MotorRotate(Forward);
		LCD_Clear();
		LCD_WriteSTRING("the  dist");
		LCD_GoTo(1,1);
		distl = UltrasonicRead();
		LCD_WriteINTEGER((u32) distl);
		LCD_GoTo(2,1);
		
		backward();
		
	}

}
ISR(TIMER0_OVF_vect)
{
	no_ovf++;
}

ISR(INT0_vect)
{
	if (flag == 0)
	{
		TCNT0 = 0 ;
		//	CLEAR_BIT(MCUCR, ISC00);
		//	SET_BIT(MCUCR, ISC01);
		(void)select_mode_of_External_Interrupt(External_Interrupt_0,The_falling_edge_mode);
		no_ovf = 0;
	}
	else if(flag == 1)
	{
		
		fcap1 = TCNT0;
		OV_final = no_ovf;
		
		CLEAR_BIT(TIMSK, TOIE0);
		CLEAR_BIT(GICR, INT0);
	}
	flag++;
}