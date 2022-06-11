/*
 * servo_motor.h
 *
 * Created: 5/27/2022 4:15:04 PM
 *  Author: K.EMAM
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_
#include "GPIO_KAREEM.h"
#include "TIMER.h"
#include "STD_TYPES.h"
#include "REG_ATMEL.h"
#include "BIT_MATH.h"

#define servo_pin   GPIO_PIN_5

#define  Right		 300
#define  Left		 65
#define  Forward	 187

 void Servo_MotorInit(void);
 void Servo_MotorRotate( u16 DIR);
 




#endif /* SERVO_MOTOR_H_ */