/*
 * GPIO_KAREEM.c
 *
 * Created: 2/23/2022 5:21:06 AM
 *  Author: K.EMAM
 */ 


#include "GPIO_KAREEM.h"
#include "REG_ATMEL.h"


void GPIO_SetPinDir(u8 port,u8 pin,u8 dir)
{
	switch (dir)
	{
		case GPIO_PIN_INPUT:
		if (pin>=0 && pin<=7)
		{
			switch (port)
			{
				case GPIO_PORTA:
				CLEAR_BIT(DDRA, pin);
				break;
				case GPIO_PORTB:
				CLEAR_BIT(DDRB, pin);
				break;
				case GPIO_PORTC:
				CLEAR_BIT(DDRC, pin);
				break;
				case GPIO_PORTD:
				CLEAR_BIT(DDRD,pin);
				break;
				default:
				break;	
			}
		}
		else
		{
			switch (port)
			{
				case GPIO_PORTA:
				DDRA = dir ;
				break;
				case GPIO_PORTB:
				DDRB= dir ;
				break;
				case GPIO_PORTC:
				DDRC = dir ;
				break;
				case GPIO_PORTD:
				DDRD = dir ;
				break;
				default:
				break;
			}
		}
		break;
		case GPIO_PIN_OUTPUT:
		if (pin>=0 && pin<=7)
		{
			switch (port)
			{
				case GPIO_PORTA:
				SET_BIT(DDRA, pin);
				break;
				case GPIO_PORTB:
				SET_BIT(DDRB, pin);
				break;
				case GPIO_PORTC:
				SET_BIT(DDRC, pin);
				break;
				case GPIO_PORTD:
				SET_BIT(DDRD,pin);
				break;
				default:
				break;
			}
		}
		else
		{
			switch (port)
			{
				case GPIO_PORTA:
				DDRA = dir ;
				break;
				case GPIO_PORTB:
				DDRB= dir ;
				break;
				case GPIO_PORTC:
				DDRC = dir ;
				break;
				case GPIO_PORTD:
				DDRD = dir ;
				break;
				default:
				break;
			}
		}
		break;
		default:
		break;	
	}
		
}

void GPIO_SetPinVal(u8 port, u8 pin, u8 val)
{
	switch (val)
	{
		case GPIO_PIN_LOW:
		if (pin>=0 && pin<=7)
		{
			GPIO_SetPinDir(port,pin,GPIO_PIN_OUTPUT);
			switch(port)
			{
				case GPIO_PORTA:
				CLEAR_BIT(PORTA,pin);
				break;
				case GPIO_PORTB:
				CLEAR_BIT(PORTB,pin);
				break;
				case GPIO_PORTC:
				CLEAR_BIT(PORTC,pin);
				break;
				case GPIO_PORTD:
				CLEAR_BIT(PORTD,pin);
				break;
				default:
				break;
			}
		}
		else
		{
			GPIO_SetPinDir(port,GPIO_ALL_PINS,GPIO_PIN_OUTPUT);
			switch(port)
			{
				case GPIO_PORTA:
				PORTA =val;
				break;
				case GPIO_PORTB:
				PORTB =val;
				break;
				case GPIO_PORTC:
				PORTC =val;
				break; 
				case GPIO_PORTD:
				PORTD =val;
				break;
				default:
				break;
			}
		}
		break;
		case GPIO_PIN_HIGH:
		if (pin >=0 && pin <=7)
		{
			GPIO_SetPinDir(port,pin,GPIO_PIN_OUTPUT);
			switch(port)
			{
				case GPIO_PORTA:
				SET_BIT(PORTA,pin);
				break;
				case GPIO_PORTB:
				SET_BIT(PORTB,pin);
				break;
				case GPIO_PORTC:
				SET_BIT(PORTC,pin);
				break;
				case GPIO_PORTD:
				SET_BIT(PORTD,pin);
				break;
				default:
				break;
			}
		}
		else
		{
				GPIO_SetPinDir(port,GPIO_ALL_PINS,GPIO_PIN_OUTPUT);
				switch(port)
				{
					case GPIO_PORTA:
					PORTA =val ;
					break;
					case GPIO_PORTB:
					PORTB =val ;
					break;
					case GPIO_PORTC:
					PORTC =val ;
					break;
					case GPIO_PORTD:
					PORTD =val ;
					break;
					default:
					break;
				}
		}
		break;
		default:
		break;	
	}
}

void GPIO_TogglePin(u8 port, u8 pin)
{
	if (pin >=0 && pin <=7)
	{
		GPIO_SetPinDir(port, pin, GPIO_PIN_OUTPUT);
		switch (port)
		{
			case GPIO_PORTA:
			TOGGLE_BIT(PORTA, pin);
			break;
			case GPIO_PORTB:
			TOGGLE_BIT(PORTB, pin);
			break;
			case GPIO_PORTC:
			TOGGLE_BIT(PORTC, pin);
			break;
			case GPIO_PORTD:
			TOGGLE_BIT(PORTD, pin);
			break;
			default:   //MISRA C rules
			break;
		}
	}
	else
	{
		GPIO_SetPinDir(port, GPIO_ALL_PINS, GPIO_PIN_OUTPUT);
		switch (port)
		{
			case GPIO_PORTA:
			PORTA ^= 0xff;
			break;
			case GPIO_PORTB:
			PORTB ^= 0xff;
			break;
			case GPIO_PORTC:
			PORTC ^= 0xff;
			break;
			case GPIO_PORTD:
			PORTD ^= 0xff;
			break;
			default:   //MISRA C rules
			break;
		}
	}
}

u8 GPIO_GetPinVal(u8 port, u8 pin)
{
	u8 val = 0;
	if (pin >=0 && pin <=7)
	{
		GPIO_SetPinDir(port, pin, GPIO_PIN_INPUT);
		switch (port)
		{
			case GPIO_PORTA:
			val = GET_BIT(PINA, pin);
			break;
			case GPIO_PORTB:
			val = GET_BIT(PINB, pin);
			break;
			case GPIO_PORTC:
			val = GET_BIT(PINC, pin);
			break;
			case GPIO_PORTD:
			val = GET_BIT(PIND, pin);
			break;
			default:   //MISRA C rules
			break;
		}
	}
	else
	{
		GPIO_SetPinDir(port, GPIO_ALL_PINS, GPIO_PIN_INPUT);
		switch (port)
		{
			case GPIO_PORTA:
			val = PINA;
			break;
			case GPIO_PORTB:
			val = PINB;
			break;
			case GPIO_PORTC:
			val = PINC;
			break;
			case GPIO_PORTD:
			val = PIND;
			break;
			default:   //MISRA C rules
			break;
		}
	}
	return val;
}

void GPIO_SetPullup(u8 port, u8 pin)
{
	if (pin >=0 && pin <=7)
	{
		GPIO_SetPinDir(port, pin, GPIO_PIN_INPUT);
		switch (port)
		{
			case GPIO_PORTA:
			SET_BIT(PORTA, pin);
			break;
			case GPIO_PORTB:
			SET_BIT(PORTB, pin);
			break;
			case GPIO_PORTC:
			SET_BIT(PORTC, pin);
			break;
			case GPIO_PORTD:
			SET_BIT(PORTD, pin);
			break;
			default:   //MISRA C rules
			break;
		}
	}
	else
	{
		GPIO_SetPinDir(port, GPIO_ALL_PINS, GPIO_PIN_INPUT);
		switch (port)
		{
			case GPIO_PORTA:
			PORTA = 0xff;
			break;
			case GPIO_PORTB:
			PORTB = 0xff;
			break;
			case GPIO_PORTC:
			PORTC = 0xff;
			break;
			case GPIO_PORTD:
			PORTD = 0xff;
			break;
			default:   //MISRA C rules
			break;
		}
	}
}