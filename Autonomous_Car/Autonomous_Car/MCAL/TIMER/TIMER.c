/*
* TIMER.c
*
* Created: 4/26/2022 1:08:25 AM
*  Author: K.EMAM
*/
//freq=1/time
// 255-(16MHZ/prescalar/Disierd freq) ----> ??  ???? ?????  ?????  ?????? ????  ????? ??? ???

/*

TCCR0  --->> control the mode of timer
TCNT0---->> set the value on over flow mode  && cleared on compare match
OCR0 --->> output compare match reg  we used for set the value we wanted to  compare with
TIMSK -->> enable  the kined of interrupte
TIFR --->> this is the interrupte flag  reg


*/

#include "TIMER.h"
//#include "Interrupt.h"
#include "STD_TYPES.h"
#include "REG_ATMEL.h"
#include "BIT_MATH.h"
#include "GPIO_KAREEM.h"
#include <avr/interrupt.h>
/*************************************timer_0************************************************/
u8  initialvalue_tcnt0=0;
u32 number_OVF=0;
u32 number_CTC=0;

void init_timer0(Timer0_mode te_mode)
{
	
	/*
	1- TCCR0 = 0  >> normal mode & no clock source & Normal port operation, OC0 disconnected.
	2- TIMSK >>> SWITCH  CASE  on it to  choose between  ovf or output compare match
	3- SERG >> SET global interrupt
	*/
	TCCR0= 0x00;
	
	switch (te_mode)
	{
		case T0_NORMAL:
		{
			interrupt_disable();
			CLEAR_BIT(TCCR0,WGM00);CLEAR_BIT(TCCR0,WGM01);
			CLEAR_BIT(TCCR0,COM00);CLEAR_BIT(TCCR0,COM01);
			SET_BIT(TIMSK,TOIE0);
			interrupt_enable();
			break;
		}
		case T0_PWM_PHASE_CORRECT:
		{
			interrupt_disable();
			
			SET_BIT(TCCR0,WGM00);CLEAR_BIT(TCCR0,WGM01);
			
			interrupt_enable();
			break;
		}
		case T0_CTC:
		{
			interrupt_disable();
			CLEAR_BIT(TCCR0,WGM00);SET_BIT(TCCR0,WGM01);
			SET_BIT(TIMSK,OCIE0);
			interrupt_enable();
			break;
		}
		case  T0_FAST_PWM:
		{
			interrupt_disable();
			SET_BIT(TCCR0,WGM00);SET_BIT(TCCR0,WGM01);
			
			interrupt_enable();
			break;
		}
		default:
		{
			break;
		}
		
	}
	
}
void select_Compare_Match_Output_Mode_of_timer0(Timer0_mode te_mode,Compare_Match_Output_Mode_for_OC0 te_cmom_selected)
{
	
	switch (te_mode)
	{
		case T0_NORMAL:
		{
			SET_BIT(TIMSK,TOIE0);
			switch (te_cmom_selected)
			{
				case Normal_port_operation_OC0_disconnected:
				{
					CLEAR_BIT(TCCR0,COM00);
					CLEAR_BIT(TCCR0,COM01);
					break;
				}
				case Toggle_OC0_on_compare_match:
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					SET_BIT(TCCR0,COM00);
					CLEAR_BIT(TCCR0,COM01);
					break;
				}
				case Clear_OC0_on_compare_match:
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					CLEAR_BIT(TCCR0,COM00);
					SET_BIT(TCCR0,COM01);
					break;
				}
				case Set_OC0_on_compare_match:
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					SET_BIT(TCCR0,COM00);
					SET_BIT(TCCR0,COM01);
					break;
				}
			}
			break;
		}
		case T0_PWM_PHASE_CORRECT:
		{
			
			switch (te_cmom_selected)
			{
				
				case Clear_OC0_on_compare_match_when_up_counting_Set_OC0_on_compare_match_when_downcounting: //non inverting
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					CLEAR_BIT(TCCR0,COM00);
					SET_BIT(TCCR0,COM01);
					break;
				}
				case Set_OC0_on_compare_match_when_up_counting_Clear_OC0_on_compare_match_when_downcounting: // inverting
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					SET_BIT(TCCR0,COM00);
					SET_BIT(TCCR0,COM01);
					break;
				}
				
			}
			break;
		}
		case T0_CTC:
		{
			SET_BIT(TIMSK,OCIE0);
			switch (te_cmom_selected)
			{
				case Normal_port_operation_OC0_disconnected:
				{
					CLEAR_BIT(TCCR0,WGM00);
					CLEAR_BIT(TCCR0,WGM01);
					break;
				}
				case Toggle_OC0_on_compare_match:
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					SET_BIT(TCCR0,COM00);
					CLEAR_BIT(TCCR0,COM01);
					break;
				}
				case Clear_OC0_on_compare_match:
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					CLEAR_BIT(TCCR0,COM00);
					SET_BIT(TCCR0,COM01);
					break;
				}
				case Set_OC0_on_compare_match:
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					SET_BIT(TCCR0,COM00);
					SET_BIT(TCCR0,COM01);
					break;
				}
			}
			break;
		}
		case  T0_FAST_PWM:
		{
			
			switch (te_cmom_selected)
			{
				
				case Clear_OC0_on_compare_match_set_OC0_at_TOP:
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					CLEAR_BIT(TCCR0,COM00);
					SET_BIT(TCCR0,COM01);
					break;
				}
				case Set_OC0_on_compare_match_Clear_OC0_at_TOP:
				{
					SET_BIT(DDRB,GPIO_PIN_3);
					SET_BIT(TCCR0,COM00);
					SET_BIT(TCCR0,COM01);
					break;
				}
				
			}
			break;
		}
	}
}
void start_timer0(Timer0_prescaler Te_prescaler)
{
	
	switch (Te_prescaler)
	{
		case No_prescaler:
		{
			CLEAR_BIT(TCCR0,CS02);CLEAR_BIT(TCCR0,CS01);SET_BIT(TCCR0,CS00);
			
			break;
		}
		case From_prescaler_8:
		{
			CLEAR_BIT(TCCR0,CS02);SET_BIT(TCCR0,CS01);CLEAR_BIT(TCCR0,CS00);
			
			break;
		}
		case From_prescaler_64:
		{
			CLEAR_BIT(TCCR0,CS02);SET_BIT(TCCR0,CS01);SET_BIT(TCCR0,CS00);
			
			break;
		}
		case From_prescaler_256:
		{
			SET_BIT(TCCR0,CS02);CLEAR_BIT(TCCR0,CS01);CLEAR_BIT(TCCR0,CS00);
			
			break;
		}
		case From_prescaler_1024:
		{
			SET_BIT(TCCR0,CS02);CLEAR_BIT(TCCR0,CS01);SET_BIT(TCCR0,CS00);
			
			break;
		}
		case External_clock_source_falling_edge:
		{
			SET_BIT(TCCR0,CS02);SET_BIT(TCCR0,CS01);CLEAR_BIT(TCCR0,CS00);
			
			break;
		}
		case External_clock_source_rising_edge:
		{
			SET_BIT(TCCR0,CS02);SET_BIT(TCCR0,CS01);SET_BIT(TCCR0,CS00);
			
			break;
		}
	}
}
void stop_timer0(void)
{
	
	CLEAR_BIT(TCCR0,CS02);CLEAR_BIT(TCCR0,CS01);CLEAR_BIT(TCCR0,CS00);
	
	
}
void set_delay_timer0_microsecand(Timer0_mode te_mode,Timer0_prescaler Te_prescaler,u32 t_delay,u8 OCRvalue_ctc)
{
	switch (te_mode)
	{
		case T0_NORMAL:
		{
			switch (Te_prescaler)
			{
				case No_prescaler:
				{
					u8 tick =((1*1)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					
					break;
				}
				case From_prescaler_8:
				{
					u8 tick =((1*8)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_64:
				{
					u8 tick =((1*64)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_256:
				{
					u8 tick =((1*256)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_1024:
				{
					u8 tick =((1*1024)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				
			}
			break;
		}
		case T0_CTC:
		{
			switch (Te_prescaler)
			{
				case No_prescaler:
				{
					u8 tick =((1*1)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					
					break;
				}
				case From_prescaler_8:
				{
					u8 tick =((1*8)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_64:
				{
					u8 tick =((1*64)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_256:
				{
					u8 tick =((1*256)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_1024:
				{
					u8 tick =((1*1024)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				
			}
			break;
			
			
		}

	}
}
void set_delay_timer0_millsecand(Timer0_mode te_mode,Timer0_prescaler Te_prescaler,u32 t_delay,u8 OCRvalue_ctc)
{
	switch (te_mode)
	{
		case T0_NORMAL:
		{
			switch (Te_prescaler)
			{
				case No_prescaler:
				{
					u8 tick =((1*1)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					
					break;
				}
				case From_prescaler_8:
				{
					u8 tick =((1*8)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_64:
				{
					u8 tick =((1*64)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_256:
				{
					u8 tick =((1*256)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_1024:
				{
					u8 tick =((1*1024)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				
			}
			break;
		}
		case T0_CTC:
		{
			switch (Te_prescaler)
			{
				case No_prescaler:
				{
					u8 tick =((1*1)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					
					break;
				}
				case From_prescaler_8:
				{
					u8 tick =((1*8)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_64:
				{
					u8 tick =((1*64)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_256:
				{
					u8 tick =((1*256)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_1024:
				{
					u8 tick =((1*1024)/frequancy);
					u32 count = ((t_delay *1)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				
			}
			break;
			
			
		}

	}
}
void set_dutycycle_timer0(Timer0_mode te_mode,Timer0_prescaler Te_prescaler,Compare_Match_Output_Mode_for_OC0 te_cmom_selected,u32 t_duty_cly)
{
	switch (te_mode)
	{
		case  T0_FAST_PWM:
		{
			switch (te_cmom_selected)
			{
				case Clear_OC0_on_compare_match_set_OC0_at_TOP:
				{
					OCR0 =((256 *t_duty_cly )/100)-1;
					break;
				}
				case Set_OC0_on_compare_match_Clear_OC0_at_TOP:
				{
					OCR0 =(256-1)-(((256 *t_duty_cly )/100)-1);
					break;
				}
			}
			
			break;
		}
		case T0_PWM_PHASE_CORRECT:
		{
			switch (te_cmom_selected)
			{
				case Clear_OC0_on_compare_match_when_up_counting_Set_OC0_on_compare_match_when_downcounting:
				{
					OCR0 =((256 *t_duty_cly )/100)-1;
					break;
				}
				case Set_OC0_on_compare_match_when_up_counting_Clear_OC0_on_compare_match_when_downcounting:
				{
					OCR0 =(256-1)-(((256 *t_duty_cly )/100)-1);
					break;
				}
			}
			break;
		}
		
	}
	
}
/* when using delay 
ISR(TIMER0_OVF_vect)
{
	static u8 count = 0;
	count++;
	if (count =number_OVF)
	{
		//what will  happen  when  time comes
		
		count=0;
		TCNT0=initialvalue_tcnt0;
	}
}
*/
ISR(TIMER0_COMP_vect)
{
	static u8 count = 0;
	count++;
	if (count =number_CTC)
	{
		//what will  happen  when  time comes
		
		count=0;
		
	}
}

/*************************************timer_1************************************************/

void init_timer1(Timer1_mode te_mode)
{
	TCCR1B=0x00;
	TCCR1A=0x00;
	switch (te_mode)
	{
		case T1_NORMAL:
		{
			interrupt_disable();
			SET_BIT(TIMSK,TOIE1);
			CLEAR_BIT(TCCR1B, WGM13);
			CLEAR_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1A, WGM11);
			CLEAR_BIT(TCCR1A, WGM10);
			SET_BIT  (TIMSK , TOIE1);
			interrupt_enable();
			break;
		}
		case T1_PHASE_CORRECT_8_BIT:
		{
			interrupt_disable();
			
			CLEAR_BIT(TCCR1B, WGM13);
			CLEAR_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1A, WGM11);
			SET_BIT  (TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case T1_PHASE_CORRECT_9_BIT:
		{
			interrupt_disable();
			CLEAR_BIT(TCCR1B, WGM13);
			CLEAR_BIT(TCCR1B, WGM12);
			SET_BIT  (TCCR1A, WGM11);
			CLEAR_BIT(TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case  T1_PHASE_CORRECT_10_BIT:
		{
			interrupt_disable();
			CLEAR_BIT(TCCR1B, WGM13);
			CLEAR_BIT(TCCR1B, WGM12);
			SET_BIT  (TCCR1A, WGM11);
			SET_BIT  (TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case T1_CTC_OCR1A:
		{
			interrupt_disable();
			
			CLEAR_BIT(TCCR1B, WGM13 );
			SET_BIT  (TCCR1B, WGM12 );
			CLEAR_BIT(TCCR1A, WGM11 );
			CLEAR_BIT(TCCR1A, WGM10 );
			SET_BIT  (TIMSK , OCIE1A);
			interrupt_enable();
			break;
		}
		case T1_FAST_PWM_8_BIT:
		{
			interrupt_disable();
			
			CLEAR_BIT(TCCR1B, WGM13);
			SET_BIT  (TCCR1B, WGM12);
			CLEAR_BIT(TCCR1A, WGM11);
			SET_BIT  (TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case T1_FAST_PWM_9_BIT:
		{
			interrupt_disable();
			CLEAR_BIT(TCCR1B, WGM13);
			SET_BIT  (TCCR1B, WGM12);
			SET_BIT  (TCCR1A, WGM11);
			CLEAR_BIT(TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case  T1_FAST_PWM_10_BIT:
		{
			interrupt_disable();
			CLEAR_BIT(TCCR1B, WGM13);
			SET_BIT  (TCCR1B, WGM12);
			SET_BIT  (TCCR1A, WGM11);
			SET_BIT  (TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case T1_PHASE_AND_FREQUENCY_CORRECT_ICR1:
		{
			interrupt_disable();
			SET_BIT(TIMSK,TICIE1);
			SET_BIT  (TCCR1B, WGM13);
			CLEAR_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1A, WGM11);
			CLEAR_BIT(TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case T1_PHASE_AND_FREQUENCY_CORRECT_OCR1A:
		{
			interrupt_disable();
			SET_BIT  (TCCR1B, WGM13);
			CLEAR_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1A, WGM11);
			SET_BIT  (TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case  T1_PHASE_CORRECT_ICR1:
		{
			interrupt_disable();
			SET_BIT(TIMSK,TICIE1);
			SET_BIT  (TCCR1B, WGM13);
			CLEAR_BIT(TCCR1B, WGM12);
			SET_BIT  (TCCR1A, WGM11);
			CLEAR_BIT(TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case T1_PHASE_CORRECT_OCR1A:
		{
			interrupt_disable();
			SET_BIT  (TCCR1B, WGM13);
			CLEAR_BIT(TCCR1B, WGM12);
			SET_BIT  (TCCR1A, WGM11);
			SET_BIT  (TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case T1_CTC_ICR1:
		{
			interrupt_disable();
			
			SET_BIT  (TCCR1B, WGM13);
			SET_BIT  (TCCR1B, WGM12);
			CLEAR_BIT(TCCR1A, WGM11);
			CLEAR_BIT(TCCR1A, WGM10);
			SET_BIT  (TIMSK , TICIE1);
			interrupt_enable();
			break;
		}
		case T1_FAST_PWM_ICR1:
		{
			interrupt_disable();
			SET_BIT(TIMSK,TICIE1);
			SET_BIT  (TCCR1B, WGM13);
			SET_BIT  (TCCR1B, WGM12);
			SET_BIT  (TCCR1A, WGM11);
			CLEAR_BIT(TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		case  T1_FAST_PWM_OCR1A:
		{
			interrupt_disable();
			SET_BIT  (TCCR1B, WGM13);
			SET_BIT  (TCCR1B, WGM12);
			SET_BIT  (TCCR1A, WGM11);
			SET_BIT  (TCCR1A, WGM10);
			interrupt_enable();
			break;
		}
		default:
		{
			break;
		}
	}
	
	
}
void select_Compare_Match_Output_Mode_of_timer1(Timer0_mode te_mode,Compare_Match_Output_Mode_for_OC1A_OC1B te_cmom_selected,Timer1_Counter_BIT_COM1XX_Status COM1XX)
{
	switch (te_mode)
	{
		case T1_NORMAL:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match:
						{
							SET_BIT  (DDRD,GPIO_PIN_5);
							SET_BIT(TCCR1A,FOC1A);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_Set_output_to_low_level:
						{
							SET_BIT(TCCR1A,FOC1A);
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(PORTD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Set_OC1A_on_compare_match_Set_output_to_high_level:
						{
							SET_BIT(TCCR1A,FOC1A);
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT(PORTD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match:
						{
							SET_BIT(TCCR1A,FOC1B);
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_Set_output_to_low_level:
						{
							SET_BIT(TCCR1A,FOC1B);
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(PORTD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Set_OC1B_on_compare_match_Set_output_to_high_level:
						{
							SET_BIT(TCCR1A,FOC1B);
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT(PORTD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_CTC_OCR1A:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					SET_BIT(TIMSK,OCIE1A);
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match:
						{
							SET_BIT(TCCR1A,FOC1A);
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_Set_output_to_low_level:
						{
							SET_BIT(TCCR1A,FOC1A);
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(PORTD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Set_OC1A_on_compare_match_Set_output_to_high_level:
						{
							SET_BIT(TCCR1A,FOC1A);
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT(PORTD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					SET_BIT(TIMSK,OCIE1B);
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match:
						{
							SET_BIT(TCCR1A,FOC1B);
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_Set_output_to_low_level:
						{
							SET_BIT(TCCR1A,FOC1B);
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(PORTD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Set_OC1B_on_compare_match_Set_output_to_high_level:
						{
							SET_BIT(TCCR1A,FOC1B);
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT(PORTD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_CTC_ICR1:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT(TCCR1A,FOC1A);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_Set_output_to_low_level:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(PORTD,GPIO_PIN_5);
							SET_BIT(TCCR1A,FOC1A);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Set_OC1A_on_compare_match_Set_output_to_high_level:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT(PORTD,GPIO_PIN_5);
							SET_BIT(TCCR1A,FOC1A);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
			
				case COM1B:
				{
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT(TCCR1A,FOC1B);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_Set_output_to_low_level:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(PORTD,GPIO_PIN_4);
							SET_BIT(TCCR1A,FOC1B);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Set_OC1B_on_compare_match_Set_output_to_high_level:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT(PORTD,GPIO_PIN_4);
							SET_BIT(TCCR1A,FOC1B);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_FAST_PWM_8_BIT:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_set_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Set_OC1A_on_compare_match_clear_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_set_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Set_OC1B_on_compare_match_clear_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_FAST_PWM_9_BIT:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_set_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Set_OC1A_on_compare_match_clear_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_set_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Set_OC1B_on_compare_match_clear_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_FAST_PWM_10_BIT:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_set_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Set_OC1A_on_compare_match_clear_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_set_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Set_OC1B_on_compare_match_clear_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_FAST_PWM_ICR1:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_set_OC1B_at_TOP:
						{
							//SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Set_OC1A_on_compare_match_clear_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_set_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Set_OC1B_on_compare_match_clear_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_FAST_PWM_OCR1A:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_set_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Set_OC1A_on_compare_match_clear_OC1B_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_set_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Set_OC1B_on_compare_match_clear_OC1A_at_TOP:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_PHASE_AND_FREQUENCY_CORRECT_ICR1:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_when_up_counting_Set_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case set_OC1A_on_compare_match_when_up_counting_clear_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_when_up_counting_Set_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case set_OC1B_on_compare_match_when_up_counting_clear_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_PHASE_CORRECT_8_BIT:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_when_up_counting_Set_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case set_OC1A_on_compare_match_when_up_counting_clear_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_when_up_counting_Set_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case set_OC1B_on_compare_match_when_up_counting_clear_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_PHASE_CORRECT_9_BIT:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_when_up_counting_Set_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case set_OC1A_on_compare_match_when_up_counting_clear_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_when_up_counting_Set_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case set_OC1B_on_compare_match_when_up_counting_clear_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_PHASE_CORRECT_10_BIT:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_when_up_counting_Set_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case set_OC1A_on_compare_match_when_up_counting_clear_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_when_up_counting_Set_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case set_OC1B_on_compare_match_when_up_counting_clear_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_PHASE_AND_FREQUENCY_CORRECT_OCR1A:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_when_up_counting_Set_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case set_OC1A_on_compare_match_when_up_counting_clear_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
				
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_when_up_counting_Set_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case set_OC1B_on_compare_match_when_up_counting_clear_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		case T1_PHASE_CORRECT_ICR1:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_when_up_counting_Set_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case set_OC1A_on_compare_match_when_up_counting_clear_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_when_up_counting_Set_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case set_OC1B_on_compare_match_when_up_counting_clear_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}case T1_PHASE_CORRECT_OCR1A:
		{
			switch (COM1XX)
			{
				
				case COM1A:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case Toggle_OC1A_on_compare_match_OC1B_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
						case Clear_OC1A_on_compare_match_when_up_counting_Set_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							CLEAR_BIT(TCCR1A , COM1A0);
							break;
						}
						case set_OC1A_on_compare_match_when_up_counting_clear_OC1B_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_5);
							SET_BIT  (TCCR1A , COM1A1);
							SET_BIT  (TCCR1A , COM1A0);
							break;
						}
					}
					break;
				}
				
				
				
				case COM1B:
				{
					
					
					switch (te_cmom_selected)
					{
						
						
						case Normal_port_operation_OC1A_OC1B_disconnected:
						{
							CLEAR_BIT(TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case Toggle_OC1B_on_compare_match_OC1A_disconnected:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							CLEAR_BIT(DDRD,GPIO_PIN_5);
							CLEAR_BIT(TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
						case Clear_OC1B_on_compare_match_when_up_counting_Set_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							CLEAR_BIT(TCCR1A , COM1B0);
							break;
						}
						case set_OC1B_on_compare_match_when_up_counting_clear_OC1A_on_compare_match_when_downcounting:
						{
							SET_BIT(DDRD,GPIO_PIN_4);
							SET_BIT  (TCCR1A , COM1B1);
							SET_BIT  (TCCR1A , COM1B0);
							break;
						}
					}
					break;
				}
			}break;
		}
		
		
	}
}
void start_timer1(Timer0_prescaler Te_prescaler)
{
	
	switch (Te_prescaler)
	{
		case No_prescaler:
		{
			CLEAR_BIT(TCCR1B, CS12);
			CLEAR_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS10);
			break;
		}
		case From_prescaler_8:
		{
			CLEAR_BIT(TCCR1B, CS12);
			SET_BIT(TCCR1B, CS11);
			CLEAR_BIT(TCCR1B, CS10);
			break;
		}
		case From_prescaler_64:
		{
			CLEAR_BIT(TCCR1B, CS12);
			SET_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS10);
			break;
		}
		case From_prescaler_256:
		{
			SET_BIT(TCCR1B, CS12);
			CLEAR_BIT(TCCR1B, CS11);
			CLEAR_BIT(TCCR1B, CS10);
			
			break;
		}
		case From_prescaler_1024:
		{
			SET_BIT(TCCR1B, CS12);
			CLEAR_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS10);
			
			break;
		}
		case External_clock_source_falling_edge:
		{
			SET_BIT(TCCR1B, CS12);
			SET_BIT(TCCR1B, CS11);
			CLEAR_BIT(TCCR1B, CS10);
			
			break;
		}
		case External_clock_source_rising_edge:
		{
			SET_BIT(TCCR1B, CS12);
			SET_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS10);
			
			break;
		}
	}
}
void stop_timer1(void)
{
	
		CLEAR_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS10);
	
	
}
/*
void set_delay_timer1_microsecand(Timer1_mode te_mode,Timer0_prescaler Te_prescaler,u32 t_delay,u8 OCRvalue_ctc)
{
	switch (te_mode)
	{
		case T1_NORMAL:
		{
			switch (Te_prescaler)
			{
				case No_prescaler:
				{
					u8 tick =((1*1)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/65536);
					initialvalue_tcnt0 =(65536-(count%65536));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					
					break;
				}
				case From_prescaler_8:
				{
					u8 tick =((1*8)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_64:
				{
					u8 tick =((1*64)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_256:
				{
					u8 tick =((1*256)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_1024:
				{
					u8 tick =((1*1024)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				
			}
			break;
		}
		case T0_CTC:
		{
			switch (Te_prescaler)
			{
				case No_prescaler:
				{
					u8 tick =((1*1)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					
					break;
				}
				case From_prescaler_8:
				{
					u8 tick =((1*8)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_64:
				{
					u8 tick =((1*64)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_256:
				{
					u8 tick =((1*256)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_1024:
				{
					u8 tick =((1*1024)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				
			}
			break;
			
			
		}

	}
}
void set_delay_timer1_millsecand(Timer1_mode te_mode,Timer0_prescaler Te_prescaler,u32 t_delay,u8 OCRvalue_ctc)
{
	switch (te_mode)
	{
		case T0_NORMAL:
		{
			switch (Te_prescaler)
			{
				case No_prescaler:
				{
					u8 tick =((1*1)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					
					break;
				}
				case From_prescaler_8:
				{
					u8 tick =((1*8)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_64:
				{
					u8 tick =((1*64)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_256:
				{
					u8 tick =((1*256)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				case From_prescaler_1024:
				{
					u8 tick =((1*1024)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_OVF=(count/256);
					initialvalue_tcnt0 =(256-(count%256));
					TCNT0=initialvalue_tcnt0;
					number_OVF++;
					break;
				}
				
			}
			break;
		}
		case T0_CTC:
		{
			switch (Te_prescaler)
			{
				case No_prescaler:
				{
					u8 tick =((1*1)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					
					break;
				}
				case From_prescaler_8:
				{
					u8 tick =((1*8)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_64:
				{
					u8 tick =((1*64)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_256:
				{
					u8 tick =((1*256)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				case From_prescaler_1024:
				{
					u8 tick =((1*1024)/frequancy);
					u32 count = ((t_delay *microsecond)/tick);
					number_CTC=(count/OCRvalue_ctc);
					OCR0=OCRvalue_ctc;
					number_CTC++;
					break;
				}
				
			}
			break;
			
			
		}

	}
}*/
void ICR_status(Timer1_ICR_Status ICR_STATUS,Timer1_ICR_type ICR_TYPE)
{
	switch (ICR_STATUS)
	{
		case ON_ICR:
			{
				SET_BIT(TIMSK,5);
				SET_BIT(TIMSK,TOIE1);
				SET_BIT(TCCR1B,ICNC1);
				switch (ICR_TYPE)
				{
				case RISE:
					SET_BIT(TCCR1B,ICES1);
					break;
				case FALL:
					CLEAR_BIT(TCCR1B,ICES1);
					break;
				}
				break;
			}
		case OFF_ICR:
			{
				CLEAR_BIT(TIMSK,5);
				break;
			}
	}
}


