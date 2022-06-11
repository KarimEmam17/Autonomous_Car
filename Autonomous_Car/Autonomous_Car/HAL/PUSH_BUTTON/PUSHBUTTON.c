/*
 * PUSHBUTTON.c
 *
 * Created: 4/5/2022 5:34:57 AM
 *  Author: K.EMAM
 */ 
#define F_CPU 16000000
#include "util/delay.h"
#include "PUSHBUTTON.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_KAREEM.h"
#include "REG_ATMEL.h"

s8 init_push_button(push_button_index push_index)
{
	
	switch(push_index)
	{
		case zero:
		{
			GPIO_SetPinDir(GPIO_PORTB,GPIO_PIN_0,GPIO_PIN_INPUT);
			GPIO_SetPinVal(GPIO_PORTB,GPIO_PIN_0,GPIO_PIN_HIGH);
			return success;	
			break;
		}
		case one:
		{
			GPIO_SetPinDir(GPIO_PORTD,GPIO_PIN_6,GPIO_PIN_INPUT);
			GPIO_SetPinVal(GPIO_PORTD,GPIO_PIN_6,GPIO_PIN_HIGH);
			return success;	
			break;
		}
		case two:
		{
			GPIO_SetPinDir(GPIO_PORTD,GPIO_PIN_2,GPIO_PIN_INPUT);
			GPIO_SetPinVal(GPIO_PORTD,GPIO_PIN_2,GPIO_PIN_HIGH);
			return success;	
			break;
		}
		default:
		return invalid;
	
	}
		
}
s8 push_button_pressed_type(push_button_index u8_push_button_index,struct_push_button_info str_info, u32 u32_count,s32 s32_status)
{
		//struct_push_button_info str_info;
		str_info.push_index=invalid_button;
		str_info.pressed_type=failed;
		str_info.duration_long=invaild_duration;
		//u32 u32_count=0;
	if(u8_push_button_index>-1 && u8_push_button_index<4)
	{
		
	
		switch(u8_push_button_index)
		{
			case zero:
			{
				
				
				_delay_ms(500);
				if(s32_status == 1)
				{
					str_info.push_index=zero;
					str_info.pressed_type=successful_pressed;
					
					/*while(GPIO_GetPinVal(GPIO_PORTB,GPIO_PIN_0) == 0)
					{
						u32_count++;
						_delay_ms(1000);
					}*/
					
					
					if ((u32_count>=0) && (u32_count<=3))
					{
						str_info.duration_long=shortt;
						
					}
					else if ((u32_count>=4) && (u32_count<=6))
					{
						str_info.duration_long=doubleeee;
						
					} 
					else
					{
						str_info.duration_long=longg;
						
					}
					
					/*if (str_info.duration_long==longg)
					{
						SET_BIT(PORTC,GPIO_PIN_7);
						_delay_ms(1000);
						CLEAR_BIT(PORTC,GPIO_PIN_7);
					}*/
				
				}
				else if (GPIO_GetPinVal(GPIO_PORTB,GPIO_PIN_0) == 0)
				{
					str_info.push_index=zero;
					str_info.pressed_type=released;
				}
				
				break;
			}
			case one:
			{
				_delay_ms(15);
				if( s32_status== 1)
				{
					str_info.push_index=one;
					str_info.pressed_type=successful_pressed;
					/*while(GPIO_GetPinVal(GPIO_PORTB,GPIO_PIN_0) == 0)
					{
						u32_count++;
						_delay_ms(1000);
					}*/
					if ((u32_count>0) && (u32_count<3))
					{
						str_info.duration_long=shortt;
					}
					else if ((u32_count>3) && (u32_count<6))
					{
						str_info.duration_long=doubleeee;
					}
					else
					{
						str_info.duration_long=longg;
					}
					
				}
				else if (GPIO_GetPinVal(GPIO_PORTD,GPIO_PIN_6) == 0)
				{
					str_info.push_index=one;
					str_info.pressed_type=released;
				}
				
				break;
			}
			case 2:
			{
				_delay_ms(15);
				if( s32_status == 1)
				{
					str_info.push_index=two;
					str_info.pressed_type=successful_pressed;
					/*while(GPIO_GetPinVal(GPIO_PORTB,GPIO_PIN_0) == 0)
					{
						u32_count++;
						_delay_ms(1000);
					}*/
					if ((u32_count>0) && (u32_count<3))
					{
						str_info.duration_long=shortt;
					}
					else if ((u32_count>3) && (u32_count<6))
					{
						str_info.duration_long=doubleeee;
					}
					else
					{
						str_info.duration_long=longg;
					}
					
				}
				else if (GPIO_GetPinVal(GPIO_PORTD,GPIO_PIN_2) == 0)
				{
					str_info.push_index=two;
					str_info.pressed_type=released;
				}
				
				break;
			}
			default:break;
			}
			/*SET_BIT(PORTD,GPIO_PIN_3);
			_delay_ms(1000);
			CLEAR_BIT(PORTD,GPIO_PIN_3);*/
			if ((str_info.push_index==zero) && (str_info.pressed_type==successful_pressed))
			{
				
				switch (str_info.duration_long)
				{
					
				case shortt:
				{
					SET_BIT(PORTC,GPIO_PIN_2);
					_delay_ms(1000);
					CLEAR_BIT(PORTC,GPIO_PIN_2);
					break;
				}
				case doubleeee:
				{
					SET_BIT(PORTC,GPIO_PIN_2);
					SET_BIT(PORTC,GPIO_PIN_7);
					_delay_ms(1000);
					CLEAR_BIT(PORTC,GPIO_PIN_2);
					CLEAR_BIT(PORTC,GPIO_PIN_7);
					break;
				}
				case longg:
				{
					SET_BIT(PORTC,GPIO_PIN_2);
					SET_BIT(PORTC,GPIO_PIN_7);
					SET_BIT(PORTD,GPIO_PIN_3);
					_delay_ms(1000);
					CLEAR_BIT(PORTC,GPIO_PIN_2);
					CLEAR_BIT(PORTC,GPIO_PIN_7);
					CLEAR_BIT(PORTD,GPIO_PIN_3);
					break;
				}
					
				}
				
			}
			else if ((str_info.push_index==one) && (str_info.pressed_type==successful_pressed))
			{
				switch (str_info.duration_long)
				{
					
					case shortt:
					{
						SET_BIT(PORTC,GPIO_PIN_2);
						_delay_ms(1000);
						CLEAR_BIT(PORTC,GPIO_PIN_2);
						break;
					}
					case doubleeee:
					{
						SET_BIT(PORTC,GPIO_PIN_2);
						SET_BIT(PORTC,GPIO_PIN_7);
						_delay_ms(1000);
						CLEAR_BIT(PORTC,GPIO_PIN_2);
						CLEAR_BIT(PORTC,GPIO_PIN_7);
						break;
					}
					case longg:
					{
						SET_BIT(PORTC,GPIO_PIN_2);
						SET_BIT(PORTC,GPIO_PIN_7);
						SET_BIT(PORTD,GPIO_PIN_3);
						_delay_ms(1000);
						CLEAR_BIT(PORTC,GPIO_PIN_2);
						CLEAR_BIT(PORTC,GPIO_PIN_7);
						CLEAR_BIT(PORTD,GPIO_PIN_3);
						break;
					}
					
				}
				
			}
			else if ((str_info.push_index==two) && (str_info.pressed_type==successful_pressed))
			{
				switch (str_info.duration_long)
				{
					
					case shortt:
					{
						SET_BIT(PORTC,GPIO_PIN_2);
						_delay_ms(1000);
						CLEAR_BIT(PORTC,GPIO_PIN_2);
						break;
					}
					case doubleeee:
					{
						SET_BIT(PORTC,GPIO_PIN_2);
						SET_BIT(PORTC,GPIO_PIN_7);
						_delay_ms(1000);
						CLEAR_BIT(PORTC,GPIO_PIN_2);
						CLEAR_BIT(PORTC,GPIO_PIN_7);
						break;
					}
					case longg:
					{
						SET_BIT(PORTC,GPIO_PIN_2);
						SET_BIT(PORTC,GPIO_PIN_7);
						SET_BIT(PORTD,GPIO_PIN_3);
						_delay_ms(1000);
						CLEAR_BIT(PORTC,GPIO_PIN_2);
						CLEAR_BIT(PORTC,GPIO_PIN_7);
						CLEAR_BIT(PORTD,GPIO_PIN_3);
						break;
					}
					
				}
				
			}
			return success;}
		else
		{
			return invalid;
		}
		
}






