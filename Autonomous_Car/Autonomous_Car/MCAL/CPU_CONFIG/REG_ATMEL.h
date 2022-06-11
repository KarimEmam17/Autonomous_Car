/*
 * REG_ATMEL.h
 *
 * Created: 2/21/2022 1:03:55 AM
 *  Author: K.EMAM
 */ 


#ifndef REG_ATMEL_H_
#define REG_ATMEL_H_

#include "STD_TYPES.h"

#define  TWBR   (*( volatile u8*)( 0x20))
#define  TWSR   (*( volatile u8*)( 0x21))
#define  TWAR   (*( volatile u8*)( 0x22))
#define  TWDR   (*( volatile u8*)( 0x23))
#define  ADCL   (*( volatile u8*)( 0x24))
#define  ADCH   (*( volatile u8*)( 0x25))
#define  ADCSRA (*( volatile u8*)( 0x26))
#define  ADMUX  (*( volatile u8*)( 0x27))
#define  ACSR   (*( volatile u8*)( 0x28))
#define  UBRRL  (*( volatile u8*)( 0x29))
#define  UCSRB  (*( volatile u8*)( 0x2A))
#define  UCSRA  (*( volatile u8*)( 0x2B))
#define  UDR    (*( volatile u8*)( 0x2C))
#define  SPCR   (*( volatile u8*)( 0x2D))
#define  SPSR   (*( volatile u8*)( 0x2E))
#define  SPDR   (*( volatile u8*)( 0x2F))
#define  PIND   (*( volatile u8*)( 0x30))
#define  DDRD   (*( volatile u8*)( 0x31))
#define  PORTD  (*( volatile u8*)( 0x32))
#define  PINC   (*( volatile u8*)( 0x33))
#define  DDRC   (*( volatile u8*)( 0x34))
#define  PORTC  (*( volatile u8*)( 0x35))
#define  PINB   (*( volatile u8*)( 0x36))
#define  DDRB   (*( volatile u8*)( 0x37))
#define  PORTB  (*( volatile u8*)( 0x38))
#define  PINA   (*( volatile u8*)( 0x39))
#define  DDRA   (*( volatile u8*)( 0x3A))
#define  PORTA  (*( volatile u8*)( 0x3B))
#define  EECR   (*( volatile u8*)( 0x3C))
#define  EEDR   (*( volatile u8*)( 0x3D))
#define  EEARL  (*( volatile u8*)( 0x3E))
#define  EEARH  (*( volatile u8*)( 0x3F))
#define  UCSRC  (*( volatile u8*)( 0x40))
#define  UBRRH  (*( volatile u8*)( 0x40))
#define  WDTCR  (*( volatile u8*)( 0x41))
#define  ASSR   (*( volatile u8*)( 0x42))
#define  OCR2   (*( volatile u8*)( 0x43))
#define  TCNT2  (*( volatile u8*)( 0x44))
#define  TCCR2  (*( volatile u8*)( 0x45))
#define  ICR1   (*( volatile u16*)(0x46))
#define  ICR1L  (*( volatile u8*)( 0x46))
#define  ICR1H  (*( volatile u8*)( 0x47))
#define  OCR1BL (*( volatile u8*)( 0x48))
#define  OCR1BH (*( volatile u8*)( 0x49))
#define  OCR1A  (*( volatile u16*)(0x4A))
#define  OCR1AL (*( volatile u8*)( 0x4A))
#define  OCR1AH (*( volatile u8*)( 0x4B))
#define  TCNT1  (*( volatile u16*)(0x4C))
#define  TCNT1L (*( volatile u8*)( 0x4C))
#define  TCNT1H (*( volatile u8*)( 0x4D))
#define  TCCR1B (*( volatile u8*)( 0x4E))
#define  TCCR1A (*( volatile u8*)( 0x4F))
#define  SFIOR  (*( volatile u8*)( 0x50))
#define  OCDR   (*( volatile u8*)( 0x51))
#define  OSCCAL (*( volatile u8*)( 0x51))
#define  TCNT0  (*( volatile u8*)( 0x52))
#define  TCCR0  (*( volatile u8*)( 0x53))
#define  MCUCSR (*( volatile u8*)( 0x54))
#define  MCUCR  (*( volatile u8*)( 0x55))
#define  TWCR   (*( volatile u8*)( 0x56))
#define  SPMCR  (*( volatile u8*)( 0x57))
#define  TIFR   (*( volatile u8*)( 0x58))
#define  TIMSK  (*( volatile u8*)( 0x59))
#define  GIFR   (*( volatile u8*)( 0x5A))
#define  GICR   (*( volatile u8*)( 0x5B))
#define  OCR0  (*( volatile u8*)(0x5C))
#define  SPL   (*( volatile u8*)(0x5D))
#define  SPH   (*( volatile u8*)(0x5E))
#define  SREG  (*( volatile u8*)( 0x5F))





#endif /* REG_ATMEL_H_ */