/*
 * interrupts.h
 *
 * Created: 4/11/2022 4:33:47 AM
 *  Author: K.EMAM
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include "STD_TYPES.h"
#include "REG_ATMEL.h"
#include "BIT_MATH.h"
#include "GPIO_KAREEM.h"
//#include <avr/interrupt.h>


#define Global_Interrupt_Enable_Bit 7   //Bit 7 – I of  SREG register



typedef enum
{
	ivce=0,
	ivsel,
	int2=5,
	int0,
	int1,
	invalid_bit=8,
}enum_General_Interrupt_Control_Register;

typedef enum
{
	the_start_of_the_Flash_memory=0,
	the_start_of_the_Boot_Loader_section_of_the_Flash,
	invalid_place,
}enum_Interrupt_Vector_place;

typedef enum
{
	isc00=0,
	isc01,
	isc10,
	isc11,
	//invalid_bit=8,
	
}enum_MCU_Control_Register;
//MCUCR 
//Bit 3, 2 – ISC11, ISC10: Interrupt Sense Control
typedef enum
{
	
	failed,
	success,
	
}enum_status_op;

typedef enum
{
	External_Interrupt_0,
	External_Interrupt_1,
	External_Interrupt_2,
	invalid_External_Interrupt,
	
}enum_External_Interrupt;
typedef enum
{
	The_low_level_mode,
	Any_logical_change_mode,
	The_falling_edge_mode,
	The_rising_edge_mode,
	invalid_mode,
	
}enum_External_Interrupt_mode;
typedef enum
{
	intf2=5,
	intf0,
	intf1,
	
	
}enum_General_Interrupt_Flag_Register;//GIFR

void interrupt_enable(void);
void interrupt_disable(void);
void  Interrupt_Vector_Select_place(enum_Interrupt_Vector_place placed);  // GICR_Register == General_Interrupt_Control_Register 
u8  init_External_Interrupt(enum_External_Interrupt External_Interrupt);
u8 select_mode_of_External_Interrupt(enum_External_Interrupt External_Interrupt,enum_External_Interrupt_mode External_Interrupt_mode);



#endif /* INTERRUPTS_H_ */