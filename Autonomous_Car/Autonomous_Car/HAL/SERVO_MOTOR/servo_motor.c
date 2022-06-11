/*
* servo_motor.c
*
* Created: 5/27/2022 4:14:39 PM
*  Author: K.EMAM
*/
#include "servo_motor.h"
#include <avr/delay.h>

u16 icr;
void Servo_MotorInit(void)
{
	SET_BIT(DDRD,GPIO_PIN_5);  // set OC1A (bin 5) as output

	
	// SET fast pwm with ICR1 as top  
	init_timer1(T1_FAST_PWM_ICR1);
	select_Compare_Match_Output_Mode_of_timer1(T1_FAST_PWM_ICR1,Clear_OC1A_on_compare_match_set_OC1B_at_TOP,COM1A);// clear OC1A on compare match
	// SET PRESCALAR 8
	start_timer1(From_prescaler_8);
	// law F_pwm = f_cpu / ( N*(1+TOP) )
	// servo motor needs 50 HZ according to law ---> TOP = 39999
	// store 39999 inside ICR1 as top for 8 prescalar

	icr = 39999;
	
	ICR1H = (icr>>8);
	ICR1L =  icr;
	
	TCNT1 = 0;
	
}
void Servo_MotorRotate( u16 DIR)
{
	OCR1A=DIR;
	
}