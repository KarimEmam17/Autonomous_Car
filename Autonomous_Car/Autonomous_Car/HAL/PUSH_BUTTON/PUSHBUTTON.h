/*
 * PUSHBUTTON.h
 *
 * Created: 4/5/2022 5:34:32 AM
 *  Author: K.EMAM
 */ 


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_KAREEM.h"
#include "REG_ATMEL.h"

typedef enum
{
	shortt=0, 
	doubleeee,
	longg,
	invaild_duration,
	
}duration_pressed;

typedef enum
{
	zero=0,
	one,
	two,
	invalid_button,
}push_button_index;

typedef enum
{
	failed=-1,
	successful_pressed=0,
	released,
}push_button_status;
typedef enum
{
	invalid=0,
	success=1,
}status_operation;
 typedef struct
 {
	 push_button_index		push_index;
	 push_button_status		pressed_type;
	 duration_pressed		duration_long;
	 }struct_push_button_info;

s8 init_push_button(push_button_index push_index);
s8 push_button_pressed_type(push_button_index u8_push_button_index,struct_push_button_info str_info, u32 u32_u32_count,s32 s32_status);








#endif /* PUSHBUTTON_H_ */