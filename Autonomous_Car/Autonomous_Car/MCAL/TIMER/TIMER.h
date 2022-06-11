/*
* TIMER.h
*
* Created: 4/26/2022 1:08:44 AM
*  Author: K.EMAM
*/


#ifndef TIMER_H_
#define TIMER_H_

#include "STD_TYPES.h"
#include "Interrupt.h"

#define microsecond 1000 // from  micro  to mill
#define frequancy	16

/*************************************timer_0************************************************/


typedef enum
{
	T0_NORMAL=0,
	T0_PWM_PHASE_CORRECT,
	T0_CTC,
	T0_FAST_PWM,
	INVAILD_MODE
	
}Timer0_mode;


typedef enum
{
	No_clock_source =0,  // (Timer/Counter stopped).
	No_prescaler,
	From_prescaler_8,
	From_prescaler_64,
	From_prescaler_256,
	From_prescaler_1024,
	External_clock_source_falling_edge,
	External_clock_source_rising_edge,
	INVAILD_prescaler
	
}Timer0_prescaler;

//Timer/Counter Control Register TCCR0 REG BITS
typedef enum
{
	cs00=0,
	cs01,
	cs02,
	wgm01,
	com00,
	com01,
	wgm00,
	foc0,
	INVAILD_BIT
	
}Timer0_Counter_Control_Register;

//Timer/Counter Register TCNT0 i set the value

//Output Compare Register OCR0

//Timer/Counter Interrupt Mask Register TIMSK

typedef enum
{
	toie0=0,
	ocie0,
	
	
}Timer0_Counter_Interrupt_Mask_Register;

//Timer/Counter Interrupt Flag Register TIFR

typedef enum
{
	tov0=0,
	ocf0,
	
	
}Timer0_Counter_Interrupt_Flag_Register;

typedef enum
{
	Normal_port_operation_OC0_disconnected=0,
	Toggle_OC0_on_compare_match,
	Clear_OC0_on_compare_match,
	Set_OC0_on_compare_match,
	Clear_OC0_on_compare_match_set_OC0_at_TOP, //non inverting mode
	Set_OC0_on_compare_match_Clear_OC0_at_TOP,// inverting  mode
	Clear_OC0_on_compare_match_when_up_counting_Set_OC0_on_compare_match_when_downcounting,//non inverting mode
	Set_OC0_on_compare_match_when_up_counting_Clear_OC0_on_compare_match_when_downcounting,// inverting  mode
	
	
}Compare_Match_Output_Mode_for_OC0;

void init_timer0(Timer0_mode te_mode); // ok for timer 0
void select_Compare_Match_Output_Mode_of_timer0(Timer0_mode te_mode,Compare_Match_Output_Mode_for_OC0 te_cmom_selected);
void start_timer0(Timer0_prescaler Te_prescaler);//
void stop_timer0(void);
void set_delay_timer0_microsecand(Timer0_mode te_mode,Timer0_prescaler Te_prescaler,u32 t_delay,u8 OCRvalue_ctc);
void set_delay_timer0_millsecand(Timer0_mode te_mode,Timer0_prescaler Te_prescaler,u32 t_delay,u8 OCRvalue_ctc);
void set_dutycycle_timer0(Timer0_mode te_mode,Timer0_prescaler Te_prescaler,Compare_Match_Output_Mode_for_OC0 te_cmom_selected,u32 t_duty_cly);

/*************************************timer_1************************************************/

typedef enum
{
	T1_NORMAL=0,
	T1_PHASE_CORRECT_8_BIT,
	T1_PHASE_CORRECT_9_BIT,
	T1_PHASE_CORRECT_10_BIT,
	T1_CTC_OCR1A,
	T1_FAST_PWM_8_BIT,
	T1_FAST_PWM_9_BIT,
	T1_FAST_PWM_10_BIT,
	T1_PHASE_AND_FREQUENCY_CORRECT_ICR1,
	T1_PHASE_AND_FREQUENCY_CORRECT_OCR1A,
	T1_PHASE_CORRECT_ICR1,
	T1_PHASE_CORRECT_OCR1A,
	T1_CTC_ICR1,
	T1_FAST_PWM_ICR1=13,
	T1_FAST_PWM_OCR1A,
	
}Timer1_mode;
typedef enum
{
	wgm10=0,
	wgm11,
	foc1B,
	foc1A,
	com1B0,
	com1B1,
	com1A0,
	com1A1,
	
	
}Timer1_Counter_Control_Register_A;
typedef enum
{
	cs10=0,
	cs11,
	cs12,
	wgm12,
	wgm13,
	ices1=6,
	icnc1,	
}Timer1_Counter_Control_Register_B;

typedef enum
{
	toie1=2,
	ocie1B,
	ocie1A,
	ticie1,
	
}Timer1_Counter_Interrupt_Mask_Register;

//Timer/Counter Interrupt Flag Register TIFR

typedef enum
{
	tov1=2,
	ocf1B,
	ocf1A,
	icf1,
	
}Timer1_Counter_Interrupt_Flag_Register;

typedef enum
{
	Normal_port_operation_OC1A_OC1B_disconnected=0,
	Toggle_OC1A_on_compare_match,
	Toggle_OC1B_on_compare_match,
	Toggle_OC1A_on_compare_match_OC1B_disconnected,
	Toggle_OC1B_on_compare_match_OC1A_disconnected,
	Clear_OC1A_on_compare_match_Set_output_to_low_level,
	Clear_OC1B_on_compare_match_Set_output_to_low_level,
	Set_OC1A_on_compare_match_Set_output_to_high_level, 
	Set_OC1B_on_compare_match_Set_output_to_high_level, 
	Clear_OC1A_on_compare_match_set_OC1B_at_TOP,
	Clear_OC1B_on_compare_match_set_OC1A_at_TOP,
	Set_OC1A_on_compare_match_clear_OC1B_at_TOP,
	Set_OC1B_on_compare_match_clear_OC1A_at_TOP,
	Clear_OC1A_on_compare_match_when_up_counting_Set_OC1B_on_compare_match_when_downcounting,
	Clear_OC1B_on_compare_match_when_up_counting_Set_OC1A_on_compare_match_when_downcounting,
	set_OC1A_on_compare_match_when_up_counting_clear_OC1B_on_compare_match_when_downcounting,
	set_OC1B_on_compare_match_when_up_counting_clear_OC1A_on_compare_match_when_downcounting,
	
}Compare_Match_Output_Mode_for_OC1A_OC1B;

typedef enum
{
	
	COM1A=0,
	COM1B,
	
	
}Timer1_Counter_BIT_COM1XX_Status;
typedef enum
{
	
	ON_ICR=0,
	OFF_ICR,
	
	
}Timer1_ICR_Status;
typedef enum
{
	RISE,
	FALL
	
}Timer1_ICR_type;

void init_timer1(Timer1_mode te_mode);
void select_Compare_Match_Output_Mode_of_timer1(Timer0_mode te_mode,Compare_Match_Output_Mode_for_OC1A_OC1B te_cmom_selected,Timer1_Counter_BIT_COM1XX_Status COM1XX);
void start_timer1(Timer0_prescaler Te_prescaler);
void ICR_status(Timer1_ICR_Status ICR_STATUS,Timer1_ICR_type ICR_TYPE);

#endif /* TIMER_H_ */