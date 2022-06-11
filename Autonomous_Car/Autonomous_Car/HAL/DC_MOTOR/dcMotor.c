/*
* dcMotor.c
*
* Created: 5/27/2022 4:41:34 PM
*  Author: K.EMAM
*/

#include "dcMotor.h"

#include "STD_TYPES.h"
#include "REG_ATMEL.h"
#include "BIT_MATH.h"
/* define H-bridge bins for motor1 & motor2 */
#define IN1		3
#define IN2		4
#define IN3		5
#define IN4		6
/***************************************/

#define EN1		0
#define EN2		1



void motorInit(void)
{
	/*  Set these H-bridge bins as output  */
	SET_BIT(DDRC, IN4);
	SET_BIT(DDRC, IN3);
	SET_BIT(DDRC, IN2);
	SET_BIT(DDRC, IN1);
	/************************************/
	
	/**   set enable bins on H-bridge to Hight   **/
	SET_BIT(DDRC, EN1);
	SET_BIT(DDRC, EN2);
	
	SET_BIT(PORTC, EN1);
	SET_BIT(PORTC, EN2);
	/*************************/
}

void motorStop (void)
{
	CLEAR_BIT (PORTC, IN2);
	CLEAR_BIT (PORTC, IN1);
	CLEAR_BIT (PORTC, IN4);
	CLEAR_BIT (PORTC, IN3);
}

void motorStart(void)
{
	SET_BIT   (PORTC, IN2);
	CLEAR_BIT (PORTC, IN1);
	SET_BIT   (PORTC, IN4);
	CLEAR_BIT (PORTC, IN3);
}

void turnRight(void)
{
	CLEAR_BIT (PORTC, IN2);
	CLEAR_BIT (PORTC, IN1);
	SET_BIT   (PORTC, IN4);
	CLEAR_BIT (PORTC, IN3);
}

void turnLeft(void)
{
	SET_BIT   (PORTC, IN2);
	CLEAR_BIT (PORTC, IN1);
	CLEAR_BIT (PORTC, IN4);
	CLEAR_BIT (PORTC, IN3);
}


void backward(void)
{
	CLEAR_BIT (PORTC, IN2);
	SET_BIT   (PORTC, IN1);
	CLEAR_BIT (PORTC, IN4);
	SET_BIT   (PORTC, IN3);
}