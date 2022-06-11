/*
 * GPIO_KAREEM.h
 *
 * Created: 2/23/2022 3:49:18 AM
 *  Author: K.EMAM
 */ 


#ifndef GPIO_KAREEM_H_
#define GPIO_KAREEM_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*PORT  SELECTION*/
#define GPIO_PORTA		0
#define GPIO_PORTB		1
#define GPIO_PORTC		2
#define GPIO_PORTD		3
/*PIN SELECTION */
#define GPIO_PIN_0		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7
#define GPIO_ALL_PINS	8
/*DIRECTION SELECTION*/ 
#define GPIO_PIN_INPUT	0x00
#define GPIO_PIN_OUTPUT	0xff
/*OUTPUT VALUE SELECTION */
#define GPIO_PIN_LOW	0x00
#define GPIO_PIN_HIGH	0xff


void GPIO_SetPinDir(u8 port,u8 pin,u8 dir);

void GPIO_SetPinVal(u8 port,u8 pin,u8 val);

void GPIO_TogglePin(u8 port, u8 pin);

u8 GPIO_GetPinVal(u8 port, u8 pin);

void GPIO_SetPullup(u8 port, u8 pin);





#endif /* GPIO_KAREEM_H_ */