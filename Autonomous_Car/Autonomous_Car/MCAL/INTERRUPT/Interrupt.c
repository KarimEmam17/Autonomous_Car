/*
 * interrupts.c
 *
 * Created: 4/11/2022 5:23:14 AM
 *  Author: K.EMAM
 */
#include "STD_TYPES.h"
#include "REG_ATMEL.h"
#include "BIT_MATH.h"
#include "interrupt.h"

#define Global_Interrupt_Enable_Bit 7   //Bit 7 – I of  SREG register
#define ISC2  6
void interrupt_enable(void)
{
	SET_BIT(SREG,Global_Interrupt_Enable_Bit);
}
//  void interrupt_enable(void) ==  SEI();


void interrupt_disable(void)
{
	CLEAR_BIT(SREG,Global_Interrupt_Enable_Bit);
}

// void interrupt_disable(void) == CLI();

void  Interrupt_Vector_Select_place(enum_Interrupt_Vector_place placed)
{
	switch(placed)
	{
		case the_start_of_the_Flash_memory :
			{
				SET_BIT(GICR,ivce);
				CLEAR_BIT(GICR,ivsel);
				break;
			}
		case the_start_of_the_Boot_Loader_section_of_the_Flash :
			{
				SET_BIT(GICR,ivce);
				SET_BIT(GICR,ivsel);	
				break;
			 }
	}
}
//1-Write the Interrupt Vector Change Enable (ivce) bit to one
//2-Within four cycles, write the desired value to ivsel while writing a zero to ivce. 


u8  init_External_Interrupt(enum_External_Interrupt External_Interrupt)
{
	if ((External_Interrupt==External_Interrupt_0) || (External_Interrupt==External_Interrupt_1) || (External_Interrupt==External_Interrupt_2))
	{
	switch(External_Interrupt)
	{
		case External_Interrupt_0:
			{
				GPIO_SetPinDir(GPIO_PORTD,GPIO_PIN_2,GPIO_PIN_INPUT);
				GPIO_SetPinVal(GPIO_PORTD,GPIO_PIN_2,GPIO_PIN_HIGH);
				interrupt_enable();
				SET_BIT(GICR,int0);
				break;
			}
		case External_Interrupt_1:
			{
				GPIO_SetPinDir(GPIO_PORTD,GPIO_PIN_3,GPIO_PIN_INPUT);
				GPIO_SetPinVal(GPIO_PORTD,GPIO_PIN_3,GPIO_PIN_HIGH);
				interrupt_enable();
				SET_BIT(GICR,int1);
				break;
			}
		case External_Interrupt_2:
			{
				GPIO_SetPinDir(GPIO_PORTB,GPIO_PIN_2,GPIO_PIN_INPUT);
				GPIO_SetPinVal(GPIO_PORTB,GPIO_PIN_2,GPIO_PIN_HIGH);
				interrupt_enable();
				SET_BIT(GICR,int2);
				break;
			}
	}
	return success;
	}
	else
	{
		return failed;
	}
}


u8 select_mode_of_External_Interrupt(enum_External_Interrupt External_Interrupt,enum_External_Interrupt_mode External_Interrupt_mode)
{
	if ((External_Interrupt>=0) && (External_Interrupt<3) && (External_Interrupt_mode>=0) && (External_Interrupt_mode<4))
	{
		switch(External_Interrupt)
		{
			case External_Interrupt_0:
			{
				switch(External_Interrupt_mode)
				{
					case The_low_level_mode:
					{
						CLEAR_BIT(MCUCR,isc11);
						CLEAR_BIT(MCUCR,isc10);
						break;
					}
					case Any_logical_change_mode:
					{
						CLEAR_BIT(MCUCR,isc11);
						SET_BIT(MCUCR,isc10);
						break;
					}
					case The_falling_edge_mode:
					{
						SET_BIT(MCUCR,isc11);
						CLEAR_BIT(MCUCR,isc10);
						break;
					}
					case The_rising_edge_mode:
					{
						SET_BIT(MCUCR,isc11);
						SET_BIT(MCUCR,isc10);
						break;
					}
				}
				break;
			}
			case External_Interrupt_1:
			{
				switch(External_Interrupt_mode)
				{
					case The_low_level_mode:
					{
						CLEAR_BIT(MCUCR,isc01);
						CLEAR_BIT(MCUCR,isc00);
						break;
					}
					case Any_logical_change_mode:
					{
						CLEAR_BIT(MCUCR,isc01);
						SET_BIT(MCUCR,isc00);
						break;
					}
					case The_falling_edge_mode:
					{
						SET_BIT(MCUCR,isc01);
						CLEAR_BIT(MCUCR,isc00);
						break;
					}
					case The_rising_edge_mode:
					{
						SET_BIT(MCUCR,isc01);
						CLEAR_BIT(MCUCR,isc00);
						break;
					}
				}
				break;
			}
			case External_Interrupt_2:
			{
				switch(External_Interrupt_mode)
				{
/*******************************ASK ENG.MINA PAGE 65**************************************************************************************/					
				/* The Asynchronous External Interrupt 2 is activated by the external pin int2 if the SREG
				I-bit and the corresponding interrupt mask in GICR are set. If ISC2 is written to zero, a
				falling edge on int2 activates the interrupt. If ISC2 is written to one, a rising edge on
				int2 activates the interrupt. Edges on int2 are registered asynchronously. Pulses on
				int2 wider than the minimum pulse width given in Table 36 will generate an interrupt.
				Shorter pulses are not guaranteed to generate an interrupt. When changing the ISC2
				bit, an interrupt can occur. Therefore, it is recommended to first disable int2 by clearing
				its Interrupt Enable bit in the GICR Register. Then, the ISC2 bit can be changed. */
					case The_falling_edge_mode:
					{
						CLEAR_BIT(GICR,int2);
						CLEAR_BIT(MCUCSR,ISC2);
						SET_BIT(GICR,int2);
						break;
					}
					case The_rising_edge_mode:
					{
						CLEAR_BIT(GICR,int2);
						SET_BIT(MCUCSR,ISC2);
						SET_BIT(GICR,int2);
						break;
					}
					default:
					return failed;
					break;
				}
				break;
			}
		}
		return success;
	}
	else
	{
		return failed;
	}
}